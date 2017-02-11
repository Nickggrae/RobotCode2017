
#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <thread>
#include <chrono>
#include <functional>
#include <iostream>

using boost::asio::ip::udp;
using namespace std;
using namespace rapidjson;

//extern boost::asio::io_service io_service;

//void startService();

class udp_server{
    public:
        udp_server():
            socket_(io_service,udp::endpoint(udp::v4(),25566)){
                start_recieve();
        }
        void setPressure(double paramPressure){pressure = paramPressure;}
        void setHighGear(bool paramHighGear){highGear = paramHighGear;}
        void setBottomIntake(bool paramBottomIntake){bottomIntake = paramBottomIntake;}
        void setStream(bool paramStream){stream = paramStream;}
        void setCrosshairOffset(double paramCrosshairOffset){crosshairOffset = paramCrosshairOffset;}
        void setTurretAngle(double paramTurretAngle){turretAngle = paramTurretAngle;}
        void setRPM(int paramRPM){RPM = paramRPM;}
        void setTopIntake(bool paramTopIntake){topIntake = paramTopIntake;}
        void setLeftRPM(int paramLeftRPM){leftRPM = paramLeftRPM;}
        void setRightRPM(int paramRightRPM){rightRPM = paramRightRPM;}
        void setHoldsGear(int paramHoldsGear){holdsGear = paramHoldsGear;}
        void setMode(int paramMode){mode = paramMode;}
        void setPowered(int paramPowered){powered = paramPowered;}
        void createJson(){
           StringBuffer message;
           Writer<StringBuffer> writer(message);
           writer.StartObject();
           writer.Key("pressure");
           writer.Double(pressure);
           writer.Key("highGear");
           writer.Bool(highGear);
           writer.Key("bottomIntake");
           writer.Bool(bottomIntake);
           writer.Key("stream");
           writer.Bool(stream);
           writer.Key("crosshairOffset");
           writer.Double(crosshairOffset);
           writer.Key("turretAngle");
           writer.Double(turretAngle);
           writer.Key("RPM");
           writer.Int(RPM);
           writer.Key("topIntake");
           writer.Bool(topIntake);
           writer.Key("leftRPM");
           writer.Int(leftRPM);
           writer.Key("rightRPM");
           writer.Int(rightRPM);
           writer.Key("holdsGear");
           writer.Bool(holdsGear);
           writer.Key("mode");
           writer.Int(mode);
           writer.Key("powered");
           writer.Bool(powered);
           writer.EndObject();
           finalString = message.GetString();
           }

        void serverInit(){
        	//boost::asio::io_service io = io_service;
        	//boost::thread serverThread(boost::bind(&udp_server::startService, this, io));
            //boost::thread serverThreadd(startService);
            //while(true){}
        	io_service.run();
        	//boost::thread serverThread(boost::bind(&boost::asio::io_service::run, &io_service));

        	//io_service.run();
        }
        void serverEnd(){
            serverThread.join();
        }
    private:
        boost::asio::io_service io_service;
        boost::thread serverThread;
        double pressure;
        bool highGear;
        bool bottomIntake;
        bool stream;
        double crosshairOffset;
        double turretAngle;
        int RPM;
        bool topIntake;
        int leftRPM;
        int rightRPM;
        bool holdsGear;
        int mode;
        bool powered;
        string finalString;
        rapidjson::Document document;
        void start_recieve(){
            cout<<"Waiting"<<endl;
            socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_),remote_endpoint,
            boost::bind(&udp_server::handle_recieve,this,
            boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
        }
        void handle_recieve(const boost::system::error_code& error,size_t){
            if(!error || error == boost::asio::error::message_size){
                boost::shared_ptr<string> message(new string (finalString));
                socket_.async_send_to(
                boost::asio::buffer(*message),remote_endpoint,
                boost::bind(&udp_server::handle_send,this,message,
                boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
                start_recieve();
            }
        }
        void handle_send(boost::shared_ptr<string>,
            const boost::system::error_code&, size_t){
        }

        udp::socket socket_;
        udp::endpoint remote_endpoint;
        array<char,1>recv_buffer_;
};

#endif
