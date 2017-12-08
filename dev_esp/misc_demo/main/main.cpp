#include <esp_log.h>
#include <string>
#include <iostream>
#include "sdkconfig.h"
#include <math.h>
#include "driver/i2c.h"
#include <cstring>

#define SDA_PIN 22
#define SCL_PIN 21
#define MICS_VZ_89TE_ADDR      0x70 
#define MICS_VZ_89TE_ADDR_CMD_GETSTATUS	0x0C	// This command is used to read the VZ89 status coded with 6 bytes:
#define MICS_VZ_89TE_DATE_CODE 0x0D

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


void I2C_read_7_bytes(uint8_t addrDev, uint8_t addrReg, uint8_t data[]) {
	int ret;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	if (cmd == NULL) {
		cout << "C'est pas cool :(" << endl;
	}
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, MICS_VZ_89TE_ADDR_CMD_GETSTATUS, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, 0x00, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, 0x00, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, 0x00, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, 0x00, ACK_CHECK_EN);
	i2c_master_write_byte(cmd, 0x00, ACK_CHECK_EN);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
	if (ret != ESP_OK) {
        	cout << "Problem i2c write" << endl;
			cout << hex << ret << dec << endl;
    }

	cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (addrDev << 1) | I2C_MASTER_READ, ACK_VAL);
	ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    if (ret != ESP_OK) {
        cout << "Problem i2c weird" << endl;
    }
	i2c_cmd_link_delete(cmd);
	
    vTaskDelay(100 / portTICK_RATE_MS);

    cmd = i2c_cmd_link_create();
   	i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addrDev << 1)| I2C_MASTER_READ, ACK_CHECK_EN);
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
        	cout << "Problem i2c read" << endl;
    }
	i2c_cmd_link_delete(cmd);
	cout << "|" << (int)data[0] << "|" << (int)data[1] <<"|" << (int)data[2] <<"|" << (int)data[3] <<"|" << (int)data[4] <<"|" << (int)data[5] <<"|" << (int)data[6] << endl; 
}

void I2C_demo() {
	uint8_t data[7];
	int status, co2, voc;
	I2C_config();
	cout << "I2C config OK" << endl;
	vTaskDelay(1000 / portTICK_RATE_MS);
	while(1) {
		I2C_read_7_bytes(MICS_VZ_89TE_ADDR, MICS_VZ_89TE_ADDR_CMD_GETSTATUS, data);
		status = data[5];
    	co2 = (data[1] - 13) * (1600.0 / 229) + 400; // ppm: 400 .. 2000
    	voc = (data[0] - 13) * (1000.0/229); // ppb: 0 .. 1000
		cout << "Status: " << (int)status << endl;
		cout << "co2: " << co2 << endl;
		cout << "voc: " << voc << endl;
		vTaskDelay(2000 / portTICK_RATE_MS);
		memset(data,0,sizeof(data));
	}
}

void app_main(void)
{
	I2C_demo();
} // app_main
