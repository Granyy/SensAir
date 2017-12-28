/******************************************************************************/
/*        @TITLE : SensairBLE.cpp                                             */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 28, 2017                                               */
/* @MODIFICATION : dec 28, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "SensairBLE.h"

void MyCallbackHandler::onRead(BLECharacteristic *pCharacteristic) {
	cout << "*********" << endl;
	cout << "   READ  " << endl;
	cout << "*********" << endl;
	gasValue = m_gasVal.get_gasValue();
	cJSON *gasJSON;
	gasJSON = cJSON_CreateObject();
	cJSON_AddNumberToObject(gasJSON, "CO",(float)gasValue.CO);
	cJSON_AddNumberToObject(gasJSON, "CO2",(float)gasValue.CO2);
	cJSON_AddNumberToObject(gasJSON, "NO2",(float)gasValue.NO2);
	cJSON_AddNumberToObject(gasJSON, "VOC",(float)gasValue.VOC);
	string gasStr(cJSON_Print(gasJSON));
	cJSON_Delete(gasJSON);
	cout << gasStr << endl;
	pCharacteristic->setValue(gasStr);
}

void MyCallbackHandler::onWrite(BLECharacteristic *pCharacteristic) {
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

	BLEService* pService = pServer->createService("91bad492-b950-4226-aa2b-4ede9fa42f59");

	BLECharacteristic* pCharacteristic = pService->createCharacteristic(
		BLEUUID("0d563a58-196a-48ce-ace2-dfec78acc814"),
		BLECharacteristic::PROPERTY_READ
	);

	
	GasValue* gasPtr = static_cast<GasValue*>(data);
	pCharacteristic->setCallbacks(new MyCallbackHandler(*gasPtr));
	pCharacteristic->setValue("READ");

	pService->start();

	BLEService* myService = pServer->createService("3978601c-634d-41c1-a33f-dbdd92b68dbf");

	BLECharacteristic* myCharacteristic = myService->createCharacteristic(
		BLEUUID("16ce95bb-8ce1-48ff-8043-680cb323324d"),
		BLECharacteristic::PROPERTY_WRITE
	);

	myCharacteristic->setCallbacks(new MyCallbackHandler2());
	myCharacteristic->setValue("WRITE");

	myService->start();

	BLEAdvertising* pAdvertising = pServer->getAdvertising();
	pAdvertising->addServiceUUID(BLEUUID(pService->getUUID()));
	pAdvertising->addServiceUUID(BLEUUID(myService->getUUID()));
	pAdvertising->start();
	delay(1000000);
}
