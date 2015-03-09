#include "p24FJ64GA002.h"
#include "keypad.h"
#include "timer.h"
#define DEBOUNCE_DELAY 5000

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){

    //Setting the outputs
    TRIS_A0 = 0;
    TRIS_A1 = 0;
    TRIS_B2 = 0;
    TRIS_B3 = 0;

    //Setting the inputs
    TRIS_B5 = 1;
    TRIS_B11 = 1;
    TRIS_B10 = 1;

    //Turning on ODC
    ODC_A0 = 1;
    ODC_A1 = 1;
    ODC_B2 = 1;
    ODC_B3 = 1;

    //Writting zero to Columns
    ROW1 = 0;
    ROW2 = 0;
    ROW3 = 0;
    ROW4 = 1121;

    //Turning on the pull up resistors
    CN27PU = 1;
    CN15PU = 1;
    CN16PU = 1;

    //Turning on the CN interrupt enables
    CNIE_CN27 = 1;
    CNIE_CN15 = 1;
    CNIE_CN16 = 1;


}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    IEC1bits.CNIE = 0;
    char key = -1;

    /*The following scans the keypad line by line, trying to determine which one is high*/

    setLATs();
    //Scan ROW 1
    ROW1 = OFF;
    if(COL3 == KEY_PRESSED){
        delayUs(DEBOUNCE_DELAY);
        key = '1';
        setLATs();
        return key;
    }
    else if (COL2 == KEY_PRESSED){
        delayUs(DEBOUNCE_DELAY);
         key = '2';
         setLATs();
         return key;
    }

    else if (COL3 == KEY_PRESSED){
         delayUs(DEBOUNCE_DELAY);
         key = '3';
         setLATs();
         return key;
    }

    ROW2 = OFF;
    if(COL1 == KEY_PRESSED){
        delayUs(DEBOUNCE_DELAY);
        key ='4';
        setLATs();
        return key;
    }

    else if(COL2 == KEY_PRESSED){
        delayUs(DEBOUNCE_DELAY);
        key = '5';
        setLATs();
        return key;
    }

    else if(COL3 == KEY_PRESSED ){
        delayUs(DEBOUNCE_DELAY);
        key = '6';
        setLATs();
        return key;
    }

    ROW3 = OFF;
    if(COL1 == KEY_PRESSED){
        delayUs(DEBOUNCE_DELAY);
        key = '7';
        setLATs();
        return key;
    }
    else if(COL2 == KEY_PRESSED){
        delayUs(DEBOUNCE_DELAY);
        key = '8';
        setLATs();
        return key;
    }
    else if(COL3 == KEY_PRESSED){
        key = '9';
        setLATs();
        return key;
    }
    ROW4 = OFF;
    if(COL1 == KEY_PRESSED){
        key = '*';
        setLATs();
        return key;
    }
    else if(COL2 == KEY_PRESSED ){
        key = '0';
        setLATs();
        return key;
    }
    else if(COL3 == KEY_PRESSED){
        key = '#';
        setLATs();
        return key;
    }

    return key;
}

void setLATs(void){
    ROW1 = OFF;
    ROW2 = OFF;
    ROW3 = OFF;
    ROW4 = OFF;

}