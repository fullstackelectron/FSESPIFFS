/*
 * FSECanadaSPIFFS.h
 *
 *  Created on: Apr. 18, 2021
 *      Author: jareas
 */
#include <FS.h>
#include "FSESPIFFSParams.h"

#ifndef LIB_FSECSPIFFS_SRC_FSESPIFFS_H_
#define LIB_FSECSPIFFS_SRC_FSESPIFFS_H_
#define PARAMS_BUCKET_SIZE 10
class FSESPIFFS {
public:
	FSESPIFFS();
	FSESPIFFS(String file);
	bool addParam(FSESPIFFSParams param);
	void cleanAll();
	void setConfigFile(String file);
	void saveParams();
	void addParam(FSESPIFFSParams *param);
	void readData();
	const char *getByKey(const char* key);
	int keyExists(const char *key);
private:
	int _params_bucket_size=10;
	StaticJsonDocument<500> _jsonDocument;
	int _paramsCount = 0;
	FSESPIFFSParams** _params;
	int _max_params;
	String _file;
	void DEBUG_FSE_SPIFFS(const char *text);
	void DEBUG_FSE_SPIFFS(const char *text, bool newLine);
};

#endif /* LIB_FSECSPIFFS_SRC_FSESPIFFS_H_ */
