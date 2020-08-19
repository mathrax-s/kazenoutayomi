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


#define NO_FINGER 0xFFFFu
#define SLIDER_RESOLUTION 100

int Button[8] = {0,0,0,0,0,0,0,0};
int Status[8] = {0,0,0,0,0,0,0,0};
int bright;

//PROTOTYPE

int main()
{
    int i;
    
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
        while(CapSense_IsBusy() != 0)
		{
			/* Loop until condition true */


        
        Button[0] = CapSense_CheckIsWidgetActive(CapSense_SENSOR_BUTTON0__BTN);
        Button[1] = CapSense_CheckIsWidgetActive(CapSense_SENSOR_BUTTON1__BTN);
        Button[2] = CapSense_CheckIsWidgetActive(CapSense_SENSOR_BUTTON2__BTN);
        Button[3] = CapSense_CheckIsWidgetActive(CapSense_SENSOR_BUTTON3__BTN);
        Button[4] = CapSense_CheckIsWidgetActive(CapSense_SENSOR_BUTTON4__BTN);
        Button[5] = CapSense_CheckIsWidgetActive(CapSense_SENSOR_BUTTON5__BTN);
        Button[6] = CapSense_CheckIsWidgetActive(CapSense_SENSOR_BUTTON6__BTN);
        Button[7] = CapSense_CheckIsWidgetActive(CapSense_SENSOR_BUTTON7__BTN);
        
 

        

        for(i=0; i<8; i++){
            if(Button[i]==1){
                //Pin_1_Write(0);
                bright*=0.9;
                if(Status[i]==0){
                    Status[i]=1;
                    UART_1_UartPutChar((i+1));
                }
            }else{
                if(Status[i]==1){
                    Status[i]=0;
                }
            }
        }
        LED_CONTROL_WriteCompare(65535-(uint32)bright);
        bright+=100;
        if(bright>65535)bright=65535;
        }
        
    }
    
    return 0;
}
