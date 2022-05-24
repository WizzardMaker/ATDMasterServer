#pragma once

struct SampleCallbacks;

namespace RakNet {
	class RakPeerInterface;
	class CloudServer;
}

class ServerBrowser {
private:
	RakNet::RakPeerInterface* rakPeer = nullptr;
	RakNet::RoomsPlugin* server = nullptr;
	
	SampleCallbacks* sampleCallbacks;
public:
	ServerBrowser(RakNet::RakPeerInterface* rakPeer);
	~ServerBrowser();
	void StartServer();
	void ProcessMessages();

private:
	void LoginToServer(RakNet::Packet* p);
};
