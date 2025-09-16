#include <xc.h>
#include "IO.h"
#include "PWM.h"
#include "Robot.h"
#include "Toolbox.h"
#define PWMPER 24.0

void InitPWM(void) {
    PTCON2bits.PCLKDIV = 0b000; //Divide by 1
    PTPER = 100 * PWMPER; //�Priode en pourcentage
    //�Rglage PWM moteur 1 sur hacheur 1
    IOCON1bits.PMOD = 0b11; //PWM I/O pin pair is in the True Independent Output mode
    IOCON1bits.PENL = 1;
    IOCON1bits.PENH = 1;
    FCLCON1 = 0x0003; //�Dsactive la gestion des faults
    IOCON2bits.PMOD = 0b11; //PWM I/O pin pair is in the True Independent Output mode
    IOCON2bits.PENL = 1;
    IOCON2bits.PENH = 1;
    FCLCON2 = 0x0003; //�Dsactive la gestion des faults
    /* Enable PWM Module */
    PTCONbits.PTEN = 1;
}
float acceleration=0.25;
double talon = 50; //le talon c est le temps minimum de synchronisation entre la pwm du moteur et le microcontroleur
/*
void PWMSetSpeed(float vitesseEnPourcents, float moteur) {

    if (moteur == MOTEUR_GAUCHE) {
        if (vitesseEnPourcents > 0) {
            PDC1 = vitesseEnPourcents * PWMPER + talon; // le driver controle la pwm du pont H 
            SDC1 = talon;



        } else {
            PDC1 = talon;
            SDC1 = (-vitesseEnPourcents) * PWMPER + talon;
        }

    } else if (moteur == MOTEUR_DROIT) {
        if (vitesseEnPourcents > 0) {

            PDC2 = talon;
            SDC2 = vitesseEnPourcents * PWMPER + talon;
        } else {
            PDC2 = -vitesseEnPourcents * PWMPER + talon; // le driver controle la pwm du pont H 
            SDC2 = talon;

        }

    }
}
*/

PWMSetSpeedConsigne(float vitesseEnPourcents, int moteur){
    if(moteur==MOTEUR_DROIT){
        robotState.vitesseDroiteConsigne=-vitesseEnPourcents;
        
    }
    else {
        robotState.vitesseGaucheConsigne=vitesseEnPourcents;
        
    }
    
    
}

void PWMUpdateSpeed() {
    // Cette fonction est appelee sur timer et permet de suivre des rampes d acceleration
    if (robotState.vitesseGaucheCommandeCourante < robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Min(
            robotState.vitesseGaucheCommandeCourante + acceleration,
            robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Max(
            robotState.vitesseGaucheCommandeCourante - acceleration,
            robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > 0) {
        PDC1 = robotState.vitesseGaucheCommandeCourante * PWMPER + talon;
        SDC1 = talon;
    } else {
        PDC1 = talon;
        SDC1 = -robotState.vitesseGaucheCommandeCourante * PWMPER + talon;
    }
    if (robotState.vitesseDroiteCommandeCourante < robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Min(
            robotState.vitesseDroiteCommandeCourante + acceleration,
            robotState.vitesseDroiteConsigne);
    if (robotState.vitesseDroiteCommandeCourante > robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Max(
            robotState.vitesseDroiteCommandeCourante - acceleration,
            robotState.vitesseDroiteConsigne);
    if (robotState.vitesseDroiteCommandeCourante >= 0) {
        PDC2 = robotState.vitesseDroiteCommandeCourante * PWMPER + talon;
        SDC2 = talon;
    } else {
        PDC2 = talon;
        SDC2 = -robotState.vitesseDroiteCommandeCourante * PWMPER + talon;
    }
}
