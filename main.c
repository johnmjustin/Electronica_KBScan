/*
 * File:   main.c
 * Author: Justin
 *
 * Created on July 2, 2017, 6:45 PM
 */


// PIC18F45K20 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config FOSC = INTIO67    // Oscillator Selection bits->Internal oscillator block, port function on RA6 and RA7
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF    // Internal/External Oscillator Switchover bit->Oscillator Switchover mode disabled

// CONFIG2L
#pragma config PWRT = OFF    // Power-up Timer Enable bit->PWRT disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config BORV = 18    // Brown Out Reset Voltage bits->VBOR set to 1.8 V nominal

// CONFIG2H
#pragma config WDTEN = OFF    // Watchdog Timer Enable bit->WDT is controlled by SWDTEN bit of the WDTCON register
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits->1:32768

// CONFIG3H
#pragma config CCP2MX = PORTC    // CCP2 MUX bit->CCP2 input/output is multiplexed with RC1
#pragma config PBADEN = OFF    // PORTB A/D Enable bit->PORTB<4:0> pins are configured as digital I/O on Reset
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit->Timer1 configured for higher power operation
#pragma config HFOFST = ON    // HFINTOSC Fast Start-up->HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.
#pragma config MCLRE = ON    // MCLR Pin Enable bit->MCLR pin enabled; RE3 input pin disabled

// CONFIG4L
#pragma config STVREN = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config LVP = ON    // Single-Supply ICSP Enable bit->Single-Supply ICSP enabled
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
#pragma config DEBUG = ON    // Background Debugger Enable bit->Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug

// CONFIG5L
#pragma config CP0 = OFF    // Code Protection Block 0->Block 0 (000800-001FFFh) not code-protected
#pragma config CP1 = OFF    // Code Protection Block 1->Block 1 (002000-003FFFh) not code-protected
#pragma config CP2 = OFF    // Code Protection Block 2->Block 2 (004000-005FFFh) not code-protected
#pragma config CP3 = OFF    // Code Protection Block 3->Block 3 (006000-007FFFh) not code-protected

// CONFIG5H
#pragma config CPB = OFF    // Boot Block Code Protection bit->Boot block (000000-0007FFh) not code-protected
#pragma config CPD = OFF    // Data EEPROM Code Protection bit->Data EEPROM not code-protected

// CONFIG6L
#pragma config WRT0 = OFF    // Write Protection Block 0->Block 0 (000800-001FFFh) not write-protected
#pragma config WRT1 = OFF    // Write Protection Block 1->Block 1 (002000-003FFFh) not write-protected
#pragma config WRT2 = OFF    // Write Protection Block 2->Block 2 (004000-005FFFh) not write-protected
#pragma config WRT3 = OFF    // Write Protection Block 3->Block 3 (006000-007FFFh) not write-protected

// CONFIG6H
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-3000FFh) not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected

// CONFIG7L
#pragma config EBTR0 = OFF    // Table Read Protection Block 0->Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF    // Table Read Protection Block 1->Block 1 (002000-003FFFh) not protected from table reads executed in other blocks
#pragma config EBTR2 = OFF    // Table Read Protection Block 2->Block 2 (004000-005FFFh) not protected from table reads executed in other blocks
#pragma config EBTR3 = OFF    // Table Read Protection Block 3->Block 3 (006000-007FFFh) not protected from table reads executed in other blocks

// CONFIG7H
#pragma config EBTRB = OFF    // Boot Block Table Read Protection bit->Boot Block (000000-0007FFh) not protected from table reads executed in other blocks



#include <xc.h>
#include "mcc.h"
#include "gpio.h"
#include "main.h"

const uint8_t LED_Data_Chan1[8] = {8,4,2,1,128,64,32,16};

void SYSTEM_Initialize(void)
{

    INTERRUPT_Initialize();
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    I2C_Initialize();
    ECCP1_Initialize();
    CVREF_Initialize();
    CCP2_Initialize();
    EXT_INT_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // SCS FOSC; OSTS intosc; IRCF 8MHz_HFINTOSC/2; IDLEN disabled; 
    OSCCON = 0x60;
    // INTSRC disabled; PLLEN disabled; TUN 0; 
    OSCTUNE = 0x00;
}

