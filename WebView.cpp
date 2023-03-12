#include "stdafx.h"
#include "WebView.h"

#include <format>
#include <thread>

#include "ServerBrowser.h"
#include "NATServer.h"

#include "libs/mongoose/mongoose.h"

using namespace RakNet;

mg_mgr mgr;

void fn(mg_connection* c, int ev, void* ev_data, void* fn_data) {
	WebView* viewer = static_cast<WebView*>(fn_data);
	viewer->ServerMessageHandler(c, ev, ev_data);
}


void WebView::StartServer() {
	V_LOG("- Starting WebView Server...\n");

	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, "http://0.0.0.0:8000", fn, this);

}

void WebView::ProcessMessage() {
	mg_mgr_poll(&mgr, 100);
}

bool WebView::GetNATUserCount(mg_connection* c, mg_http_message* hm) const {
	if (!mg_http_match_uri(hm, "/api/v1/nat/users")) {
		return false;
	}

	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{count:%d}\n", this->m_natServer->GetConnectedUser());

	return true;
}

std::string TransformUsersToJson(DataStructures::List<RoomMember*> users) {
	std::string userJson{};
	for (unsigned int j = 0; j < users.Size(); j++) {
		const RoomsParticipant* user = users[j]->roomsParticipant;
		userJson = userJson.append(std::format("{{name:\"{0}\", guid:\"{1}\"}}\n", user->GetName().C_String(), user->GetGUID().ToString()));
	}

	return userJson;
}

bool WebView::GetBrowserUserCount(mg_connection* c, mg_http_message* hm) const {
	if (!mg_http_match_uri(hm, "/api/v1/browser/users")) {
		return false;
	}

	auto users = this->m_serverBrowser->GetUsers();
	const std::string userJson = TransformUsersToJson(users);

	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "[%s]\n", userJson.c_str());

	return true;
}


bool WebView::GetBrowserRooms(mg_connection* c, mg_http_message* hm) const {
	if (!mg_http_match_uri(hm, "/api/v1/browser/rooms")) {
		return false;
	}
	std::string json;

	json = json.append("");

	auto rooms = this->m_serverBrowser->GetRooms();
	for (unsigned int i = 0; i < rooms.Size(); i++) {
		Room* room = rooms[i];

		const char* name = room->GetStringProperty(DefaultRoomColumns::TC_ROOM_NAME);

		DataStructures::List<RoomMember*> users = room->roomMemberList;

		const std::string userJson = TransformUsersToJson(users);

		json.append(std::format("{{name:\"{0}\",user:[{1}]}}", name, userJson.c_str()));
	}


	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "[%s]\n", json.c_str());

	return true;
}

bool WebView::GetRoomCreationCount(mg_connection* c, mg_http_message* hm) const {
	if (!mg_http_match_uri(hm, "/api/v1/browser/history/rooms")) {
		return false;
	}

	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{count:%d}\n", this->m_serverBrowser->GetRoomCreationCount());

	return true;
}

bool WebView::GetUserLoginCount(mg_connection* c, mg_http_message* hm) {
	if (!mg_http_match_uri(hm, "/api/v1/browser/history/users")) {
		return false;
	}

	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{count:%d}\n", this->m_serverBrowser->GetUserLoginCount());

	return true;
}

void WebView::ServerMessageHandler(mg_connection* c, int ev, void* ev_data) {
	if (ev == MG_EV_HTTP_MSG) {
		mg_http_message* hm = static_cast<mg_http_message*>(ev_data);

		//NAT:
		if (GetNATUserCount(c, hm))
			return;

		//Browser:
		if (GetBrowserUserCount(c, hm))
			return;
		if (GetBrowserRooms(c, hm))
			return;

		//History:
		if (GetRoomCreationCount(c, hm))
			return;
		if (GetUserLoginCount(c, hm))
			return;

		mg_http_reply(c, 404, "", "");
	}
}
