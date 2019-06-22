#pragma once
#include <SFML/Network.hpp>

// There is no central server, all connections are Peer to Peer

class NetworkController {

private:
	sf::UdpSocket socket;
};