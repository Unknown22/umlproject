#include <string>

using namespace std;

class MultiplayerNetwork
{
private:
	int id;
public:
	MultiplayerNetwork();
	void send_keyboard();
	void send_position();
	void receive_keyboard();
	void receive_position();
};