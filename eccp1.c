/*******************************************************************************
  ECCP1 Generated Driver File

  Company:
    Microchip Technology Inc.

  File Name:
    eccp1.c

  Summary:
    This is the generated driver implementation file for the ECCP1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  Description:
    This source file provides implementations for driver APIs for ECCP1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC18F45K20
        Version           :  1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*******************************************************************************/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <xc.h>
#include "eccp1.h"
/**
  Prototype:        void ECCP1_Initialize(void)
  Input:            none
  Output:           none
  Description:      ECCP1_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            ECCP1_Initialize();
*/
void ECCP1_Initialize(void)
{
    // CCP1M off/reset; DC1B 0; P1M single; 
    CCP1CON = 0x00;
    // ECCPASE operating; PSSBD low; PSSAC low; ECCPAS disabled; 
    ECCP1AS = 0x00;
    // PRSEN manual_restart; PDC 0; 
    PWM1CON = 0x00;
    // STRD P1D_to_port; STRC P1C_to_port; STRB P1B_to_port; STRA P1A_to_CCP1M; STRSYNC start_at_begin; 
    PSTRCON = 0x01;
    // CCPR1L 0; 
    CCPR1L = 0x00;
    // CCPR1H 0; 
    CCPR1H = 0x00;
}
