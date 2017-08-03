#ifndef MAIN_H
#define MAIN_H

#define SELECT_CHANNEL_1 0b00000000
#define SELECT_CHANNEL_2 0b01000000     
#define SELECT_CHANNEL_3 0b10000000     
#define SELECT_CHANNEL_4 0b11000000     
//#define I2C_CHANNEL_1_ADDR 70
//#define I2C_CHANNEL_2_ADDR 64
//#define I2C_CHANNEL_3_ADDR 66
//#define I2C_CHANNEL_4_ADDR 68

#define I2C_CHANNEL_1_ADDR 71  // 0x47
#define I2C_CHANNEL_2_ADDR 65  // 0x41
#define I2C_CHANNEL_3_ADDR 67  // 0x43
#define I2C_CHANNEL_4_ADDR 69  // 0x45

#define I2C_LED_CHANNEL_1 73   // 0x49
#define I2C_LED_CHANNEL_2 75   // 0x4B
#define I2C_LED_CHANNEL_3 77   // 0x4D

uint8_t Encode_LED_Data_Channel1(uint8_t DataReadI2C);
#endif //MAIN_H

