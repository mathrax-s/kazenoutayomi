
/**
  TMR3 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr3.c

  @Summary
    This is the generated source file for the TMR3 driver using PIC32MX MCUs

  @Description
    This source file provides APIs for driver for TMR3. 
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
#include "tmr3.h"
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

static TMR_OBJ tmr3_obj;

/**
  Section: Driver Interface
 */


void TMR3_Initialize (void)
{
    // TMR3 0; 
    TMR3 = 0x0;
    // Period = 0.000064 s; Frequency = 64000000 Hz; PR3 4096; 
    PR3 = 0x1000;
    // TCKPS 1:1; TCS PBCLK; SIDL disabled; TGATE disabled; ON enabled; 
    T3CON = 0x8000;

    IFS0CLR= 1 << _IFS0_T3IF_POSITION;
    IEC0bits.T3IE = true;

    tmr3_obj.timerElapsed = false;

}



void __ISR(_TIMER_3_VECTOR, IPL1AUTO) _T3Interrupt (  )
{

    //***User Area Begin

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    TMR3_CallBack();

    //***User Area End

    tmr3_obj.count++;
    tmr3_obj.timerElapsed = true;
    IFS0CLR= 1 << _IFS0_T3IF_POSITION;
}

void TMR3_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR3 = value;
    /* Reset the status information */
    tmr3_obj.timerElapsed = false;
}

uint16_t TMR3_Period16BitGet( void )
{
    return( PR3 );
}

void TMR3_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR3 = value;
    /* Reset the status information */
    tmr3_obj.timerElapsed = false;
}

uint16_t TMR3_Counter16BitGet( void )
{
    return( TMR3 );
}

void __attribute__((weak)) TMR3_CallBack(void) {
    

        
    timeout ++;
    //timeout reset is I2C
    if (timeout > 250000) {
        /* perform a system unlock sequence */
        // starting critical sequence
        SYSKEY = 0x00000000; //write invalid key to force lock
        SYSKEY = 0xAA996655; //write key1 to SYSKEY
        SYSKEY = 0x556699AA; //write key2 to SYSKEY
        // OSCCON is now unlocked
        /* set SWRST bit to arm reset */
        RSWRSTSET = 1;
        /* read RSWRST register to trigger reset */
        unsigned int dummy;
        dummy = RSWRST;
    }
    if (startdone == 1) {
        if(ledtime > 0){
            ledtime --;
            LATBbits.LATB5 = 0;
        }else{
            LATBbits.LATB5 = 1;
        }
    }
    
    if (my_i2c != last_my_i2c) {
        my_sound_num = (float) (sizeof (scale)) * (float) (my_i2c / 100.0);
    }

    //From PSoC 0~99
    if ((my_sound_num != last_sound_num & my_sound_num > 0) || (my_i2c != last_my_i2c)) {

        crossfade += fadein;
        if (crossfade > 1.0)crossfade = 1.0;

        increments_pot1[ next_osc1 ] = scale_table[ scale[ my_sound_num ]];
        phase_accu_pot1[ next_osc1 ] = 0;
        envelope_positions_envpot1[ next_osc1 ] = 0;
        ++next_osc1;
        if (next_osc1 >= OSCILLATOR_COUNT) {
            next_osc1 = 0;
        }
        increments_pot1[ next_osc1 ] = scale_table[ scale[ my_sound_num ]] + 24;
        phase_accu_pot1[ next_osc1 ] = 0;
        envelope_positions_envpot1[ next_osc1 ] = 0;
        ++next_osc1;
        if (next_osc1 >= OSCILLATOR_COUNT) {
            next_osc1 = 0;
        }

        increments_pot2[ next_osc2 ] = scale_table[ scale[ my_sound_num ]] + 24;
        phase_accu_pot2[ next_osc2 ] = 0;
        envelope_positions_envpot2[ next_osc2 ] = 0;
        ++next_osc2;
        if (next_osc2 >= OSCILLATOR_COUNT) {
            next_osc2 = 0;
        }
        increments_pot2[ next_osc2 ] = scale_table[ scale[ my_sound_num ]] + 2;
        phase_accu_pot2[ next_osc2 ] = 0;
        envelope_positions_envpot2[ next_osc2 ] = 0;
        ++next_osc2;
        if (next_osc2 >= OSCILLATOR_COUNT) {
            next_osc2 = 0;
        }
    }

    last_my_i2c = my_i2c;
    last_sound_num = my_sound_num;
}

void TMR3_Start(void) {
    /* Reset the status information */
    tmr3_obj.timerElapsed = false;

    IFS0CLR= 1 << _IFS0_T3IF_POSITION;
    /*Enable the interrupt*/
    IEC0bits.T3IE = true;

    /* Start the Timer */
    T3CONbits.ON = 1;
}

void TMR3_Stop( void )
{
    /* Stop the Timer */
    T3CONbits.ON = false;

    /*Disable the interrupt*/
    IEC0bits.T3IE = false;
}

bool TMR3_GetElapsedThenClear(void)
{
    bool status;

    status = tmr3_obj.timerElapsed;

    if(status == true)
    {
        tmr3_obj.timerElapsed = false;
    }
    return status;
}

int TMR3_SoftwareCounterGet(void)
{
    return tmr3_obj.count;
}

void TMR3_SoftwareCounterClear(void)
{
    tmr3_obj.count = 0;
}

/**
 End of File
 */
