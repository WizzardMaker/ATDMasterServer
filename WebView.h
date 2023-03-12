#pragma once
struct mg_http_message;
struct mg_connection;
class NATServer;

class WebView {
public:
	WebView(const std::shared_ptr<ServerBrowser> serverBrowser, const std::shared_ptr<NATServer> natServer)
		: m_serverBrowser(serverBrowser),
		m_natServer(natServer) {}

	void        StartServer();
	static void ProcessMessage();

	void ServerMessageHandler(mg_connection* c, int ev, void* ev_data);
protected:
	std::shared_ptr<ServerBrowser> m_serverBrowser;
	std::shared_ptr<NATServer> m_natServer;


	bool GetNATUserCount(mg_connection* c, mg_http_message* hm) const;
	bool GetBrowserUserCount(mg_connection* c, mg_http_message* hm) const;
	bool GetBrowserRooms(mg_connection* c, mg_http_message* hm) const;
	bool GetRoomCreationCount(mg_connection* c, mg_http_message* hm) const;
	bool GetUserLoginCount(mg_connection* c, mg_http_message* hm);
};


