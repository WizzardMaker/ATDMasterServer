#pragma once

namespace RakNet {
	class RakPeerInterface;
	class NatPunchthroughServer;
	class UDPProxyCoordinator;
	class UDPProxyServer;
}


class NATServer {
private:
	RakNet::RakPeerInterface* rakPeer = nullptr;
	
	RakNet::NatPunchthroughServer* nat = nullptr;

	RakNet::UDPProxyCoordinator *udpCoordinator = nullptr;

	RakNet::UDPProxyServer *udpServer = nullptr;
	RakNet::RakPeerInterface* rakPeerUDP = nullptr;
public:
	NATServer(RakNet::RakPeerInterface* rakPeer);
	~NATServer();
	void StartServer();
};