uint8_t Read_Port_IN(void)
{
    return(SELECTION_PORT_IN);
}

uint8_t Read_I2C(uint8_t Channel_Addr)
{
    uint8_t rcv_data = 0x00;
    
    I2C_Master_Start();
    I2C_Master_Write(Channel_Addr & 0xFE); // Slave address with Write command 
    I2C_Master_Write(0x03);  // Command Byte - Command Register
    I2C_Master_Write(0xFF);  // Data to Register Byte, configure as output
    I2C_Master_Stop();
    __delay_ms(1);
    I2C_Master_Start();
    I2C_Master_Write(Channel_Addr & 0xFE); // Slave address with Write command    
    I2C_Master_Write(0x00); // Write command 0 to slave
    I2C_Master_Start();
    I2C_Master_Write(Channel_Addr & 0xFF); // Slave address with Read command
    rcv_data = I2C_Master_Read(0);    // Read Data 
    I2C_Master_Stop();
    __delay_ms(1);
    I2C_Master_Start();
    I2C_Master_Write(Channel_Addr & 0xFF); // Slave address with Read command
    rcv_data = I2C_Master_Read(0);    // Read Data 
    I2C_Master_Stop();
    __delay_ms(1);
    return rcv_data;    
          
}

void Write_I2C(uint8_t Channel_Addr, uint8_t Data)
{
    I2C_Master_Start();
    I2C_Master_Write(Channel_Addr & 0xFE); // Slave address with Write command 
    I2C_Master_Write(0x03);  // Command Byte - Command Register
    I2C_Master_Write(0x00);  // Data to Register Byte, configure as output
    I2C_Master_Stop();
    __delay_ms(1);
    I2C_Master_Start();
    I2C_Master_Write(Channel_Addr & 0xFE); // Slave address with Write command
    I2C_Master_Write(0x01);  // Command Byte - Output Register
    I2C_Master_Write(Data);  // Data to be on the port
    I2C_Master_Stop();    
    __delay_ms(1);    
}

uint8_t Encode_LED_Data_Channel1(uint8_t DataReadI2C)
{
    uint8_t index = 0;
    
    while(!(DataReadI2C & 0b00000001))
    {
        DataReadI2C = DataReadI2C >> 1;
        index++;
    }
    return(LED_Data_Chan1[index]);
}

void main(void) {
    
    SYSTEM_Initialize();
    
    uint8_t channel = 0x00;
    uint8_t I2C_Data = 0x00;    
    
    Write_I2C(I2C_LED_CHANNEL_1, (0x02 ^ 0xFF));   // At power on FR2 will be selected
    
    while(1)
    {                
        LED_STATUS_OUT = 1;                
        channel = Read_Port_IN() & 0b11000000;  
        // Test
        channel = 0b10000000;
        switch (channel)
        {
            case SELECT_CHANNEL_1:                
                I2C_Data = Read_I2C(I2C_CHANNEL_1_ADDR);
                if (I2C_Data != 0xFF)    // If Switch is pressed then only we will Swith On LED.
                {                    
                    Write_I2C(I2C_LED_CHANNEL_1,~(Encode_LED_Data_Channel1(~I2C_Data)));
                }
                break;
            case SELECT_CHANNEL_2:
                I2C_Data = Read_I2C(I2C_CHANNEL_2_ADDR);
                Write_I2C(I2C_LED_CHANNEL_2,I2C_Data);
                break;
            case SELECT_CHANNEL_3:
                I2C_Data = Read_I2C(I2C_CHANNEL_3_ADDR);
                Write_I2C(I2C_LED_CHANNEL_3,I2C_Data);
                break;
            case SELECT_CHANNEL_4:
                I2C_Data =  Read_I2C(I2C_CHANNEL_4_ADDR);
                // Write_I2C(I2C_LED_CHANNEL_4,I2C_Data);
                break;
            default:
                break;
        }
        DATA_PORT_OUT = I2C_Data;        
        
    }
    
    return;
}
