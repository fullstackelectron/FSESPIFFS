/*
 * FSECanadaSPIFFS.cpp
 *
 *  Created on: Apr. 18, 2021
 *      Author: jareas
 */
#include "FSESPIFFS.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>

FSESPIFFS::FSESPIFFS() {
	_max_params = _params_bucket_size;
	_params = (FSESPIFFSParams**)malloc(_max_params * sizeof(FSESPIFFSParams*));
}

FSESPIFFS::FSESPIFFS(String file) {
	_file = file;
	_max_params = _params_bucket_size;
	_params = (FSESPIFFSParams**)malloc(_max_params * sizeof(FSESPIFFSParams*));
}

void FSESPIFFS::cleanAll() {
	if (SPIFFS.begin()) {
		if (SPIFFS.exists(_file)) {
			SPIFFS.remove(_file);
		}
		if (_params != NULL) {
			free(_params);
		}
		_max_params = _params_bucket_size;
		_paramsCount = 0;
		_params = (FSESPIFFSParams**)malloc(_max_params * sizeof(FSESPIFFSParams*));
	}
}

void FSESPIFFS::setConfigFile(String file) {
	_file = file;
	DEBUG_FSE_SPIFFS("File name is:");
	DEBUG_FSE_SPIFFS(_file.c_str());
}

void FSESPIFFS::readData() {
	StaticJsonDocument<500> _jsonDocument;
	if (SPIFFS.begin()) {
		DEBUG_FSE_SPIFFS("mounted file system");
		if (SPIFFS.exists(_file)) {
			DEBUG_FSE_SPIFFS("reading config file");
			File configFile = SPIFFS.open(_file, "r");
			if (configFile) {
				Serial.println("config file opened for read");
				size_t size = configFile.size();
				DeserializationError err = deserializeJson(_jsonDocument, configFile);
				if (!err) {
					JsonArray arr = _jsonDocument.as<JsonArray>();
					for (JsonVariant value : arr) {
						addParam(new FSESPIFFSParams(value["key"].as<char*>(), value["value"].as<char*>()));
					}
				} else {
					DEBUG_FSE_SPIFFS("failed to load json config with code:");
					DEBUG_FSE_SPIFFS(err.c_str());
				}
				configFile.close();
			} else {
				DEBUG_FSE_SPIFFS("Fail opening file for read");
			}
		}
	}
}

void FSESPIFFS::DEBUG_FSE_SPIFFS(const char *text, bool newLine){
	Serial.print("**FSESPIFFS: ");
	if (newLine) {
		Serial.println(text);
	} else {
		Serial.print(text);
	}
}

void FSESPIFFS::DEBUG_FSE_SPIFFS(const char *text){
	DEBUG_FSE_SPIFFS(text, true);
}

void FSESPIFFS::saveParams() {
	for (int i=0; i<_paramsCount; i++){
		_jsonDocument[i]["key"] = _params[i]->getKey();
		_jsonDocument[i]["value"] = _params[i]->getValue();
		DEBUG_FSE_SPIFFS(_jsonDocument[_params[i]->getKey()]);
	}

	if (SPIFFS.begin()){
		File configFile = SPIFFS.open(_file, "w");
		if (!configFile) {
			DEBUG_FSE_SPIFFS("failed to open config file for writing");
		  return;
		}

		DEBUG_FSE_SPIFFS("Writting...", false);

		// Serialize JSON to file
		if (serializeJson(_jsonDocument, configFile) == 0) {
			DEBUG_FSE_SPIFFS("Failed to write to file with code:");
		}

		configFile.close();

	} else {
		DEBUG_FSE_SPIFFS("Failed to open SPIFFS");

	}

	_jsonDocument.clear();
}

int FSESPIFFS::keyExists(const char *key) {
	for (int i=0; i<_paramsCount;i++) {
		if (strcmp(_params[i]->getKey(), key) == 0) {
			return i;
		} else {
		}
	}
	return -1;
}

void FSESPIFFS::addParam(FSESPIFFSParams *param) {
	int index = keyExists(param->getKey());
	if (index == -1) {
		if(_paramsCount + 1 > _max_params) {
			_max_params += PARAMS_BUCKET_SIZE; // allocating another bucket
			FSESPIFFSParams** new_params = (FSESPIFFSParams**)realloc(_params, _max_params * sizeof(FSESPIFFSParams*));
			if (new_params != NULL) {
			  _params = new_params;
			} else {
			  return;
			}
		}
		_params[_paramsCount] = param;
		_paramsCount++;
	} else {
		_params[index] = param;
	}
}

const char *FSESPIFFS::getByKey(const char* key) {
	int index = keyExists(key);
	if (index != -1) {
		return _params[index]->getValue();
	}
	return "";
}
