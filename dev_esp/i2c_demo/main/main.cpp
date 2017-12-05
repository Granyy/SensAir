#include <esp_log.h>
#include <FreeRTOS.h>
#include <string>
#include <Task.h>
#include <I2C.h>
#include <iostream>
#include "sdkconfig.h"
#include <math.h>

#define SDA_PIN 22
#define SCL_PIN 26

#define ADDR_GROVE    0x04

#define ADDR_IS_SET             0           // if this is the first time to run, if 1126, set 
#define ADDR_FACTORY_ADC_NH3    2
#define ADDR_FACTORY_ADC_CO     4
#define ADDR_FACTORY_ADC_NO2    6

#define ADDR_USER_ADC_HN3       8
#define ADDR_USER_ADC_CO        10
#define ADDR_USER_ADC_NO2       12
#define ADDR_IF_CALI            14          // IF USER HAD CALI

#define ADDR_I2C_ADDRESS        20

#define CH_VALUE_NH3            1
#define CH_VALUE_CO             2
#define CH_VALUE_NO2            3

#define CMD_ADC_RES0            1           // NH3
#define CMD_ADC_RES1            2           // CO
#define CMD_ADC_RES2            3           // NO2
#define CMD_ADC_RESALL          4           // ALL CHANNEL
#define CMD_CHANGE_I2C          5           // CHANGE I2C
#define CMD_READ_EEPROM         6           // READ EEPROM VALUE, RETURN UNSIGNED INT
#define CMD_SET_R0_ADC          7           // SET R0 ADC VALUE
#define CMD_GET_R0_ADC          8           // GET R0 ADC VALUE
#define CMD_GET_R0_ADC_FACTORY  9           // GET FACTORY R0 ADC VALUE
#define CMD_CONTROL_LED         10
#define CMD_CONTROL_PWR         11
#define ACK_CHECK_EN                       0x1              /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS                      0x0              /*!< I2C master will not check ack from slave */
#define ACK_VAL                            0x0              /*!< I2C ack value */
#define NACK_VAL                           0x1  

using namespace std;

extern "C" {
   void app_main();
}



void I2C_config() {
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = (gpio_num_t)SDA_PIN;
	conf.scl_io_num = (gpio_num_t)SCL_PIN;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 100000;
	i2c_param_config(I2C_NUM_0, &conf);
	i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
}


uint16_t I2C_read_2_bytes(uint8_t addrDev, uint8_t addrReg) {
	unsigned char byte1;
	unsigned char byte2;
	int value;
	int ret;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, addrReg, ACK_CHECK_EN);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "Problem i2c write" << endl;
    }
    vTaskDelay(30 / portTICK_RATE_MS);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addrDev << 1)| I2C_MASTER_READ, ACK_CHECK_EN);
	i2c_master_read_byte(cmd, &byte1, ACK_VAL);
	i2c_master_read_byte(cmd, &byte2, NACK_VAL);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000/portTICK_PERIOD_MS);
	if (ret != ESP_OK) {
        	cout << "Problem i2c read" << endl;
    }
	i2c_cmd_link_delete(cmd);
	cout << (int)byte1 << " " <<(int)byte2 << endl;
	value = (byte1 << 8) + (byte2);
	cout << "Value: " << value << endl;
	return value;
}

uint16_t I2C_read_2_bytes_data(uint8_t addrDev, uint8_t addrReg, uint8_t addrDta) {
	unsigned char byte1;
	unsigned char byte2;
	int value;
	int ret;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, addrReg, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, addrDta, ACK_CHECK_EN);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "Problem i2c write" << endl;
    }
    vTaskDelay(30 / portTICK_RATE_MS);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addrDev << 1)| I2C_MASTER_READ, ACK_CHECK_EN);
	i2c_master_read_byte(cmd, &byte1, ACK_VAL);
	i2c_master_read_byte(cmd, &byte2, NACK_VAL);
	i2c_master_stop(cmd);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000/portTICK_PERIOD_MS);
	if (ret != ESP_OK) {
        	cout << "Problem i2c read" << endl;
    }
	i2c_cmd_link_delete(cmd);
	cout << (int)byte1 << " " <<(int)byte2 << endl;
	value = (byte1 << 8) + (byte2);
	cout << "Value (data): " << value << endl;
	return value;
}


void I2C_write(uint8_t addrDev, uint8_t addrReg, uint8_t data) {
	int ret;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, addrReg, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, data, ACK_CHECK_EN);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "Problem i2c write" << endl;
    }
}

void I2C_demo() {
	int value, value2;
	float ratio, c;
	I2C_config();
	value = I2C_read_2_bytes_data(ADDR_GROVE, CMD_READ_EEPROM, ADDR_IS_SET);
	cout << "Version " << value << endl;
	
	while (1) {
		
		value = I2C_read_2_bytes(ADDR_GROVE, CH_VALUE_CO);
		value2 = I2C_read_2_bytes_data(ADDR_GROVE, CMD_READ_EEPROM, ADDR_FACTORY_ADC_CO);
		
		ratio = (float)value/(float)value2*(1023.0-value2)/(1023.0-value);
		cout << "ratio: " << ratio << endl;
		c = pow(ratio, -1.179)*4.385;
		cout << "CO (ppm): " << c << endl;
		vTaskDelay(2000/ portTICK_RATE_MS);
		I2C_write(ADDR_GROVE,CMD_CONTROL_LED,0x00);
		value = I2C_read_2_bytes(ADDR_GROVE, CH_VALUE_CO);
		value2 = I2C_read_2_bytes_data(ADDR_GROVE, CMD_READ_EEPROM, ADDR_FACTORY_ADC_CO);
		
		ratio = (float)value/(float)value2*(1023.0-value2)/(1023.0-value);
		cout << "Ratio: " << ratio << endl;
		c = pow(ratio, -1.007)/6.855;
		cout << "NO2 (ppm): " << c << endl;
		vTaskDelay(2000/ portTICK_RATE_MS);
		I2C_write(ADDR_GROVE,CMD_CONTROL_LED,0x01);
	}
}

void app_main(void)
{
	I2C_demo();
} // app_main
