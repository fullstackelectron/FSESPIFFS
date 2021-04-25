/*
 * FSECanadaSPIFFSParams.cpp
 *
 *  Created on: Apr. 18, 2021
 *      Author: jareas
 */

#include "FSESPIFFSParams.h"

FSESPIFFSParams::FSESPIFFSParams(const char *key, const char *value) {
	// TODO Auto-generated constructor stub
	_key = key;
	_value = value;
}

FSESPIFFSParams::~FSESPIFFSParams() {
	// TODO Auto-generated destructor stub
}


const char *FSESPIFFSParams::getValue(){
	return _value;
}
const char *FSESPIFFSParams::getKey(){
	return _key;
}
void FSESPIFFSParams::setValue(const char *value){
	_value = value;
}
void FSESPIFFSParams::setKey(const char *key){
	_key = key;
}
