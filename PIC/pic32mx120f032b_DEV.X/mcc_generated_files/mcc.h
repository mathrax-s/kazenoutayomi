/**
  @Generated PIC32MX MCUs Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.h

  @Summary:
    This is the mcc.h file generated using PIC32MX MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC32MX MCUs - pic32mx : v1.35
        Device            :  PIC32MX120F032B
        Version           :  1.02
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

#ifndef MCC_H
#define	MCC_H
#include <xc.h>
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include "uart1.h"
#include "tmr1.h"
#include "tmr2.h"
#include "tmr3.h"
#include "interrupt_manager.h"
#include "oc1.h"
#include "i2c1.h"
#include "../wave_mrk.h"
#include "../wavetable2.h"
#include "../scale_table.h"
#include "../pitches.h"



#define _XTAL_FREQ  64000000UL

#define POT1 10
// power of two; must match with scale_table values
#define POT2 8 // power of two; must match with scale_table values

#define ENVPOT1 7
#define ENVPOT2 5

#define FADEIN 1
#define FADEOUT 0.99999

#define OSCILLATOR_COUNT 12 // 16 oscillators: 25% load with -O1 (64: 90%)
#define CLIP 1016 // 127 * 8


//static const volatile int8_t* wtp1 = wt_attack1;
//static const volatile int8_t* wtp2 = wt_attack2;

extern uint32_t increments_pot1[ OSCILLATOR_COUNT ];
extern uint32_t phase_accu_pot1[ OSCILLATOR_COUNT ];
extern uint32_t envelope_positions_envpot1[ OSCILLATOR_COUNT ];

extern uint32_t increments_pot2[ OSCILLATOR_COUNT ];
extern uint32_t phase_accu_pot2[ OSCILLATOR_COUNT ];
extern uint32_t envelope_positions_envpot2[ OSCILLATOR_COUNT ];

extern uint8_t next_osc1;
extern uint8_t next_osc2;
extern uint16_t ticks;
extern uint32_t time;
extern uint16_t event_index;

extern const uint16_t event_count;

#define  sizeof_wt1_attack_pot              ((uint32_t)(sizeof(wt_attak1) << POT1))
#define  sizeof_wt1_sustain_pot             ((uint32_t)(sizeof(wt_sustain1) << POT1))
#define  sizeof_wt1                         (sizeof_wt1_attack_pot+sizeof_wt1_sustain_pot)
#define  sizeof_envelope1_table_envpot      ((uint32_t)(sizeof(envelope_table1) << ENVPOT1))

#define  sizeof_wt2_attack_pot              ((uint32_t)(sizeof (wt_attak2) << POT2))
#define  sizeof_wt2_sustain_pot             ((uint32_t)(sizeof (wt_sustain2) << POT2))
#define  sizeof_wt2                         (sizeof_wt2_attack_pot+sizeof_wt2_sustain_pot)
#define  sizeof_envelope2_table_envpot      ((uint32_t)sizeof (envelope_table2) << ENVPOT2)


extern uint8_t my_sound_num;
extern uint8_t last_sound_num;
extern uint8_t my_i2c;
extern uint8_t last_my_i2c;
extern uint8_t now_slider;

extern uint8_t receive_num;

extern float crossfade;
extern uint32_t count;
extern uint8_t sound_count;
extern uint8_t startdone;

extern uint32_t timeout;
extern uint32_t ledtime;

extern float fadein;
extern float fadeout;

extern uint8_t sensor_data;

// for MATHRAX
static const uint8_t scale[] = {

    //    NOTE_D0, NOTE_E0, NOTE_G0, NOTE_A0, NOTE_B0,
    //    NOTE_D1, NOTE_E1, NOTE_G1, NOTE_A1, NOTE_B1,
    //
    //    NOTE_D2, NOTE_E2, NOTE_G2, NOTE_A2, NOTE_B2,
    //    NOTE_D3, NOTE_E3, NOTE_G3, NOTE_A3, NOTE_B3,
    //    NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4,

    NOTE_D3, NOTE_E3, NOTE_G3, NOTE_A3, NOTE_B3,
    NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4,
    NOTE_D5, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_B5,
    NOTE_D6, NOTE_E6, NOTE_G6, NOTE_A6, NOTE_B6,
    NOTE_D7, NOTE_E7, NOTE_G7, NOTE_A7, NOTE_B7,
    NOTE_D8, NOTE_E8, NOTE_G8, NOTE_A8, NOTE_B8,
    NOTE_D9, NOTE_E9, NOTE_G9, NOTE_A9, NOTE_B9,


    //    NOTE_D8, NOTE_E8, NOTE_G8, NOTE_A8, NOTE_B8,
    //    NOTE_D9, NOTE_E9, NOTE_G9, NOTE_A9, NOTE_B9,

    //        NOTE_Db3, NOTE_Eb3, NOTE_Gb3, NOTE_Ab3, NOTE_Bb3,
    //        NOTE_Db4, NOTE_Eb4, NOTE_Gb4, NOTE_Ab4, NOTE_Bb4,
    //        NOTE_Db5, NOTE_Eb5, NOTE_Gb5, NOTE_Ab5, NOTE_Bb5,
    //        NOTE_Db6, NOTE_Eb6, NOTE_Gb6, NOTE_Ab6, NOTE_Bb6,
    //        NOTE_Db7, NOTE_Eb7, NOTE_Gb7, NOTE_Ab7, NOTE_Bb7,
    //        NOTE_Db8, NOTE_Eb8, NOTE_Gb8, NOTE_Ab8, NOTE_Bb8,
};

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Unlocks the write protected register to enable any write operation
 *                  MCC GUI
 * @Example
    SYSTEM_RegUnlock();
 */
void SYSTEM_RegUnlock(void);

/**
 * @Param
    none

 * @Returns
    none

 * @Description
    Locks the write protected register to disable any write operation

 * @Example
    SYSTEM_RegLock();
 */

void SYSTEM_RegLock(void);

/**
 * @Param
    none

 * @Returns
    none

 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 * @Example
    SYSTEM_Initialize(void);
 */

void SYSTEM_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the oscillator to the default states configured in the
 *                  MCC GUI
 * @Example
    OSCILLATOR_Initialize(void);
 */
void OSCILLATOR_Initialize(void);

/**
 * @Param
    none

 * @Returns
    none

 * @Description
    Automatically called whenever there is a un-handled exception
 
 * @Example
    none
 */

void _general_exception_handler (void);

#endif	/* MCC_H */
/**
 End of File
 */