#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <vector>
#include <string>

class RPCClient {
public:
    RPCClient(const std::string& address, int port);
    
    bool invokeRemoteMethod(const std::string& method,
                            const std::vector<int>& params,
                            int requestId,
                            int& result);

private:
    Poco::Net::SocketAddress _serverAddress;
    Poco::Net::DatagramSocket _socket;
};

#endif // RPCCLIENT_H

