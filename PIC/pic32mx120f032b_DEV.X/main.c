/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC32MX MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC32MX MCUs - pic32mx : v1.35
        Device            :  PIC32MX270F256B
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.42
        MPLAB             :  MPLAB X 3.55
 */

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

#include "mcc_generated_files/mcc.h"

uint32_t increments_pot1[ OSCILLATOR_COUNT ];
uint32_t phase_accu_pot1[ OSCILLATOR_COUNT ];
uint32_t envelope_positions_envpot1[ OSCILLATOR_COUNT ];

uint32_t increments_pot2[ OSCILLATOR_COUNT ];
uint32_t phase_accu_pot2[ OSCILLATOR_COUNT ];
uint32_t envelope_positions_envpot2[ OSCILLATOR_COUNT ];

uint8_t next_osc1 = 0;
uint8_t next_osc2 = 0;

uint8_t my_sound_num = 0;
uint8_t last_sound_num = 0;

uint8_t receive_num;

uint8_t my_i2c = 0;
uint8_t last_my_i2c = 0;

uint8_t now_slider = 0;

float crossfade;
uint32_t count = 0;
uint8_t sound_count = 0;
uint8_t startdone = 0;

uint32_t timeout = 0;
uint32_t ledtime = 0;

float fadein = FADEIN;
float fadeout = FADEOUT;

uint8_t sensor_data;
/*
                         Main application
 */
int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    uint8_t osc;

    for (osc = 0; osc < OSCILLATOR_COUNT; ++osc) {
        increments_pot1[ osc ] = 0;
        phase_accu_pot1[ osc ] = 0;
        envelope_positions_envpot1[ osc ] = 0;
        increments_pot2[ osc ] = 0;
        phase_accu_pot2[ osc ] = 0;
        envelope_positions_envpot2[ osc ] = 0;
    }

    LATBbits.LATB5 = 1;
    LATBbits.LATB7 = 0;
    LATAbits.LATA4 = 0; //RS485 receive

    uint8_t i;
    uint32_t j;
    startdone = 0;
    for (i = 0; i < 10; i++) {
        LATBbits.LATB5 = 0;
        for (j = 0; j < 100000; j++) {
            asm("nop");
        }
        LATBbits.LATB5 = 1;
        for (j = 0; j < 100000; j++) {
            asm("nop");
        }
    }
    startdone = 1;
    
    while (true) {
        
		if(UART1_ReceiveBufferIsEmpty() == false){
            receive_num = UART1_Read();
            if(receive_num>=0 && receive_num<=100){
                sensor_data = receive_num;
                my_sound_num = (float) (sizeof (scale)) * (float) (receive_num / 100.0);
                now_slider = receive_num;
            }
		}

    }

    return -1;
}
/**
 End of File
 */