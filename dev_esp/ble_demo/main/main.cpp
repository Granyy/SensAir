/**
 * Create a new BLE server with write/read characteristic.
 */

#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include <esp_log.h>
#include <string>
#include <Task.h>
#include <sys/time.h>
#include <sstream>
#include "sdkconfig.h"
#include <iostream>

using namespace std;



extern "C" {
   void app_main();
}



class MyCallbackHandler: public BLECharacteristicCallbacks {
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

static char LOG_TAG[] = "SampleServer";

class MainBLEServer: public Task {
	void run(void *data) {

		BLEDevice::init("SENSAIR");
		BLEServer* pServer = BLEDevice::createServer();

		BLEService* pService = pServer->createService("91bad492-b950-4226-aa2b-4ede9fa42f59");

		BLECharacteristic* pCharacteristic = pService->createCharacteristic(
			BLEUUID("0d563a58-196a-48ce-ace2-dfec78acc814"),
			BLECharacteristic::PROPERTY_BROADCAST | BLECharacteristic::PROPERTY_READ  |
			BLECharacteristic::PROPERTY_NOTIFY    | BLECharacteristic::PROPERTY_WRITE |
			BLECharacteristic::PROPERTY_INDICATE
		);

        
	    pCharacteristic->setCallbacks(new MyCallbackHandler());
		pCharacteristic->setValue("Hello World!");

		pService->start();

		BLEAdvertising* pAdvertising = pServer->getAdvertising();
		pAdvertising->addServiceUUID(BLEUUID(pService->getUUID()));
		pAdvertising->start();
		delay(1000000);
	}
};


void run(void) {
	MainBLEServer* pMainBleServer = new MainBLEServer();
	pMainBleServer->setStackSize(20000);
	pMainBleServer->start();

} 

void app_main(void)
{
	run();
} // app_main
