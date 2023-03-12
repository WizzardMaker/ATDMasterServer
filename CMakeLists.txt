cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(ATDMasterServer CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "DebugLinux"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_DEBUGLINUX "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUGLINUX "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUGLINUX "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUGLINUX "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUGLINUX "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################



























set(PROJECT_NAME ATDMasterServer)

################################################################################
# Source groups
################################################################################
set(Include
    "defines.h"
    "NATServer.h"
    "ServerBrowser.h"
    "ServerBrowserMessageTypes.h"
    "WebView.h"
    "stdafx.h"
)
source_group("Include" FILES ${Include})

set(Lib__raknet
    "libs/raknet/_FindFirst.cpp"
    "libs/raknet/_FindFirst.h"
    "libs/raknet/AutopatcherPatchContext.h"
    "libs/raknet/AutopatcherRepositoryInterface.h"
    "libs/raknet/Base64Encoder.cpp"
    "libs/raknet/Base64Encoder.h"
    "libs/raknet/BitStream.cpp"
    "libs/raknet/BitStream.h"
    "libs/raknet/CCRakNetSlidingWindow.cpp"
    "libs/raknet/CCRakNetSlidingWindow.h"
    "libs/raknet/CCRakNetUDT.cpp"
    "libs/raknet/CCRakNetUDT.h"
    "libs/raknet/CheckSum.cpp"
    "libs/raknet/CheckSum.h"
    "libs/raknet/CloudClient.cpp"
    "libs/raknet/CloudClient.h"
    "libs/raknet/CloudCommon.cpp"
    "libs/raknet/CloudCommon.h"
    "libs/raknet/CloudServer.cpp"
    "libs/raknet/CloudServer.h"
    "libs/raknet/CMakeLists.txt"
    "libs/raknet/CommandParserInterface.cpp"
    "libs/raknet/CommandParserInterface.h"
    "libs/raknet/ConnectionGraph2.cpp"
    "libs/raknet/ConnectionGraph2.h"
    "libs/raknet/ConsoleServer.cpp"
    "libs/raknet/ConsoleServer.h"
    "libs/raknet/DataCompressor.cpp"
    "libs/raknet/DataCompressor.h"
    "libs/raknet/DirectoryDeltaTransfer.cpp"
    "libs/raknet/DirectoryDeltaTransfer.h"
    "libs/raknet/DR_SHA1.cpp"
    "libs/raknet/DR_SHA1.h"
    "libs/raknet/DS_BinarySearchTree.h"
    "libs/raknet/DS_BPlusTree.h"
    "libs/raknet/DS_BytePool.cpp"
    "libs/raknet/DS_BytePool.h"
    "libs/raknet/DS_ByteQueue.cpp"
    "libs/raknet/DS_ByteQueue.h"
    "libs/raknet/DS_Hash.h"
    "libs/raknet/DS_Heap.h"
    "libs/raknet/DS_HuffmanEncodingTree.cpp"
    "libs/raknet/DS_HuffmanEncodingTree.h"
    "libs/raknet/DS_HuffmanEncodingTreeFactory.h"
    "libs/raknet/DS_HuffmanEncodingTreeNode.h"
    "libs/raknet/DS_LinkedList.h"
    "libs/raknet/DS_List.h"
    "libs/raknet/DS_Map.h"
    "libs/raknet/DS_MemoryPool.h"
    "libs/raknet/DS_Multilist.h"
    "libs/raknet/DS_OrderedChannelHeap.h"
    "libs/raknet/DS_OrderedList.h"
    "libs/raknet/DS_Queue.h"
    "libs/raknet/DS_QueueLinkedList.h"
    "libs/raknet/DS_RangeList.h"
    "libs/raknet/DS_Table.cpp"
    "libs/raknet/DS_Table.h"
    "libs/raknet/DS_ThreadsafeAllocatingQueue.h"
    "libs/raknet/DS_Tree.h"
    "libs/raknet/DS_WeightedGraph.h"
    "libs/raknet/DynDNS.cpp"
    "libs/raknet/DynDNS.h"
    "libs/raknet/EmailSender.cpp"
    "libs/raknet/EmailSender.h"
    "libs/raknet/EmptyHeader.h"
    "libs/raknet/EpochTimeToString.cpp"
    "libs/raknet/EpochTimeToString.h"
    "libs/raknet/Export.h"
    "libs/raknet/FileList.cpp"
    "libs/raknet/FileList.h"
    "libs/raknet/FileListNodeContext.h"
    "libs/raknet/FileListTransfer.cpp"
    "libs/raknet/FileListTransfer.h"
    "libs/raknet/FileListTransferCBInterface.h"
    "libs/raknet/FileOperations.cpp"
    "libs/raknet/FileOperations.h"
    "libs/raknet/FormatString.cpp"
    "libs/raknet/FormatString.h"
    "libs/raknet/FullyConnectedMesh2.cpp"
    "libs/raknet/FullyConnectedMesh2.h"
    "libs/raknet/Getche.cpp"
    "libs/raknet/Getche.h"
    "libs/raknet/Gets.cpp"
    "libs/raknet/Gets.h"
    "libs/raknet/GetTime.cpp"
    "libs/raknet/GetTime.h"
    "libs/raknet/gettimeofday.cpp"
    "libs/raknet/gettimeofday.h"
    "libs/raknet/GridSectorizer.cpp"
    "libs/raknet/GridSectorizer.h"
    "libs/raknet/HTTPConnection.cpp"
    "libs/raknet/HTTPConnection.h"
    "libs/raknet/HTTPConnection2.cpp"
    "libs/raknet/HTTPConnection2.h"
    "libs/raknet/IncrementalReadInterface.cpp"
    "libs/raknet/IncrementalReadInterface.h"
    "libs/raknet/InternalPacket.h"
    "libs/raknet/Itoa.cpp"
    "libs/raknet/Itoa.h"
    "libs/raknet/Kbhit.h"
    "libs/raknet/LinuxStrings.cpp"
    "libs/raknet/LinuxStrings.h"
    "libs/raknet/LocklessTypes.cpp"
    "libs/raknet/LocklessTypes.h"
    "libs/raknet/LogCommandParser.cpp"
    "libs/raknet/LogCommandParser.h"
    "libs/raknet/MessageFilter.cpp"
    "libs/raknet/MessageFilter.h"
    "libs/raknet/MessageIdentifiers.h"
    "libs/raknet/MTUSize.h"
    "libs/raknet/NativeFeatureIncludes.h"
    "libs/raknet/NativeFeatureIncludesOverrides.h"
    "libs/raknet/NativeTypes.h"
    "libs/raknet/NatPunchthroughClient.cpp"
    "libs/raknet/NatPunchthroughClient.h"
    "libs/raknet/NatPunchthroughServer.cpp"
    "libs/raknet/NatPunchthroughServer.h"
    "libs/raknet/NatTypeDetectionClient.cpp"
    "libs/raknet/NatTypeDetectionClient.h"
    "libs/raknet/NatTypeDetectionCommon.cpp"
    "libs/raknet/NatTypeDetectionCommon.h"
    "libs/raknet/NatTypeDetectionServer.cpp"
    "libs/raknet/NatTypeDetectionServer.h"
    "libs/raknet/NetworkIDManager.cpp"
    "libs/raknet/NetworkIDManager.h"
    "libs/raknet/NetworkIDObject.cpp"
    "libs/raknet/NetworkIDObject.h"
    "libs/raknet/PacketConsoleLogger.cpp"
    "libs/raknet/PacketConsoleLogger.h"
    "libs/raknet/PacketFileLogger.cpp"
    "libs/raknet/PacketFileLogger.h"
    "libs/raknet/PacketizedTCP.cpp"
    "libs/raknet/PacketizedTCP.h"
    "libs/raknet/PacketLogger.cpp"
    "libs/raknet/PacketLogger.h"
    "libs/raknet/PacketOutputWindowLogger.cpp"
    "libs/raknet/PacketOutputWindowLogger.h"
    "libs/raknet/PacketPool.h"
    "libs/raknet/PacketPriority.h"
    "libs/raknet/PluginInterface2.cpp"
    "libs/raknet/PluginInterface2.h"
    "libs/raknet/PS3Includes.h"
    "libs/raknet/PS4Includes.cpp"
    "libs/raknet/PS4Includes.h"
    "libs/raknet/Rackspace.cpp"
    "libs/raknet/Rackspace.h"
    "libs/raknet/RakAlloca.h"
    "libs/raknet/RakAssert.h"
    "libs/raknet/RakMemoryOverride.cpp"
    "libs/raknet/RakMemoryOverride.h"
    "libs/raknet/RakNetCommandParser.cpp"
    "libs/raknet/RakNetCommandParser.h"
    "libs/raknet/RakNetDefines.h"
    "libs/raknet/RakNetDefinesOverrides.h"
    "libs/raknet/RakNetSmartPtr.h"
    "libs/raknet/RakNetSocket.cpp"
    "libs/raknet/RakNetSocket.h"
    "libs/raknet/RakNetSocket2.cpp"
    "libs/raknet/RakNetSocket2.h"
    "libs/raknet/RakNetSocket2_360_720.cpp"
    "libs/raknet/RakNetSocket2_Berkley.cpp"
    "libs/raknet/RakNetSocket2_Berkley_NativeClient.cpp"
    "libs/raknet/RakNetSocket2_NativeClient.cpp"
    "libs/raknet/RakNetSocket2_PS3_PS4.cpp"
    "libs/raknet/RakNetSocket2_PS4.cpp"
    "libs/raknet/RakNetSocket2_Vita.cpp"
    "libs/raknet/RakNetSocket2_Windows_Linux.cpp"
    "libs/raknet/RakNetSocket2_Windows_Linux_360.cpp"
    "libs/raknet/RakNetSocket2_WindowsStore8.cpp"
    "libs/raknet/RakNetStatistics.cpp"
    "libs/raknet/RakNetStatistics.h"
    "libs/raknet/RakNetTime.h"
    "libs/raknet/RakNetTransport2.cpp"
    "libs/raknet/RakNetTransport2.h"
    "libs/raknet/RakNetTypes.cpp"
    "libs/raknet/RakNetTypes.h"
    "libs/raknet/RakNetVersion.h"
    "libs/raknet/RakPeer.cpp"
    "libs/raknet/RakPeer.h"
    "libs/raknet/RakPeerInterface.h"
    "libs/raknet/RakSleep.cpp"
    "libs/raknet/RakSleep.h"
    "libs/raknet/RakString.cpp"
    "libs/raknet/RakString.h"
    "libs/raknet/RakThread.cpp"
    "libs/raknet/RakThread.h"
    "libs/raknet/RakWString.cpp"
    "libs/raknet/RakWString.h"
    "libs/raknet/Rand.cpp"
    "libs/raknet/Rand.h"
    "libs/raknet/RandSync.cpp"
    "libs/raknet/RandSync.h"
    "libs/raknet/ReadyEvent.cpp"
    "libs/raknet/ReadyEvent.h"
    "libs/raknet/RefCountedObj.h"
    "libs/raknet/RelayPlugin.cpp"
    "libs/raknet/RelayPlugin.h"
    "libs/raknet/ReliabilityLayer.cpp"
    "libs/raknet/ReliabilityLayer.h"
    "libs/raknet/ReplicaEnums.h"
    "libs/raknet/ReplicaManager3.cpp"
    "libs/raknet/ReplicaManager3.h"
    "libs/raknet/Router2.cpp"
    "libs/raknet/Router2.h"
    "libs/raknet/RPC4Plugin.cpp"
    "libs/raknet/RPC4Plugin.h"
    "libs/raknet/SecureHandshake.cpp"
    "libs/raknet/SecureHandshake.h"
    "libs/raknet/SendToThread.cpp"
    "libs/raknet/SendToThread.h"
    "libs/raknet/SignaledEvent.cpp"
    "libs/raknet/SignaledEvent.h"
    "libs/raknet/SimpleMutex.cpp"
    "libs/raknet/SimpleMutex.h"
    "libs/raknet/SimpleTCPServer.h"
    "libs/raknet/SingleProducerConsumer.h"
    "libs/raknet/SocketDefines.h"
    "libs/raknet/SocketIncludes.h"
    "libs/raknet/SocketLayer.cpp"
    "libs/raknet/SocketLayer.h"
    "libs/raknet/StatisticsHistory.cpp"
    "libs/raknet/StatisticsHistory.h"
    "libs/raknet/StringCompressor.cpp"
    "libs/raknet/StringCompressor.h"
    "libs/raknet/StringTable.cpp"
    "libs/raknet/StringTable.h"
    "libs/raknet/SuperFastHash.cpp"
    "libs/raknet/SuperFastHash.h"
    "libs/raknet/TableSerializer.cpp"
    "libs/raknet/TableSerializer.h"
    "libs/raknet/TCPInterface.cpp"
    "libs/raknet/TCPInterface.h"
    "libs/raknet/TeamBalancer.cpp"
    "libs/raknet/TeamBalancer.h"
    "libs/raknet/TeamManager.cpp"
    "libs/raknet/TeamManager.h"
    "libs/raknet/TelnetTransport.cpp"
    "libs/raknet/TelnetTransport.h"
    "libs/raknet/ThreadPool.h"
    "libs/raknet/ThreadsafePacketLogger.cpp"
    "libs/raknet/ThreadsafePacketLogger.h"
    "libs/raknet/TransportInterface.h"
    "libs/raknet/TwoWayAuthentication.cpp"
    "libs/raknet/TwoWayAuthentication.h"
    "libs/raknet/UDPForwarder.cpp"
    "libs/raknet/UDPForwarder.h"
    "libs/raknet/UDPProxyClient.cpp"
    "libs/raknet/UDPProxyClient.h"
    "libs/raknet/UDPProxyCommon.h"
    "libs/raknet/UDPProxyCoordinator.cpp"
    "libs/raknet/UDPProxyCoordinator.h"
    "libs/raknet/UDPProxyServer.cpp"
    "libs/raknet/UDPProxyServer.h"
    "libs/raknet/VariableDeltaSerializer.cpp"
    "libs/raknet/VariableDeltaSerializer.h"
    "libs/raknet/VariableListDeltaTracker.cpp"
    "libs/raknet/VariableListDeltaTracker.h"
    "libs/raknet/VariadicSQLParser.cpp"
    "libs/raknet/VariadicSQLParser.h"
    "libs/raknet/VitaIncludes.cpp"
    "libs/raknet/VitaIncludes.h"
    "libs/raknet/WindowsIncludes.h"
    "libs/raknet/WSAStartupSingleton.cpp"
    "libs/raknet/WSAStartupSingleton.h"
    "libs/raknet/XBox360Includes.h"
)
source_group("Lib\\raknet" FILES ${Lib__raknet})

set(Lib__rooms
    "libs/rooms-plugin/IntervalTimer.cpp"
    "libs/rooms-plugin/IntervalTimer.h"
    "libs/rooms-plugin/ProfanityFilter.cpp"
    "libs/rooms-plugin/ProfanityFilter.h"
    "libs/rooms-plugin/RoomsContainer.cpp"
    "libs/rooms-plugin/RoomsContainer.h"
    "libs/rooms-plugin/RoomsErrorCodes.cpp"
    "libs/rooms-plugin/RoomsErrorCodes.h"
    "libs/rooms-plugin/RoomsPlugin.cpp"
    "libs/rooms-plugin/RoomsPlugin.h"
    "libs/rooms-plugin/RoomTypes.cpp"
    "libs/rooms-plugin/RoomTypes.h"
)
source_group("Lib\\rooms" FILES ${Lib__rooms})

set(Lib__mongoose
    "libs/mongoose/mongoose.cpp"
    "libs/mongoose/mongoose.h"
)
source_group("Lib\\mongoose" FILES ${Lib__mongoose})

set(Source
    "ATDMasterServer.cpp"
    "NATServer.cpp"
    "ServerBrowser.cpp"
    "WebView.cpp"
)
source_group("Source" FILES ${Source})

set(ALL_FILES
    ${Include}
    ${Lib__raknet}
    ${Lib__rooms}
    ${Source}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE ATDMasterServer)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE    "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE    "TRUE"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
            MultiThreadedDebug
        >
        $<$<CONFIG:DebugLinux>:
            MultiThreadedDebug
        >
        $<$<CONFIG:Release>:
            MultiThreaded
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:DebugLinux>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
            MultiThreadedDebug
        >
        $<$<CONFIG:DebugLinux>:
            MultiThreadedDebug
        >
        $<$<CONFIG:Release>:
            MultiThreaded
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:DebugLinux>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/raknet;"
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/rooms-plugin"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/raknet;"
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/rooms-plugin"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:DebugLinux>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_WINSOCK_DEPRECATED_NO_WARNINGS;"
        "_CRT_SECURE_NO_WARNINGS;"
        "_CONSOLE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:DebugLinux>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_WINSOCK_DEPRECATED_NO_WARNINGS;"
        "_CRT_SECURE_NO_WARNINGS;"
        "_CONSOLE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /MP;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /MP;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:DebugLinux>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:DebugLinux>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "pthread"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

