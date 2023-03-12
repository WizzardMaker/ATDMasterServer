#include "NatPunchthroughClient.h"
#include "stdafx.h"
#include "NATServer.h"
#include "RakPeerInterface.h"
#include "NatPunchthroughServer.h"
#include "UDPProxyCoordinator.h"
#include "UDPProxyServer.h"

using namespace RakNet;

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

	rakPeer->AttachPlugin(udpCoordinator);
	udpCoordinator->SetRemoteLoginPassword(COORDINATOR_PASSWORD);

	SocketDescriptor sd(SocketDescriptor(UDP_SERVER_PORT, nullptr));
	rakPeerUDP = RakPeerInterface::GetInstance();
	StartupResult hres = rakPeerUDP->Startup(8096, &sd, 1);

	rakPeerUDP->AttachPlugin(udpServer);
	udpServer->LoginToCoordinator(COORDINATOR_PASSWORD, rakPeerUDP->GetInternalID(UNASSIGNED_SYSTEM_ADDRESS));
}

unsigned int NATServer::GetConnectedUser() const {
	return this->nat->GetConnectedUserCount();
}
