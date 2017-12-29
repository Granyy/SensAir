/******************************************************************************/
/*        @TITLE : SensairBLE.h                                               */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 28, 2017                                               */
/* @MODIFICATION : dec 28, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#ifndef __SENSAIRBLE_H__

#define __SENSAIRBLE_H__

#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "GasValue.h"
#include <string>
#include <Task.h>
#include <sys/time.h>
#include <sstream>
#include <iostream>
#include "cJSON.h"

using namespace std;

class CallbackValue: public BLECharacteristicCallbacks {
public:
	CallbackValue(GasValue& gasVal) : m_gasVal(gasVal) {}
private:
    GasValue& m_gasVal;
    struct gas gasValue;
	void onRead(BLECharacteristic *pCharacteristic);
    void onWrite(BLECharacteristic *pCharacteristic);
};

class CallbackRawValue: public BLECharacteristicCallbacks {
public:
    CallbackRawValue(GasValue& gasVal) : m_gasVal(gasVal) {}
private:
    GasValue& m_gasVal;
    struct gasRaw gasRawValue;
	void onRead(BLECharacteristic *pCharacteristic);
    void onWrite(BLECharacteristic *pCharacteristic);
};

class CallbackWrite: public BLECharacteristicCallbacks {
	private :
		void onRead(BLECharacteristic *pCharacteristic);
		void onWrite(BLECharacteristic *pCharacteristic);
};


class MainBLEServer: public Task {
	void run(void *data);
};

#endif
