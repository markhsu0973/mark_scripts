#include <net/socket.hpp>
#include <iostream>

int main() {
    net::socket client(net::socket::ipv4, net::socket::stream);
    client.connect("127.0.0.1", 3667);
    std::cout << client.receive(16);
}