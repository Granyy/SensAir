/******************************************************************************/
/*        @TITLE : MicsGasSensor.cpp                                          */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 10, 2017                                               */
/* @MODIFICATION : dec 10, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "MicsGasSensor.h"


MicsGasSensor::MicsGasSensor() {
    _i2caddr = MICS_VZ_89TE_ADDR;
    co2 = 0.0;
    voc = 0.0;
}

float MicsGasSensor::get_CO2() {
    return co2;
}

float MicsGasSensor::get_VOC() {
    return voc;
}

float MicsGasSensor::get_year() {
    return year;
}

float MicsGasSensor::get_month() {
    return month;
}

float MicsGasSensor::get_day() {
    return day;
}

float MicsGasSensor::get_rev() {
    return rev;
}

float MicsGasSensor::get_crc() {
    return crc;
}

float MicsGasSensor::get_status() {
    return status;
}

void MicsGasSensor::read_sensor() {
    static uint8_t data[7];
    read_data(MICS_VZ_89TE_ADDR, MICS_VZ_89TE_ADDR_CMD_GETSTATUS, data);
    
    status = data[5];
    
    co2 = (data[1] - 13) * (1600.0 / 229) + 400;
    voc = (data[0] - 13) * (1000.0/229);

}

void MicsGasSensor::get_version() {
    static uint8_t data[7];
    read_data(MICS_VZ_89TE_ADDR, MICS_VZ_89TE_DATE_CODE, data);
    
    year = data[0];
    month = data[1];
    day = data[2];
    rev = data[3];
    crc = data[6];
}


void MicsGasSensor::read_data(uint8_t addrDev, uint8_t addrReg, uint8_t data[]) {
	int ret;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_VAL);
	i2c_master_write_byte(cmd, MICS_VZ_89TE_ADDR_CMD_GETSTATUS, ACK_VAL);
	i2c_master_write_byte(cmd, 0x00, ACK_VAL);
	i2c_master_write_byte(cmd, 0x00, ACK_VAL);
	i2c_master_write_byte(cmd, 0x00, ACK_VAL);
	i2c_master_write_byte(cmd, 0x00, ACK_VAL);
	i2c_master_write_byte(cmd, 0x00, ACK_VAL);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c write" << endl;
    }
	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_READ, ACK_VAL);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c write" << endl;
    }
	i2c_cmd_link_delete(cmd);
	
    vTaskDelay(100 / portTICK_RATE_MS);

    cmd = i2c_cmd_link_create();
   	i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addrDev << 1)| I2C_MASTER_READ, ACK_VAL);
	i2c_master_read_byte(cmd, &data[0], ACK_VAL);
	i2c_master_read_byte(cmd, &data[1], ACK_VAL);
	i2c_master_read_byte(cmd, &data[2], ACK_VAL);
	i2c_master_read_byte(cmd, &data[3], ACK_VAL);
	i2c_master_read_byte(cmd, &data[4], ACK_VAL);
	i2c_master_read_byte(cmd, &data[5], ACK_VAL);
	i2c_master_read_byte(cmd, &data[6], NACK_VAL);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000/portTICK_PERIOD_MS);
	if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c read" << endl;
    }
	i2c_cmd_link_delete(cmd);
}

MicsGasSensor mics;