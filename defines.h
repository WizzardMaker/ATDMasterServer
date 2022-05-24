#pragma once

#ifdef _DEBUG
///Verbose Log
#define V_LOG(...) printf(__VA_ARGS__)
#else
///Verbose Log
#define V_LOG()
#endif

///Error Log
#define E_LOG(...) printf(__VA_ARGS__)

constexpr int UDP_SERVER_PORT = 61014;
constexpr int SERVER_BROWSER_PORT = 61013;
constexpr const char* GAME_IDENTIFIER = "ATD";
constexpr const char* COORDINATOR_PASSWORD = "ATD_UDP_MASTER";