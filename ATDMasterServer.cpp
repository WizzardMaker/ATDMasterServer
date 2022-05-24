// ATDMasterServer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <memory>

#include "RakPeerInterface.h"
#include "stdafx.h"

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

    const unique_ptr<NATServer> nat = make_unique<NATServer>(rakPeer);
	const unique_ptr <ServerBrowser> browser = make_unique<ServerBrowser>(rakPeer);

	SocketDescriptor sd(SocketDescriptor(SERVER_BROWSER_PORT, nullptr));
	StartupResult hres = rakPeer->Startup(8096, &sd, 1);
	if (hres != RAKNET_STARTED) {
		printf("Error while starting the server! Reason: %d\n", hres);
		//__debugbreak();
		return -1;
	}

	nat->StartServer();
	browser->StartServer();

	while(true) {
		browser->ProcessMessages();
	}
}
