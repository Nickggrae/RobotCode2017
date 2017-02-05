#include "Shared.h"
#include "Copernicus.h"

#ifdef COPERNICUS_USE_TABLES
//DEFINING THE FRONT END
void Copernicus::setPressure(const double psi){//you may not know me, but my name's psi. im just the o'hare delivery guy
	setNumber("pressure", psi);
}

void Copernicus::setHighGear(const bool gear){
	setBool("highGear", gear);
}

void Copernicus::setFloorIntake(const bool floorIntake){
	setBool("floorIntake", floorIntake);
}

void Copernicus::setStream(const bool stream){
	setBool("stream", stream);
}

void Copernicus::setCrosshairOffset(const double offset){
	setNumber("crosshairOffset", offset);
}

void Copernicus::setTurretAngle(const double radians){
	setNumber("turretAngle", radians);
}

void Copernicus::setFlywheelRPM(const int rpm){
	setNumber("flywheelRPM", static_cast<double>(rpm));
}

void Copernicus::setTargetRPM(const int rpm){
	setNumber("targetRPM", static_cast<double>(rpm));
}

void Copernicus::setTopIntake(const bool intaking){
	setBool("topIntake", intaking);
}

void Copernicus::setLeftRPM(const int rpm){
	setNumber("leftRPM", static_cast<double>(rpm));
}

void Copernicus::setRightRPM(const int rpm){
	setNumber("rightRPM", static_cast<double>(rpm));
}

void Copernicus::setHasGear(const bool gear){
	setBool("holdsGear", gear);
}

void Copernicus::setMode(const Copernicus::Mode mode){
	setNumber("mode", static_cast<int>(mode));
}

void Copernicus::update(){
	setBool("powered", true);
}

//IMPLEMENTATION
std::shared_ptr<NetworkTable> Copernicus::table = nullptr;

void Copernicus::createTable(){
	table = NetworkTable::GetTable("copernicus");//ayy copernicus
}

void Copernicus::setBool(const char* key, const bool val){
	if(table == nullptr){
		createTable();
	}

	table->PutBoolean(key, val);
}

void Copernicus::setNumber(const char* key, const double val){
	if(table == nullptr){
		createTable();
	}

	table->PutNumber(key, val);
}

void Copernicus::setString(const char* key, const char* val){
	if(table == nullptr){
		createTable();
	}

	table->PutString(key, val);
}
#elif defined(COPERNICUS_USE_UDP)
std::unique_ptr<udp_server> Copernicus::server = nullptr;

void Copernicus::createTable(){
	udp_server server;
	server.setBottomIntake(false);
	server.setCrosshairOffset(0);
	server.setHighGear(false);
	server.setHoldsGear(false);
	server.setLeftRPM(0);
	server.setMode(0);
	server.setPowered(false);
	server.setPressure(0);
	server.setRPM(0);
	server.setRightRPM(0);
	server.setStream(false);
	server.setTopIntake(false);
	server.setTurretAngle(0);
	server.createJson();
	server.serverInit();
}

#endif
