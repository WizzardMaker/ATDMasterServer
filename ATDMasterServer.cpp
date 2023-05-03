
#include <thread>

#include "RakPeerInterface.h"
#include "stdafx.h"
#include "NATServer.h"
#include "ServerBrowser.h"
#include "WebView.h"

using namespace RakNet;
using namespace std;

int main()
{
	printf("#############################\n");
	printf("ATD Master Server V0.0.1\n");
	printf("#############################\n");
	printf("\n");
	printf("Starting ATD master server...\n");

	RakPeerInterface* rakPeer = RakPeerInterface::GetInstance();

    const shared_ptr<NATServer> nat = make_shared<NATServer>(rakPeer);
	const shared_ptr<ServerBrowser> browser = make_shared<ServerBrowser>(rakPeer);
	const shared_ptr<WebView> view = make_shared<WebView>(browser, nat);

	SocketDescriptor sd(SocketDescriptor(SERVER_BROWSER_PORT, nullptr));
	StartupResult hres = rakPeer->Startup(8096, &sd, 1);
	if (hres != RAKNET_STARTED) {
		printf("Error while starting the server! Reason: %d\n", hres);
		//__debugbreak();
		return -1;
	}

	nat->StartServer();
	browser->StartServer();
	view->StartServer();

	printf("ATD master server started!\n");

	std::thread pollingThread([&] {
		while(true) {
			view->ProcessMessage();
			nat->ProcessMessages();
		}
	});
	

	while(true) {
		browser->ProcessMessages();
	}
}
