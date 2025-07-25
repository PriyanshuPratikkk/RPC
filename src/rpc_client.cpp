#include "RPCClient.h"
#include <iostream>

int main() {
    RPCClient client("127.0.0.1", 9999);
    std::vector<int> params = {2, 3, 4};
    int result;

    if (client.invokeRemoteMethod("add", params, 1, result)) {
        std::cout << "[Client] Result of add: " << result << std::endl;
    } else {
        std::cout << "[Client] Failed to invoke 'add'" << std::endl;
    }

    if (client.invokeRemoteMethod("multiply", params, 2, result)) {
        std::cout << "[Client] Result of multiply: " << result << std::endl;
    } else {
        std::cout << "[Client] Failed to invoke 'multiply'" << std::endl;
    }

    return 0;
}
