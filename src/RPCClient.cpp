#include "RPCClient.h"
#include "MessageSerializer.h"

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <Poco/Timespan.h>

RPCClient::RPCClient(const std::string& address, int port)
    : _serverAddress(address, port), _socket(Poco::Net::DatagramSocket()) {
    _socket.connect(_serverAddress);
    _socket.setReceiveTimeout(Poco::Timespan(5, 0)); // 5 seconds timeout
    std::cout << "[Client] Connected to server at " << address << ":" << port << std::endl;
}

bool RPCClient::invokeRemoteMethod(const std::string& method,
                                   const std::vector<int>& params,
                                   int requestId,
                                   int& result) {
    std::string requestStr = MessageSerializer::serializeRequest(method, params, requestId);
    
    // Send request to the server
    try {
        _socket.sendBytes(requestStr.c_str(), requestStr.size());
        std::cout << "[Client] Sent request: " << requestStr << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "[Client] Error sending request: " << ex.what() << std::endl;
        return false;
    }

    // Receive response from server
    char buffer[1024];
    try {
        int n = _socket.receiveBytes(buffer, sizeof(buffer) - 1);
        buffer[n] = '\0';
        std::string responseStr(buffer);
        std::cout << "[Client] Received response: " << responseStr << std::endl;

        if (!MessageSerializer::deserializeResponse(responseStr, result, requestId)) {
            std::cerr << "[Client] Failed to parse server response." << std::endl;
            return false;
        }

        return true;
    } catch (const Poco::Exception& ex) {
        std::cerr << "[Client] Timeout or error receiving response: " << ex.displayText() << std::endl;
        return false;
    }
}

