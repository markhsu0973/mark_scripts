#include <net/socket.hpp>
#include <iostream>

int main() {
    net::socket server(net::socket::ipv4, net::socket::stream);
    unsigned port = 3667;
    server.bind("127.0.0.1", port);
    server.listen(port);
    std::cout << "Waiting for a client..\n";
    auto client = server.accept();
    std::cout << "Client connected\n";
    client.send("Hello World!\n");
}
