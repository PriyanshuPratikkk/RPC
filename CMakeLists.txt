cmake_minimum_required(VERSION 3.10)
project(rpc_framework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find Poco libraries
find_package(Poco REQUIRED COMPONENTS Foundation Net JSON)

# Common source files
set(SOURCES
    src/MessageSerializer.cpp
    src/RPCClient.cpp
    src/RPCServer.cpp
)

# Server executable
add_executable(rpc_server src/rpc_server.cpp ${SOURCES})
target_link_libraries(rpc_server Poco::Foundation Poco::Net Poco::JSON)

# Client executable
add_executable(rpc_client src/rpc_client.cpp ${SOURCES})
target_link_libraries(rpc_client Poco::Foundation Poco::Net Poco::JSON)

