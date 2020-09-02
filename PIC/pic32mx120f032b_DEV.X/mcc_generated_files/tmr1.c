
/**
  TMR1 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr1.c

  @Summary
    This is the generated source file for the TMR1 driver using PIC32MX MCUs

  @Description
    This source file provides APIs for driver for TMR1. 
    Generation Information : 
        Product Revision  :  PIC32MX MCUs - pic32mx : v1.35
        Device            :  PIC32MX120F032B
        Driver Version    :  0.5
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.42
        MPLAB 	          :  MPLAB X 3.55
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

/**
  Section: Included Files
 */

#include <xc.h>
#include "tmr1.h"
#include "mcc.h"

/**
  Section: Data Type Definitions
 */

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintainence of the hardware instance.

  @Description
    This defines the object required for the maintainence of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
 */

typedef struct _TMR_OBJ_STRUCT
{
    /* Timer Elapsed */
    bool                                                    timerElapsed;
    /*Software Counter value*/
    uint8_t                                                 count;

} TMR_OBJ;

static TMR_OBJ tmr1_obj;

/**
  Section: Driver Interface
 */


void TMR1_Initialize (void)
{
    // TMR1 0; 
    TMR1 = 0x0;
    // Period = 0.000032 s; Frequency = 64000000 Hz; PR1 2048; 
    PR1 = 0x800;
    // TCKPS 1:1; TWDIS disabled; TCS PBCLK; SIDL disabled; TSYNC disabled; TGATE disabled; ON enabled; 
    T1CON = 0x8000;

    IFS0CLR= 1 << _IFS0_T1IF_POSITION;
    IEC0bits.T1IE = true;

    tmr1_obj.timerElapsed = false;

}



void __ISR(_TIMER_1_VECTOR, IPL1AUTO) _T1Interrupt (  )
{

    //***User Area Begin

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    TMR1_CallBack();

    //***User Area End

    tmr1_obj.count++;
    tmr1_obj.timerElapsed = true;
    IFS0CLR= 1 << _IFS0_T1IF_POSITION;
}

void TMR1_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR1 = value;
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;
}

uint16_t TMR1_Period16BitGet( void )
{
    return( PR1 );
}

void TMR1_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR1 = value;
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;
}

uint16_t TMR1_Counter16BitGet( void )
{
    return( TMR1 );
}

void __attribute__ ((weak)) TMR1_CallBack(void)
{
    // Add your custom callback code here
    int8_t osc = 0;
    int32_t value = 0;
    int32_t value1 = 0;
    int32_t value2 = 0;

    for (osc = 0; osc < OSCILLATOR_COUNT; osc++) {
        phase_accu_pot1[ osc ] += increments_pot1[ osc ];
        while (phase_accu_pot1[ osc ] >= (sizeof_wt1)) {
            phase_accu_pot1[ osc ] -= sizeof_wt1_sustain_pot;
        }
        uint16_t phase_accu = (phase_accu_pot1[ osc ] >> POT1);
        int8_t accu;
        if (phase_accu_pot1[ osc ] < sizeof_wt1_attack_pot) {
            accu = (wt_attak1[phase_accu]);
        } else {
            accu = (wt_sustain1[phase_accu]);
        }
        value1 += (envelope_table1[ envelope_positions_envpot1[ osc ] >> ENVPOT1 ] >> env1[osc]) * accu;
//        value1 += envelope_table1[ envelope_positions_envpot1[ osc ] >> ENVPOT1 ]  * accu;
        if (phase_accu_pot1[ osc ] >= sizeof_wt1_attack_pot &&
                envelope_positions_envpot1[ osc ] < sizeof_envelope1_table_envpot - 1) {
            envelope_positions_envpot1[ osc ]++;
        }
    }
    value1 >>= 10; // envelope_table resolution

    for (osc = 0; osc < OSCILLATOR_COUNT; osc++) {
        phase_accu_pot2[ osc ] += increments_pot2[ osc ];
        while (phase_accu_pot2[ osc ] >= (sizeof_wt2)) {
            phase_accu_pot2[ osc ] -= sizeof_wt2_sustain_pot;
        }
        uint16_t phase_accu = (phase_accu_pot2[ osc ] >> POT2);
        int8_t accu;
        if (phase_accu_pot2[ osc ] < sizeof_wt2_attack_pot) {
            accu = (wt_attak2[phase_accu]);
        } else {
            accu = (wt_sustain2[phase_accu]);
        }
        value2 += (envelope_table2[ envelope_positions_envpot2[ osc ] >> ENVPOT2 ] >> env2[osc]) * accu;
//        value2 += envelope_table2[ envelope_positions_envpot2[ osc ] >> ENVPOT2 ] * accu;
        if (phase_accu_pot2[ osc ] >= sizeof_wt2_attack_pot &&
                envelope_positions_envpot2[ osc ] < sizeof_envelope2_table_envpot - 1) {
            envelope_positions_envpot2[ osc ]++;
        }
    }

    value2 >>= 10; // envelope_table resolution

    //value1..TOUCH, value2..I2C
    value =  value1 * crossfade + value2 * (1.0 - crossfade);

    if (value > CLIP) {
        value = CLIP;
    } else if (value < -CLIP) {
        value = -CLIP;
    }
    OC1RS = (1024 + value);
    
    
    
}

void TMR1_Start(void) {
    /* Reset the status information */
    tmr1_obj.timerElapsed = false;

    IFS0CLR= 1 << _IFS0_T1IF_POSITION;
    /*Enable the interrupt*/
    IEC0bits.T1IE = true;

    /* Start the Timer */
    T1CONbits.ON = 1;
}

void TMR1_Stop( void )
{
    /* Stop the Timer */
    T1CONbits.ON = false;

    /*Disable the interrupt*/
    IEC0bits.T1IE = false;
}

bool TMR1_GetElapsedThenClear(void)
{
    bool status;

    status = tmr1_obj.timerElapsed;

    if(status == true)
    {
        tmr1_obj.timerElapsed = false;
    }
    return status;
}

int TMR1_SoftwareCounterGet(void)
{
    return tmr1_obj.count;
}

void TMR1_SoftwareCounterClear(void)
{
    tmr1_obj.count = 0;
}

/**
 End of File
 */
