﻿#include <string>

#include "stdafx.h"
#include "ServerBrowser.h"

#include "CloudServer.h"
#include "RakPeerInterface.h"
#include "NatPunchthroughServer.h"
#include "ServerBrowserMessageTypes.h"
#include "StringCompressor.h"

using namespace RakNet;

struct ATDRoomsCallbacks : public RakNet::RoomsCallback {
	ServerBrowser *parent;

	explicit ATDRoomsCallbacks(ServerBrowser* parent)
		: parent(parent) {}

	// Results of calls
	virtual void CreateRoom_Callback(const RakNet::SystemAddress& senderAddress, RakNet::CreateRoom_Func* callResult) { (void)senderAddress;

		if(callResult->resultCode != REC_SUCCESS) {
			E_LOG("[Server Browser] Room creation failed! Reason: \"%s\"\n", RoomsErrorCodeDescription::ToEnglish(callResult->resultCode));
			return;
		}
		V_LOG("[Server Browser] New game room \"%s\"!\n", callResult->networkedRoomCreationParameters.roomName.C_String());

		parent->m_roomCreations++;
	}
	//virtual void EnterRoom_Callback(const RakNet::SystemAddress& senderAddress, RakNet::EnterRoom_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void JoinByFilter_Callback(const RakNet::SystemAddress& senderAddress, RakNet::JoinByFilter_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void LeaveRoom_Callback(const RakNet::SystemAddress& senderAddress, RakNet::LeaveRoom_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void GetInvitesToParticipant_Callback(const RakNet::SystemAddress& senderAddress, RakNet::GetInvitesToParticipant_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void SendInvite_Callback(const RakNet::SystemAddress& senderAddress, RakNet::SendInvite_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void AcceptInvite_Callback(const RakNet::SystemAddress& senderAddress, RakNet::AcceptInvite_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void StartSpectating_Callback(const RakNet::SystemAddress& senderAddress, RakNet::StartSpectating_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void StopSpectating_Callback(const RakNet::SystemAddress& senderAddress, RakNet::StopSpectating_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void GrantModerator_Callback(const RakNet::SystemAddress& senderAddress, RakNet::GrantModerator_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void ChangeSlotCounts_Callback(const RakNet::SystemAddress& senderAddress, RakNet::ChangeSlotCounts_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void SetCustomRoomProperties_Callback(const RakNet::SystemAddress& senderAddress, RakNet::SetCustomRoomProperties_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void GetRoomProperties_Callback(const RakNet::SystemAddress& senderAddress, RakNet::GetRoomProperties_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void ChangeRoomName_Callback(const RakNet::SystemAddress& senderAddress, RakNet::ChangeRoomName_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void SetHiddenFromSearches_Callback(const RakNet::SystemAddress& senderAddress, RakNet::SetHiddenFromSearches_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void SetDestroyOnModeratorLeave_Callback(const RakNet::SystemAddress& senderAddress, RakNet::SetDestroyOnModeratorLeave_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void SetReadyStatus_Callback(const RakNet::SystemAddress& senderAddress, RakNet::SetReadyStatus_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void GetReadyStatus_Callback(const RakNet::SystemAddress& senderAddress, RakNet::GetReadyStatus_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void SetRoomLockState_Callback(const RakNet::SystemAddress& senderAddress, RakNet::SetRoomLockState_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void GetRoomLockState_Callback(const RakNet::SystemAddress& senderAddress, RakNet::GetRoomLockState_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void AreAllMembersReady_Callback(const RakNet::SystemAddress& senderAddress, RakNet::AreAllMembersReady_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void KickMember_Callback(const RakNet::SystemAddress& senderAddress, RakNet::KickMember_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void UnbanMember_Callback(const RakNet::SystemAddress& senderAddress, RakNet::UnbanMember_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void GetBanReason_Callback(const RakNet::SystemAddress& senderAddress, RakNet::GetBanReason_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void AddUserToQuickJoin_Callback(const RakNet::SystemAddress& senderAddress, RakNet::AddUserToQuickJoin_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void RemoveUserFromQuickJoin_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RemoveUserFromQuickJoin_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void IsInQuickJoin_Callback(const RakNet::SystemAddress& senderAddress, RakNet::IsInQuickJoin_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void SearchByFilter_Callback(const RakNet::SystemAddress& senderAddress, RakNet::SearchByFilter_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void ChangeHandle_Callback(const RakNet::SystemAddress& senderAddress, RakNet::ChangeHandle_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//virtual void Chat_Callback(const RakNet::SystemAddress& senderAddress, RakNet::Chat_Func* callResult) { (void)senderAddress; callResult->PrintResult(); }
	//// Notifications due to other room members
	//virtual void QuickJoinExpired_Callback(const RakNet::SystemAddress& senderAddress, RakNet::QuickJoinExpired_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void QuickJoinEnteredRoom_Callback(const RakNet::SystemAddress& senderAddress, RakNet::QuickJoinEnteredRoom_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomMemberStartedSpectating_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomMemberStartedSpectating_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomMemberStoppedSpectating_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomMemberStoppedSpectating_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void ModeratorChanged_Callback(const RakNet::SystemAddress& senderAddress, RakNet::ModeratorChanged_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void SlotCountsSet_Callback(const RakNet::SystemAddress& senderAddress, RakNet::SlotCountsSet_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void CustomRoomPropertiesSet_Callback(const RakNet::SystemAddress& senderAddress, RakNet::CustomRoomPropertiesSet_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomNameSet_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomNameSet_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void HiddenFromSearchesSet_Callback(const RakNet::SystemAddress& senderAddress, RakNet::HiddenFromSearchesSet_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomMemberReadyStatusSet_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomMemberReadyStatusSet_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomLockStateSet_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomLockStateSet_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomMemberKicked_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomMemberKicked_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomMemberHandleSet_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomMemberHandleSet_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomMemberLeftRoom_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomMemberLeftRoom_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomMemberJoinedRoom_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomMemberJoinedRoom_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomInvitationSent_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomInvitationSent_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomInvitationWithdrawn_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomInvitationWithdrawn_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void RoomDestroyedOnModeratorLeft_Callback(const RakNet::SystemAddress& senderAddress, RakNet::RoomDestroyedOnModeratorLeft_Notification* notification) { (void)senderAddress; notification->PrintResult(); }
	//virtual void Chat_Callback(const RakNet::SystemAddress& senderAddress, RakNet::Chat_Notification* notification) { (void)senderAddress; notification->PrintResult(); printf("Chat=%s\nFiltered=%s\n", notification->chatMessage.C_String(), notification->filteredChatMessage.C_String()); }
};

