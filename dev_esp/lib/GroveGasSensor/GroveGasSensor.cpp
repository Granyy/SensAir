/******************************************************************************/
/*        @TITLE : GroveGasSensor.cpp                                         */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 10, 2017                                               */
/* @MODIFICATION : dec 10, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                 */
/******************************************************************************/

#include "GroveGasSensor.h"

uint16_t GroveGasSensor::get_addr_dta(uint8_t addrDev, uint8_t addrReg) {
    uint8_t byte1, byte2;
	uint16_t value;
	int ret;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_VAL);
	i2c_master_write_byte(cmd, addrReg, ACK_VAL);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c write" << endl;
    }
    vTaskDelay(30 / portTICK_RATE_MS);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addrDev << 1)| I2C_MASTER_READ, ACK_VAL);
	i2c_master_read_byte(cmd, &byte1, ACK_VAL);
	i2c_master_read_byte(cmd, &byte2, NACK_VAL);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000/portTICK_PERIOD_MS);
	if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c read" << endl;
    }
	i2c_cmd_link_delete(cmd);
	value = (byte1 << 8) + (byte2);
	return value;
}


uint16_t GroveGasSensor::get_addr_dta(uint8_t addrDev, uint8_t addrReg, uint8_t addrDta) {
	uint8_t byte1, byte2;
	uint16_t value;
	int ret;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_VAL);
	i2c_master_write_byte(cmd, addrReg, ACK_VAL);
	i2c_master_write_byte(cmd, addrDta, ACK_VAL);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c write" << endl;
    }
    vTaskDelay(30 / portTICK_RATE_MS);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addrDev << 1)| I2C_MASTER_READ, ACK_VAL);
	i2c_master_read_byte(cmd, &byte1, ACK_VAL);
	i2c_master_read_byte(cmd, &byte2, NACK_VAL);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000/portTICK_PERIOD_MS);
	if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c read" << endl;
    }
	i2c_cmd_link_delete(cmd);
	value = (byte1 << 8) + (byte2);
	return value;
}

void GroveGasSensor::write_i2c(uint8_t addrDev, uint8_t addrReg, uint8_t data) {
    int ret;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_VAL);
	i2c_master_write_byte(cmd, addrReg, ACK_VAL);
	i2c_master_write_byte(cmd, data, ACK_VAL);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c write" << endl;
    }
}

void GroveGasSensor::write_i2c(uint8_t addrDev, uint8_t* data) {
    int ret;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_VAL);
    for (int i=0; i<sizeof(data); i++) {
        i2c_master_write_byte(cmd, data[i], ACK_VAL);
    }
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "[ERROR " << hex << ret << dec << "] i2c write" << endl;
    }
}


float GroveGasSensor::calc_gas(int gas)
{    
    
    float c = -1;

    switch(gas)
    {
        case CO:
        {   
            int A0_1 = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_CO);
            int An_1 = get_addr_dta(DEFAULT_I2C_ADDR, CH_VALUE_CO);
            float ratio1 = (float)An_1/(float)A0_1*(1023.0-A0_1)/(1023.0-An_1);
            c = pow(ratio1, -1.179)*4.385;
            break;
        }
        case NO2:
        {   
            int A0_2 = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_NO2);
            int An_2 = get_addr_dta(DEFAULT_I2C_ADDR, CH_VALUE_NO2);
            float ratio2 = (float)An_2/(float)A0_2*(1023.0-A0_2)/(1023.0-An_2);
            c = pow(ratio2, 1.007)/6.855; 
            break;
        }
        case NH3:
        {
            int A0_0 = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_HN3);
            int An_0 = get_addr_dta(DEFAULT_I2C_ADDR, CH_VALUE_NH3);
            float ratio0 = (float)An_0/(float)A0_0*(1023.0-A0_0)/(1023.0-An_0);
            c = pow(ratio0, -1.67)/1.47;
            break;
        }
        default:
            break;
    }
    return isnan(c)?-1:c;
}




void GroveGasSensor::power_on() {
    write_i2c(DEFAULT_I2C_ADDR,CMD_CONTROL_PWR,0x01);
}

void GroveGasSensor::power_off() {
    write_i2c(DEFAULT_I2C_ADDR,CMD_CONTROL_PWR,0x00);
}




float GroveGasSensor::get_R0(int gas) { 
    int a = 0;
    switch(gas)
    {
        case NH3:         
        a = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_HN3);
        break;
        
        case CO:         
        a = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_CO);
        break;
        
        case NO2: 
        a = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_NO2);
        break;
        
        default:;
    }

    float r = 56.0*(float)a/(1023.0-(float)a);
    return r;
}


float GroveGasSensor::get_Rs(int gas) {
    
    int a = 0;
    switch(gas)
    {
        case NH3:        
        a = get_addr_dta(DEFAULT_I2C_ADDR, CH_VALUE_NH3);
        break;
        
        case CO:      
        a = get_addr_dta(DEFAULT_I2C_ADDR, CH_VALUE_CO);
        break;
        
        case NO2:      
        a = get_addr_dta(DEFAULT_I2C_ADDR, CH_VALUE_NO2);
        break;
        
        default:;
    }
    
    float r = 56.0*(float)a/(1023.0-(float)a);
    return r;
}




void GroveGasSensor::led_on() {
    write_i2c(DEFAULT_I2C_ADDR,CMD_CONTROL_LED,0x00);
}   

void GroveGasSensor::led_off() {
    write_i2c(DEFAULT_I2C_ADDR,CMD_CONTROL_LED,0x01);
}




void GroveGasSensor::display_eeprom()
{   
    cout << "ADDR_IS_SET = " << get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_IS_SET) << endl;
    cout << "ADDR_FACTORY_ADC_NH3 = " << get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_FACTORY_ADC_NH3) << endl;
    cout << "ADDR_FACTORY_ADC_CO = " << get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_FACTORY_ADC_CO) << endl;
    cout << "ADDR_FACTORY_ADC_NO2 = " << get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_FACTORY_ADC_NO2) << endl;
    cout << "ADDR_USER_ADC_HN3 = " << get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_HN3) << endl;
    cout << "ADDR_USER_ADC_CO = " << get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_CO) << endl;
    cout << "ADDR_USER_ADC_NO2 = " << get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_USER_ADC_NO2)  << endl;
    cout << "ADDR_I2C_ADDRESS = " << get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_I2C_ADDRESS) << endl;
}

void GroveGasSensor::factory_setting()
{
    uint8_t tmp[7];

    uint16_t a0 = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_FACTORY_ADC_NH3);
    uint16_t a1 = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_FACTORY_ADC_CO);
    uint16_t a2 = get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_FACTORY_ADC_NO2);
    
    tmp[0] = 7;
    tmp[1] = a0>>8;
    tmp[2] = a0&0xff;     
    tmp[3] = a1>>8;
    tmp[4] = a1&0xff;

    tmp[5] = a2>>8;
    tmp[6] = a2&0xff;   
    vTaskDelay(100/ portTICK_RATE_MS);
    write_i2c(DEFAULT_I2C_ADDR, tmp);
    vTaskDelay(100/ portTICK_RATE_MS);
}

uint8_t GroveGasSensor::get_version()
{
    if(get_addr_dta(DEFAULT_I2C_ADDR, CMD_READ_EEPROM, ADDR_IS_SET) == 1126) 
    {
        __version = 2;
        cout << "version = 2" << endl;
        return 2;
    }
    else {
         __version = 1;
        cout << "version = 1" << endl;
        cout << "WARNING - ALL FUNCTIONNALITIES MAY NOT BE SUPPORTED" << endl;
        return 1;
    }
}