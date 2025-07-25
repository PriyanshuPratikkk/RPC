#include "RPCServer.h"
#include <iostream>

int addFunction(const std::vector<int>& params, int requestId) {
    int sum = 0;
    for (int val : params) sum += val;
    std::cout << "[Server] Processed 'add' for ID " << requestId << ", result = " << sum << std::endl;
    return sum;
}

int multiplyFunction(const std::vector<int>& params, int requestId) {
    int product = 1;
    for (int val : params) product *= val;
    std::cout << "[Server] Processed 'multiply' for ID " << requestId << ", result = " << product << std::endl;
    return product;
}

int main() {
    RPCServer server("127.0.0.1", 9999);
    server.registerMethod("add", addFunction);
    server.registerMethod("multiply", multiplyFunction);

    std::cout << "[Server] Waiting for RPC requests..." << std::endl;
    server.start();

    return 0;
}

