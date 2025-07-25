#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>

/**
 * RPCServer listens for JSON-based UDP messages,
 * deserializes incoming requests, invokes registered methods,
 * and sends JSON responses.
 */
class RPCServer {
public:
    // Constructor initializes the server with address and port
    RPCServer(const std::string& address, int port);

    // Register a method that takes (vector<int>, requestId) and returns an int
    void registerMethod(const std::string& name, std::function<int(std::vector<int>, int)> func);

    // Starts listening for and processing incoming requests
    void start();

private:
    void processRequest(const std::string& requestStr, Poco::Net::SocketAddress& clientAddr);

    Poco::Net::SocketAddress _address;
    Poco::Net::DatagramSocket _socket;
    std::unordered_map<std::string, std::function<int(std::vector<int>, int)>> _methods;
};

