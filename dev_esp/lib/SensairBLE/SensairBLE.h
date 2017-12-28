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
#include "GasTreatment.h"
#include <esp_log.h>
#include <string>
#include <Task.h>
#include <sys/time.h>
#include <sstream>
#include "sdkconfig.h"
#include <iostream>

using namespace std;

class MyCallbackHandler: public BLECharacteristicCallbacks {
public:
    MyCallbackHandler(struct gas& gasVal) : m_gasVal(gasVal) {}
private:
    struct gas& m_gasVal;
	void onRead(BLECharacteristic *pCharacteristic);
    void onWrite(BLECharacteristic *pCharacteristic);
};

class MyCallbackHandler2: public BLECharacteristicCallbacks {
	void onRead(BLECharacteristic *pCharacteristic) {
        cout << "*********" << endl;
        cout << "   READ  " << endl;
        cout << "*********" << endl;
		struct timeval tv;
		gettimeofday(&tv, nullptr);
		std::ostringstream os;
		os << "Time: " << tv.tv_sec;
		pCharacteristic->setValue(os.str());
	}

    void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
            cout << "*********" << endl;
            cout << "WRITE " << value << endl;
            cout << "*********" << endl;
        }
    }
};


class MainBLEServer: public Task {
	void run(void *data);
};

#endif
