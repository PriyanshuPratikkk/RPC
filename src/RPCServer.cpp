// src/RPCServer.cpp

#include "RPCServer.h"
#include "MessageSerializer.h"
#include <iostream>

using namespace Poco::Net;

/**
 * Initializes the RPC server at the given address and port.
 * Binds a UDP socket to the address.
 */
RPCServer::RPCServer(const std::string& address, int port)
    : _address(address, port), _socket(_address, true) {
    std::cout << "RPC Server started at " << address << ":" << port << std::endl;
}

/**
 * Registers a method with a name and its function handler.
 */
void RPCServer::registerMethod(const std::string& name, std::function<int(std::vector<int>, int)> func) {
    _methods[name] = func;
}

/**
 * Starts the main loop to receive and process incoming RPC requests.
 */
void RPCServer::start() {
    char buffer[1024];

    while (true) {
        SocketAddress clientAddr;
        int n = _socket.receiveFrom(buffer, sizeof(buffer) - 1, clientAddr);
        buffer[n] = '\0';

        std::string requestStr(buffer);
        processRequest(requestStr, clientAddr);
    }
}

/**
 * Parses and executes the received request, sends a JSON response.
 */
void RPCServer::processRequest(const std::string& requestStr, SocketAddress& clientAddr) {
    std::string methodName;
    std::vector<int> params;
    int id;

    bool success = MessageSerializer::deserializeRequest(requestStr, methodName, params, id);
    if (!success) {
        std::cerr << "[RPCServer] Failed to parse request JSON: " << requestStr << std::endl;
        return;
    }

    if (_methods.find(methodName) != _methods.end()) {
        try {
            int result = _methods[methodName](params, id);
            std::string response = MessageSerializer::serializeResponse(result, id);
            _socket.sendTo(response.c_str(), response.size(), clientAddr);
        } catch (const std::exception& ex) {
            std::cerr << "[RPCServer] Error during method execution: " << ex.what() << std::endl;
        }
    } else {
        std::cerr << "[RPCServer] Unknown method requested: " << methodName << std::endl;
    }
}

