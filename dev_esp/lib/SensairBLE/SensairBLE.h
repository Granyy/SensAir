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
#include "BatteryValue.h"
#include <string>
#include <Task.h>
#include <sys/time.h>
#include <sstream>
#include <iostream>
#include "cJSON.h"
#include "Configuration.h"


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
	void onRead(BLECharacteristic *pCharacteristic) override;
    void onWrite(BLECharacteristic *pCharacteristic);
};

class CallbackBattery: public BLECharacteristicCallbacks {
public:
	CallbackBattery(BatteryValue& _batteryValue) : m_batteryValue(_batteryValue) {}
private:
    BatteryValue& m_batteryValue;
	void onRead(BLECharacteristic *pCharacteristic);
    void onWrite(BLECharacteristic *pCharacteristic);
};

class CallbackWrite: public BLECharacteristicCallbacks {
	private :
		void onRead(BLECharacteristic *pCharacteristic);
		void onWrite(BLECharacteristic *pCharacteristic);
};


class MainBLEServer: public Task {
private:
	GasValue &_gasValue;
	BatteryValue &_batteryValue;
public:
	MainBLEServer(GasValue &gasValue, BatteryValue &batteryValue):_gasValue(gasValue),_batteryValue(batteryValue) {};
	void run(void *data);

};


class MainBLEServerCallbacks: public BLEServerCallbacks  {
	void onConnect(BLEServer* pServer);
	void onDisconnect(BLEServer* pServer);
};

#endif
