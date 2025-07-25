#pragma once

#include <string>
#include <vector>

/**
 * MessageSerializer handles encoding and decoding of RPC requests and responses
 * using JSON format via the POCO JSON library.
 */
class MessageSerializer {
public:
    // Serialize a method call request with method name, params, and ID
    static std::string serializeRequest(const std::string& method, const std::vector<int>& params, int id);

    // Serialize a method response with result and ID
    static std::string serializeResponse(int result, int id);

    // Deserialize a JSON request string into method, params, and ID
    static bool deserializeRequest(const std::string& jsonStr, std::string& method, std::vector<int>& params, int& id);

    // Deserialize a JSON response string into result and ID
    static bool deserializeResponse(const std::string& jsonStr, int& result, int& id);
};

