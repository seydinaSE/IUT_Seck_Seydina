/* 
 * File:   main.c
 * Author: E306-PC2
 *
 * Created on September 2, 2025, 4:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"

int main (void){
    InitOscillator();
    InitIO();
    InitPWM();
    InitTimer23();
  



while(1){
    
}


}