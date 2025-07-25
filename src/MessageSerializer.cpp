#include "MessageSerializer.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <sstream>

using namespace Poco::JSON;
using namespace Poco::Dynamic;

std::string MessageSerializer::serializeRequest(const std::string& method, const std::vector<int>& params, int id) {
    Object::Ptr root = new Object;
    root->set("method", method);
    root->set("id", id);

    // Disambiguated Poco::JSON::Array
    Poco::JSON::Array::Ptr jsonArray = new Poco::JSON::Array;
    for (int val : params) {
        jsonArray->add(val);
    }

    root->set("params", jsonArray);

    std::stringstream ss;
    root->stringify(ss);
    return ss.str();
}

std::string MessageSerializer::serializeResponse(int result, int id) {
    Object::Ptr root = new Object;
    root->set("result", result);
    root->set("id", id);

    std::stringstream ss;
    root->stringify(ss);
    return ss.str();
}

bool MessageSerializer::deserializeRequest(const std::string& jsonStr, std::string& method, std::vector<int>& params, int& id) {
    try {
        Parser parser;
        Var result = parser.parse(jsonStr);
        Object::Ptr obj = result.extract<Object::Ptr>();

        method = obj->getValue<std::string>("method");
        id = obj->getValue<int>("id");

        // Disambiguated Poco::JSON::Array
        Poco::JSON::Array::Ptr jsonArray = obj->getArray("params");

        for (size_t i = 0; i < jsonArray->size(); ++i) {
            params.push_back(jsonArray->getElement<int>(i));
        }
        return true;
    } catch (...) {
        return false;
    }
}

bool MessageSerializer::deserializeResponse(const std::string& jsonStr, int& result, int& id) {
    try {
        Parser parser;
        Var parsed = parser.parse(jsonStr);
        Object::Ptr obj = parsed.extract<Object::Ptr>();

        result = obj->getValue<int>("result");
        id = obj->getValue<int>("id");
        return true;
    } catch (...) {
        return false;
    }
}

