#include <Engine/Core.h>
#include <Server/Level.h>

namespace Server {

	class Server : public Engine::Core {









	};
}


int main() {

	Server::Server server;

	Server::Level* level = new Server::Level();
	server.setScene(level);


	server.runHeadless();

	return -1;
}