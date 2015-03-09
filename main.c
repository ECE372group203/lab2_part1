#include "p24FJ64GA002.h"
#include "timer.h"
#include "keypad.h"
#include "lcd.h"


#define DEBOUNCE_DELAY 5000


typedef enum stateTypeEnum{
    waitForPress, debouncePress, scanButton, waitForRelease, debounceRelease
} stateType;

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

/***********************************************************
* waitForPress - this state will wait for the ISR to go high
* debouncePress - this state runs of the timer for some delay
* scanButton - runs the keypad scan function to find which button was pressed and sends that to LCD
* waitForRelease - waits till ISR goes high again and sets its direction
* debounceRelease - delay for debouncing of button
***********************************************************/

volatile stateType curState = waitForPress;


int main(void){
    initKeypad();
   
    initLCD();
    

    int lineCheck = 0;
    IEC1bits.CNIE = 1; //Overall Change Notification on
    IFS1bits.CNIF = 0; //Set the flag down





    char key = -1;

    while(1){
        switch(curState){
            case scanButton:

                key = scanKeypad();
                if(key != -1 ){

                    if(lineCheck <= 7){
                    printCharLCD(key);
                    lineCheck++;
                    }
                    else if(lineCheck == 8){
                        moveCursorLCD(1,0);
                        printCharLCD(key);
                        lineCheck++;
                    }
                    else if(lineCheck > 7 && lineCheck <= 15){
                        
                        printCharLCD(key); //
                        lineCheck++;
                        }
                    else if(lineCheck == 16){
                    moveCursorLCD(0,0);
                    printCharLCD(key);
                    lineCheck = 0;
                }
                  resetKeypad();
                  curState = waitForRelease;
                  IEC1bits.CNIE = 1;
                }
                

                break;

            case waitForPress:
                break;
            case debouncePress:
                delayUs(DEBOUNCE_DELAY);
                curState = scanButton;
                break;
            case waitForRelease:
                
                IEC1bits.CNIE = 1;
                break;
            case debounceRelease:
                delayUs(DEBOUNCE_DELAY);
                curState = waitForPress;
                break;

        }


    }
    return 0;
}

void _ISR _CNInterrupt(void){

    IFS1bits.CNIF = 0;
    if(COL1 == KEY_PRESSED || COL2 == KEY_PRESSED || COL3 == KEY_PRESSED)curState = debouncePress;
    else curState = debounceRelease;
}