ServerBrowser::ServerBrowser(RakNet::RakPeerInterface* rakPeer) : m_rakPeer(rakPeer), m_server(new RoomsPlugin()) { }

ServerBrowser::~ServerBrowser() {
	if (m_rakPeer->IsActive()) {
		m_rakPeer->Shutdown(100);
	}

	m_rakPeer->DetachPlugin(m_server);
	delete m_server;
	
	RakPeerInterface::DestroyInstance(m_rakPeer);

	delete m_sampleCallbacks;
}

void ServerBrowser::StartServer() {
	V_LOG("- Starting Server Browser...\n");

	m_rakPeer->SetMaximumIncomingConnections(8192);

	m_sampleCallbacks = new ATDRoomsCallbacks(this);
	m_server->AddRoomsCallback(m_sampleCallbacks);

	m_server->SetServer(true);

	m_rakPeer->AttachPlugin(m_server);
	m_server->roomsContainer.AddTitle(GAME_IDENTIFIER);
}

void WriteBitStreamToString(char* myString, BitStream* input)
{
	StringCompressor::Instance()->DecodeString(myString, 256, input);
}

void ServerBrowser::LoginToServer(Packet *p) {
	char name[256];
	BitStream* data = new BitStream(p->data, p->length, false);
	data->IgnoreBytes(1);
	WriteBitStreamToString(name, data);

	if (!m_server->LoginRoomsParticipant(name, p->systemAddress, p->guid, RakNet::UNASSIGNED_SYSTEM_ADDRESS)) {
		printf("[Server Browser] User \"%s\" tried to connect, but was already logged in!\n", name);
		m_rakPeer->CloseConnection(p->guid, true,0);
	} else {
		printf("[Server Browser] New user: \"%s\" with id \"%s\"\n", name, p->guid.ToString());
		this->m_userLogins++;
	}

	delete data;
}

void ServerBrowser::ProcessMessages() {
	RakNet::Packet* p;
	p = m_rakPeer->Receive();
	if (p) {
		switch (p->data[0]) {
			case ID_NEW_INCOMING_CONNECTION:
				printf("[Server Browser] New connection received!\n");
				break;
			case ServerBrowserMessageTypes::REGISTER_NAME:
				LoginToServer(p);
				break;
			case ID_CONNECTION_LOST:
			case ID_DISCONNECTION_NOTIFICATION:
				printf("[Server Browser] Lost connection to: \"%s\"!\n", p->guid.ToString());
				break;
		}

		m_rakPeer->DeallocatePacket(p);
	}
}

DataStructures::List<Room*> ServerBrowser::GetRooms() const {
	auto g = this->m_server->roomsContainer.perGamesRoomsContainers.Get(GAME_IDENTIFIER);

	DataStructures::List<Room*> allRooms;
	g->GetAllRooms(allRooms);

	return allRooms;
}

DataStructures::List<RoomMember*> ServerBrowser::GetUsers() const {

	auto g = this->m_server->roomsContainer.perGamesRoomsContainers.Get(GAME_IDENTIFIER);

	DataStructures::List<RoomMember*> users;
	users.Clear(false, _FILE_AND_LINE_);

	DataStructures::List<Room*> allRooms;
	g->GetAllRooms(allRooms);

	for(unsigned int i = 0; i < allRooms.Size(); i++) {
		Room* room = allRooms[i];
		for(unsigned int j = 0; j < room->roomMemberList.Size(); j++) {
			users.Push(room->roomMemberList[j], __FILE__, __LINE__);
		}
	}

	return users;
}

unsigned int ServerBrowser::GetRoomCreationCount() const {
	return this->m_roomCreations;
}

unsigned int ServerBrowser::GetUserLoginCount() const {
	return this->m_userLogins;
}


