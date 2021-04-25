/*
  SPIFFS
  Library to abstract the persistency of data using SPIFFS

  Created April 24, 2021 May 2014
  by FSECanada

  This example code is in the public domain.

*/
#include "FSESPIFFSParams.h"
#include "FSESPIFFS.h"

FSESPIFFS _mySpiffs;
FSESPIFFSParams *p;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  // Wait for serial to initialize.
  while(!Serial) { }

  _mySpiffs.setConfigFile("/config.json");
  //_mySpiffs.cleanAll();
  _mySpiffs.readData(); // load data from SPIFFS if exists. this is required before start reading any data

  if (_mySpiffs.keyExists("A") == -1) { // checking if data exists
    //data does not exist. So, lets save some data
    Serial.println("data does not exist. Saving it");
    const char *k,*v;
    k = "A";
    v = "value_A";
      p = new FSESPIFFSParams(k /*key*/,v  /*key*/);
      _mySpiffs.addParam(p);
    k = "B";
    v = "value_B";
    p = new FSESPIFFSParams(k /*key*/,v  /*key*/);
    _mySpiffs.addParam(p);
    _mySpiffs.saveParams(); // saving data. Now it is available after reset the device until FSESPIFFS::cleanAll() is called
  } else {
    Serial.println("Data already exists");
  }
  Serial.println("Setup finished");
}

void loop() {
  Serial.print("Reading key A:");
  Serial.println(_mySpiffs.getByKey("A"));
  Serial.print("Reading key B:");
  Serial.println(_mySpiffs.getByKey("B"));
  delay(2000);
}
