#include <boost/asio.hpp>
#include <array>
#define PORT_NUM 1010


class client{
	public:
	boost::asio::ip::udp::socket socket;
	boost::asio::io_service ioService;
	boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("10.54.31.23"),PORT_NUM);
	float turretAngle;
	bool floorIntake;




	void init(){
		socket = new boost::asio::ip::udp::socket(io);
	}

	void sendAngle(){
		std::array<char,1> identifier = {'A'};
		std::array<float,1> rawBuffer = {turretAngle};
		socket.open(boost::asio::ip::udp::v4());
		socket.send_to(boost::asio::buffer(identifier), endpoint);
		socket.send_to(boost::asio::buffer(rawBuffer), endpoint);
	}

	void sendFloorIntake(){
		std::array<char,1> identifier = {'I'};
		std::array<bool,1> rawBuffer = {floorIntake};
		socket.open(boost::asio::ip::udp::v4());
		socket.send_to(boost::asio::buffer(rawBuffer), endpoint);
	}

	void sendTopIntake(){
	//	std::array<char,1> identifier = {'


	void updateVal();


