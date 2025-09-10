/* 
 * File:   PWM.h
 * Author: E306-PC2
 *
 * Created on 10 septembre 2025, 09:45
 */

#ifndef PWM_H
#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1
void InitPWM(void);
void PWMSetSpeed(float moteur, float vitesseEnPourcents);
#endif	/* PWM_H */

