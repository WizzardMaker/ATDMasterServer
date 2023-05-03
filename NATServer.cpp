#include "NatPunchthroughClient.h"
#include "stdafx.h"
#include "NATServer.h"

#include <thread>

#include "RakPeerInterface.h"
#include "NatPunchthroughServer.h"
#include "UDPProxyCoordinator.h"
#include "UDPProxyServer.h"

using namespace RakNet;


class UDPProxyHandler : public RakNet::UDPProxyServerResultHandler {
public:
	void OnLoginSuccess(RakNet::RakString usedPassword, RakNet::UDPProxyServer* proxyServerPlugin) override {
		V_LOG("OnLoginSuccess");
	}

	void OnAlreadyLoggedIn(RakNet::RakString usedPassword, RakNet::UDPProxyServer* proxyServerPlugin) override {
		V_LOG("OnAlreadyLoggedIn");
	}

	void OnNoPasswordSet(RakNet::RakString usedPassword, RakNet::UDPProxyServer* proxyServerPlugin) override {
		V_LOG("OnNoPasswordSet");
	}

	void OnWrongPassword(RakNet::RakString usedPassword, RakNet::UDPProxyServer* proxyServerPlugin) override {
		V_LOG("OnWrongPassword");
	}
};

class ExNatPunchthroughServer : public NatPunchthroughServer {
public:
	[[nodiscard]] unsigned int GetConnectedUserCount() const {
		return this->users.Size();
	}
};

NATServer::NATServer(RakNet::RakPeerInterface* rakPeer) : rakPeer(rakPeer), nat(new ExNatPunchthroughServer()), udpCoordinator(new UDPProxyCoordinator()), udpServer(new UDPProxyServer) {}

NATServer::~NATServer() {
	if(rakPeer->IsActive()) {
		rakPeer->Shutdown(100);
	}

	rakPeer->DetachPlugin(udpCoordinator);
	rakPeer->DetachPlugin(nat);
	NatPunchthroughServer::DestroyInstance(nat);
	UDPProxyCoordinator::DestroyInstance(udpCoordinator);

	RakPeerInterface::DestroyInstance(rakPeer);
}

void NATServer::StartServer() {

	V_LOG("- Starting NAT & UDP Server...\n");
	
	rakPeer->AttachPlugin(nat);
	NatPunchthroughServerDebugInterface_Printf* debug = new NatPunchthroughServerDebugInterface_Printf();
	nat->SetDebugInterface(debug);
	
	udpCoordinator->SetRemoteLoginPassword(COORDINATOR_PASSWORD);
	rakPeer->AttachPlugin(udpCoordinator);

	SocketDescriptor sd(SocketDescriptor(UDP_SERVER_PORT, nullptr));
	rakPeerUDP = RakPeerInterface::GetInstance();

	udpServer->SetResultHandler(new UDPProxyHandler());
	rakPeerUDP->AttachPlugin(udpServer);
	StartupResult hres = rakPeerUDP->Startup(8096, &sd, 1);
}

unsigned int NATServer::GetConnectedUser() const {
	return this->nat->GetConnectedUserCount();
}

int CheckConnectionPacket(Packet* p) {
	switch(p->data[0]) {
	case ID_CONNECTION_REQUEST_ACCEPTED:
		{ // Send our ID to server so that others can connect to us
			return 1;
		}
	case ID_CONNECTION_ATTEMPT_FAILED:
	case ID_REMOTE_SYSTEM_REQUIRES_PUBLIC_KEY:
	case ID_OUR_SYSTEM_REQUIRES_SECURITY:
	case ID_PUBLIC_KEY_MISMATCH:
	case ID_INVALID_PASSWORD:
	case ID_CONNECTION_BANNED:
	case ID_INCOMPATIBLE_PROTOCOL_VERSION:
	case ID_NO_FREE_INCOMING_CONNECTIONS:
	case ID_IP_RECENTLY_CONNECTED:
		V_LOG("Connect(..) failed! Reason: %d", p->data[0]);
		return 0;
	case ID_ALREADY_CONNECTED:
		return 0;
	default:
		return 2;
	}
}


bool AwaitConnection(RakPeerInterface* peerInterface) {
	while(true) {
		Packet* p = peerInterface->Receive();
		if(p == nullptr)
			continue;

		const int result = CheckConnectionPacket(p);

		if(result == 2) {
			peerInterface->PushBackPacket(p, false);
		} else {
			peerInterface->DeallocatePacket(p);
			return result == 1;
		}
	}
}

void NATServer::ProcessMessages() {
	if(!this->hasUDPLoggedIn) {
		SystemAddress coordinator_address = rakPeer->GetInternalID(UNASSIGNED_SYSTEM_ADDRESS);
		rakPeerUDP->Connect(coordinator_address.ToString(false), coordinator_address.GetPort(), nullptr, 0);
		if(!AwaitConnection(rakPeerUDP)) {
			throw;
		}
		udpServer->LoginToCoordinator(COORDINATOR_PASSWORD, coordinator_address);
		this->hasUDPLoggedIn = true;
	}

	Packet* packet = rakPeerUDP->Receive();
	if(packet) {
		rakPeerUDP->DeallocatePacket(packet);
	}
}
