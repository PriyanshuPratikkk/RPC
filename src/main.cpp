#include "RPCServer.h"
#include <iostream>

/**
 * A sample function that will be registered and invoked remotely.
 * It sums all integers in the `params` vector.
 */
int addFunction(const std::vector<int>& params, int requestId) {
    int sum = 0;
    for (int val : params) {
        sum += val;
    }
    std::cout << "[Server] Processed 'add' for ID " << requestId << ", result = " << sum << std::endl;
    return sum;
}

int multiplyFunction(const std::vector<int>& params, int requestId) {
    int product = 1;
    for (int val : params) {
        product *= val;
    }
    std::cout << "[Server] Processed 'multiply' for ID " << requestId << ", result = " << product << std::endl;
    return product;
}

int main() {
    // Initialize server on localhost and port 9999
    RPCServer server("127.0.0.1", 9999);

    // Register remote methods
    server.registerMethod("add", addFunction);
    server.registerMethod("multiply", multiplyFunction);

    std::cout << "[Server] Waiting for RPC requests..." << std::endl;

    // Start the server loop
    server.start();

    return 0;
}

