/* 
 * File:   ADC.h
 * Author: E306-PC2
 *
 * Created on 16 septembre 2025, 11:24
 */

#ifndef ADC_H
#define	ADC_H

void InitADC1(void);
void __attribute__((interrupt, no_auto_psv)) _AD1Interrupt(void);
void ADC1StartConversionSequence();
void ADCClearConversionFinishedFlag(void);


#endif	/* ADC_H */

