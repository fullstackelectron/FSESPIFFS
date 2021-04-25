**Introduction**

Simplified way to save data to your ESP8266 device using SPIFFS. 

**Dependencies**
This module uses `bblanchon/ArduinoJson` which is a rich featured library to handle Json objects. This module uses a single rooted Json object with key=>value structure to save the data. 
**Methods**

* setConfigFile(String)
	
Tell the class which file to use to save the data

     * param -> The full path for the file to hold the configurations (.ie "/config.json")
     * return -> void
     
     _mySpiffs.setConfigFile("/config.json");
  
* addParam(FSESPIFFSParams)

Add a new param to the queue of params
	
     * param -> An instance of FSESPIFFSParams
     * return -> void
     
		p = new FSESPIFFSParams("A" /*key*/,"B"  /*key*/);
		_mySpiffs.addParam(p);

* saveParams(void)

Save all data added to the given json file. The data will be kept in memory until the device resets

		* params -> void
		* return -> void
		
* readData(void);

Will load the json file and read the values to memory. It is required 

		* params -> void
		* return -> void

* getByKey (const char*)

Will read the params saved in memory and return the value stored for the given key

		*param -> the key to retrieve the value
		* return -> the value stored for the key or blank

* cleanAll(void)

will clean the memory remove saved data

**Example**


```
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

```
