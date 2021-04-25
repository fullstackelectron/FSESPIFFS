/*
 * FSECanadaSPIFFSParams.h
 *
 *  Created on: Apr. 18, 2021
 *      Author: jareas
 */

#ifndef LIB_FSESPIFFS_SRC_FSESPIFFSPARAMS_H_
#define LIB_FSESPIFFS_SRC_FSESPIFFSPARAMS_H_
#include <ArduinoJson.h>

class FSESPIFFSParams {
public:
	FSESPIFFSParams(const char *key, const char *value);
	FSESPIFFSParams();
	virtual ~FSESPIFFSParams();
	const char *getValue();
	const char *getKey();
	void setValue(const char *value);
	void setKey(const char *key);
	const char *_key, *_value;
};

#endif /* LIB_FSESPIFFS_SRC_FSESPIFFSPARAMS_H_ */
