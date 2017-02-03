#include "Shared.h"
#include "Copernicus.h"

std::shared_ptr<NetworkTable> Copernicus::table = nullptr;

void Copernicus::createTable(){
	table = NetworkTable::GetTable("copernicus");
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
