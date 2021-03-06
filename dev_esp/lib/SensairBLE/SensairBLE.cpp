/******************************************************************************/
/*        @TITLE : SensairBLE.cpp                                             */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 28, 2017                                               */
/* @MODIFICATION : dec 28, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "SensairBLE.h"

void CallbackValue::onRead(BLECharacteristic *pCharacteristic) {
	cout << "********** READ VALUE " << endl;
	gasValue = m_gasVal.get_gasValue();
	cJSON *gasJSON;
	gasJSON = cJSON_CreateObject();
	cJSON_AddNumberToObject(gasJSON, "CO",(float)gasValue.CO);
	cJSON_AddNumberToObject(gasJSON, "CO2",(float)gasValue.CO2);
	cJSON_AddNumberToObject(gasJSON, "NO2",(float)gasValue.NO2);
	cJSON_AddNumberToObject(gasJSON, "VOC",(float)gasValue.VOC);
	string gasStr(cJSON_Print(gasJSON));
	cJSON_Delete(gasJSON);
	pCharacteristic->setValue(gasStr);
}


void CallbackRawValue::onRead(BLECharacteristic *pCharacteristic) {
	cout << "********** READ RAW " << endl;
	gasRawValue = m_gasVal.get_gasRawValue();
	cJSON *gasJSON;
	gasJSON = cJSON_CreateObject();
	cJSON_AddNumberToObject(gasJSON, "CO",(float)gasRawValue.CO);
	cJSON_AddNumberToObject(gasJSON, "CO2",(float)gasRawValue.CO2);
	cJSON_AddNumberToObject(gasJSON, "NO2",(float)gasRawValue.NO2);
	cJSON_AddNumberToObject(gasJSON, "VOC",(float)gasRawValue.VOC);
	string gasStr(cJSON_Print(gasJSON));
	cJSON_Delete(gasJSON);
	pCharacteristic->setValue(gasStr);
}

void CallbackBattery::onRead(BLECharacteristic *pCharacteristic) {
	cout << "********** READ BATTERY " << endl;
	uint8_t batteryValue = m_batteryValue.get_batteryLevel();
	std::ostringstream os;
	os << batteryValue;
	pCharacteristic->setValue(os.str());
}


void CallbackBattery::onWrite(BLECharacteristic *pCharacteristic) {
	std::string value = pCharacteristic->getValue();
	if (value.length() > 0) {
	        cout << "*********" << endl;
	        cout << "WRITE " << value << endl;
	        cout << "*********" << endl;
	    }
	}


void CallbackRawValue::onWrite(BLECharacteristic *pCharacteristic) {
std::string value = pCharacteristic->getValue();
if (value.length() > 0) {
        cout << "*********" << endl;
        cout << "WRITE " << value << endl;
        cout << "*********" << endl;
    }
}

void CallbackValue::onWrite(BLECharacteristic *pCharacteristic) {
std::string value = pCharacteristic->getValue();
if (value.length() > 0) {
        cout << "*********" << endl;
        cout << "WRITE " << value << endl;
        cout << "*********" << endl;
    }
}


void CallbackWrite::onRead(BLECharacteristic *pCharacteristic) {
	cout << "********** READ TIME " << endl;
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	std::ostringstream os;
	os << "Time: " << tv.tv_sec;
	pCharacteristic->setValue(os.str());
}

void CallbackWrite::onWrite(BLECharacteristic *pCharacteristic) {
std::string value = pCharacteristic->getValue();
if (value.length() > 0) {
        cout << "*********" << endl;
        cout << "WRITE " << value << endl;
        cout << "*********" << endl;
    }
}


void MainBLEServer::run(void *data) {

	BLEDevice::init("SENSAIR");
	BLEServer* pServer = BLEDevice::createServer();
	pServer->setCallbacks(new MainBLEServerCallbacks());

	BLEService* pServiceValue = pServer->createService("91bad492-b950-4226-aa2b-4ede9fa42f59");

	BLECharacteristic* pCharacteristicValue = pServiceValue->createCharacteristic(
		BLEUUID("0d563a58-196a-48ce-ace2-dfec78acc814"),
		BLECharacteristic::PROPERTY_READ
	);
	pCharacteristicValue->setCallbacks(new CallbackValue(_gasValue));
	pCharacteristicValue->setValue("READ");

	BLECharacteristic* pCharacteristicRaw = pServiceValue->createCharacteristic(
		BLEUUID("01bf2093-f2d3-4fcc-8d2b-eda1667d96f4"),
		BLECharacteristic::PROPERTY_READ
	);
	pCharacteristicRaw->setCallbacks(new CallbackRawValue(_gasValue));
	pCharacteristicRaw->setValue("READ_RAW");
	pServiceValue->start();


	BLEService* pServiceWrite = pServer->createService("3978601c-634d-41c1-a33f-dbdd92b68dbf");
	BLECharacteristic* pCharacteristicWrite = pServiceWrite->createCharacteristic(
		BLEUUID("16ce95bb-8ce1-48ff-8043-680cb323324d"),
		BLECharacteristic::PROPERTY_WRITE
	);
	pCharacteristicWrite->setCallbacks(new CallbackWrite());
	pCharacteristicWrite->setValue("WRITE");
	pServiceWrite->start();

	BLEService* pServiceBattery = pServer->createService("db091a33-940e-4708-897d-6bff1650f275");
	BLECharacteristic* pCharacteristicBattery = pServiceBattery->createCharacteristic(
		BLEUUID("2e936fcd-702f-48d6-83bf-db32e57f7a8d"),
		BLECharacteristic::PROPERTY_READ
	);
	pCharacteristicBattery->setCallbacks(new CallbackBattery(_batteryValue));
	pCharacteristicBattery->setValue("BATTERY");
	pServiceBattery->start();


	BLEAdvertising* pAdvertising = pServer->getAdvertising();
	pAdvertising->addServiceUUID(BLEUUID(pServiceValue->getUUID()));
	pAdvertising->addServiceUUID(BLEUUID(pServiceWrite->getUUID()));
	pAdvertising->addServiceUUID(BLEUUID(pServiceBattery->getUUID()));
	pAdvertising->start();
	delay(1000000);
}


void MainBLEServerCallbacks::onConnect(BLEServer* pServer) {
	gpio_set_level(BLE_LED_GPIO, 1);
}

void MainBLEServerCallbacks::onDisconnect(BLEServer* pServer) {
	gpio_set_level(BLE_LED_GPIO, 0);
}

