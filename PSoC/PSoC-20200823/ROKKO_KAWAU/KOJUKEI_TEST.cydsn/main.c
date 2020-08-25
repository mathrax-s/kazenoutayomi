/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>


//#define NO_FINGER 0xFFFFu
//#define SLIDER_RESOLUTION 100

//int status;
int bright;
int slider_pos = 0;

int preCnt;
int	current_sensor;	
int prev_sensor;
int	prev_sound;
int	slider_start_pos;

float average;
    
//PROTOTYPE

int main()
{

    
    CyGlobalIntEnable;      /* Enable global interrupts */
    CapSense_Start();	
    UART_1_Start();
    LED_CONTROL_Start();
    /* Initialize baselines */ 
    CapSense_InitializeAllBaselines();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */


    
    for(;;)
    {
        /* Update all baselines */
        CapSense_UpdateEnabledBaselines();
        
   		/* Start scanning all enabled sensors */
    	CapSense_ScanEnabledWidgets();
        
        /* Place your application code here */
        while(CapSense_IsBusy() != 0);
		
		/* Loop until condition true */
		current_sensor = CapSense_GetCentroidPos(0);
        average = average*(9.0/10.0) + (float)(current_sensor/10.0);
        
		if(prev_sensor == 0xFF){

			slider_start_pos=(int)current_sensor;
            bright=0;
			UART_1_UartPutChar((slider_start_pos)+1);


		}else {

			if(current_sensor==0xFF){
                UART_1_UartPutChar(0);
				slider_pos = 0;
			}else{
				if(current_sensor!=prev_sensor){
					bright=0;
					UART_1_UartPutChar((int)(current_sensor)+1);
					slider_pos = (int)current_sensor+1;
				}
			}
		}   	
    	prev_sensor = current_sensor;

    
        LED_CONTROL_WriteCompare(65535-(uint32)bright);
        bright+=1000;
        if(bright>65535)bright=65535;
        
        
    }
    
    return 0;
}
