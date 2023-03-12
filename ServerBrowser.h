#pragma once

struct ATDRoomsCallbacks;

namespace RakNet {
	class RakPeerInterface;
	class CloudServer;
}

class ServerBrowser {
private:
	RakNet::RakPeerInterface* m_rakPeer = nullptr;
	RakNet::RoomsPlugin* m_server = nullptr;
	
	ATDRoomsCallbacks* m_sampleCallbacks;

protected:
	friend ATDRoomsCallbacks;

	unsigned int m_roomCreations = 0;
	unsigned int m_userLogins = 0;
public:
	ServerBrowser(RakNet::RakPeerInterface* rakPeer);
	~ServerBrowser();
	void StartServer();
	void ProcessMessages();

	[[nodiscard]] DataStructures::List<RakNet::Room*>       GetRooms() const;
	[[nodiscard]] DataStructures::List<RakNet::RoomMember*> GetUsers() const;
	[[nodiscard]] unsigned int                              GetRoomCreationCount() const;
	[[nodiscard]] unsigned int                              GetUserLoginCount() const;

private:
	void LoginToServer(RakNet::Packet* p);
};
