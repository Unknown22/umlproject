#include <string>

using namespace std;

class MultiplayerNetwork
{
private:
	MultiplayerNetwork(int id);
	int id;
public:
	void send_keyboard();
	void send_position();
	void receive_keyboard();
	void receive_position();
};