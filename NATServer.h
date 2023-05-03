#pragma once


namespace RakNet {
    class RakPeerInterface;
    class NatPunchthroughServer;
    class UDPProxyCoordinator;
    class UDPProxyServer;
}

class ExNatPunchthroughServer;


class NATServer {
private:
    RakNet::RakPeerInterface* rakPeer = nullptr;
    
    ExNatPunchthroughServer* nat = nullptr;

    RakNet::UDPProxyCoordinator *udpCoordinator = nullptr;

    RakNet::UDPProxyServer *udpServer = nullptr;
    RakNet::RakPeerInterface* rakPeerUDP = nullptr;

    bool hasUDPLoggedIn = false;
public:
    NATServer(RakNet::RakPeerInterface* rakPeer);
    ~NATServer();
    void StartServer();
    
    [[nodiscard]] unsigned int GetConnectedUser() const;
    void                       ProcessMessages();
};
