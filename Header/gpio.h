/* 
 * File:   gpio.h
 * Author: Justin John
 * Comments:
 * Revision history: 
 */

#ifndef GPIO_H
#define GPIO_H


#define I2C_SCL PORTCbits.RC3   // I2C Clock Pin
#define I2C_SDA PORTCbits.RC4   // I2C Data Pin
#define LED_STATUS_OUT PORTCbits.RC5 // LED Status Pin
#define SELECTION_PORT_IN PORTD    // Iinput from computer
#define DATA_PORT_OUT   PORTA       // Output to computer


#endif
