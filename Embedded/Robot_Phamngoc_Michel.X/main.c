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
#include "ADC.h"
#include "Robot.h"
#include "main.h"
#include "CB_TX1.h"
#include "CB_RX1.h"
#include "libpic30.h"
//
int Capteur;


int main(void) {
    InitOscillator();
    InitIO();
    InitADC1();
    InitPWM();
    InitTimer1();
    InitTimer4();
    InitUART();
    //InitTimer23();
    
    EN_PWM=1;


     //SendMessageDirect((unsigned char*) "Bonjour", 7);

 
    while (1) {
      
int i;
for(i=0; i< CB_RX1_GetDataSize(); i++)
{
unsigned char c = CB_RX1_Get();
SendMessage(&c,1);
}
__delay32(1000);

        
        /*  
             // unsigned int  AResult[] =ADCGetResult();  
           if (AResult[0] < 1084) {

      } else {

          LED_BLANCHE_1 = 0;
      }
      if (AResult[1] < 1084) {

          LED_BLEUE_1 = 1;
      } else {

          LED_BLEUE_1 = 0;
      }
      if (AResult[2] < 1084) {

          LED_ORANGE_1 = 1;
      } else {

          LED_ORANGE_1 = 0;
      }*/




        if (ADCIsConversionFinished()) { //fin de l'aquisition du convertisseur
            ADCClearConversionFinishedFlag(); // on enleve le flag pour pouvoir faire une nouvelle conversion
            unsigned int * result = ADCGetResult(); //création d'un pointeur pour récupérer les données 
            float volts = ((float) result [0])* 3.3 / 4096; //volt
            robotState.distanceTelemetreGauche1 = 34 / volts - 5; //volt to distance
            volts = ((float) result [1])* 3.3 / 4096;
            robotState.distanceTelemetreGauche = 34 / volts - 5; //volt to distance
            volts = ((float) result [2])* 3.3 / 4096;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [3])* 3.3 / 4096;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [4])* 3.3 / 4096;
            robotState.distanceTelemetreDroit1 = 34 / volts - 5;





            if (robotState.distanceTelemetreGauche1 < 30) {
                LED_BLANCHE_1 = 1;
                Capteur = Capteur | 0x10;
            } else {
                LED_BLANCHE_1 = 0;
                Capteur = Capteur & 0b01111;
            }
            if (robotState.distanceTelemetreGauche < 32) {
                LED_BLEUE_1 = 1;
                Capteur = Capteur | 0b01000;
            } else {
                LED_BLEUE_1 = 0;
                Capteur = Capteur & 0b10111;
            }
            if (robotState.distanceTelemetreCentre < 40) {
                LED_ORANGE_1 = 1;
                Capteur = Capteur | 0b00100;
            } else {
                LED_ORANGE_1 = 0;
                Capteur = Capteur & 0b11011;
            }
            if (robotState.distanceTelemetreDroit < 32) {
                LED_ROUGE_1 = 1;
                Capteur = Capteur | 0b00010;
            } else {
                LED_ROUGE_1 = 0;
                Capteur = Capteur & 0b11101;
            }
            if (robotState.distanceTelemetreDroit1 < 30) {
                LED_VERTE_1 = 1;
                Capteur = Capteur | 0b00001;
            } else {
                LED_VERTE_1 = 0;
                Capteur = Capteur & 0b11110;
            }
            if(robotState.distanceTelemetreCentre > 35 && robotState.distanceTelemetreGauche > 20 && robotState.distanceTelemetreDroit > 20 && robotState.distanceTelemetreDroit1 > 20 && robotState.distanceTelemetreGauche1 > 20){
                Capteur =  0b10001;
            }
        }







    }




}


unsigned char stateRobot = 0;

void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_ATTENTE_EN_COURS;
        case STATE_ATTENTE_EN_COURS:
            if (timestamp > 1000)
                stateRobot = STATE_AVANCE;
            break;
        case STATE_AVANCE:
            PWMSetSpeedConsigne(30, MOTEUR_DROIT);
            PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
            stateRobot = STATE_AVANCE_EN_COURS;
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(10, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(10, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(12, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-12, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(-12, MOTEUR_DROIT);
            PWMSetSpeedConsigne(12, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case RECULE:
            PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
            break;

        default:
            stateRobot = STATE_ATTENTE;
            break;
    }
}
unsigned char nextStateRobot = 0;

void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;
    //éDtermination de la position des obstacles en fonction des ééètlmtres
    if (Capteur == 0b00001) //Obstacle àdroite
        positionObstacle = OBSTACLE_A_DROITE_1;


    else if (Capteur == 0b00010) //Obstacle àdroite
        positionObstacle = OBSTACLE_A_DROITE_1;

    else if (Capteur == 0b00100)
        positionObstacle = OBSTACLE_EN_FACE;


    else if (Capteur == 0b01000) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_GAUCHE;
    else if (Capteur == 0b10000) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;




    else if (Capteur == 0b10001) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE_1;
    else if (Capteur == 0b11011) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;
    else if (Capteur == 0b11000) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;
    else if (Capteur == 0b11100) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;
    else if (Capteur == 0b11110) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;
    else if (Capteur == 0b00011) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;
    else if (Capteur == 0b00111) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;
    else if (Capteur == 0b01111) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;
    else if (Capteur == 0b11111) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;

    else if (Capteur == 0b00110) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;
    else if (Capteur == 0b01100) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;

    else if (Capteur == 0b01001) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE;
    else if (Capteur == 0b10010) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_GAUCHE;

    else if (Capteur == 0b01011) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;

    else if (Capteur == 0b01010) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;

    else if (Capteur == 0b10011) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE;

    else if (Capteur == 0b11001) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_GAUCHE;

    else if (Capteur == 0b10101) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;

    else if (Capteur == 0b11101) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;
    else if (Capteur == 0b10111) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_GAUCHE;

    else if (Capteur == 0b11010) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;
    else if (Capteur == 0b01110) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;


    else if (Capteur == 0b01101) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;
    else if (Capteur == 0b10110) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;



    else if (Capteur == 0b00101) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_DROITE_1;
    else if (Capteur == 0b10100) //Obstacle àgauche
        positionObstacle = OBSTACLE_EN_FACE;

    else if (Capteur == 0b00000) //Obstacle àgauche
        positionObstacle = PAS_D_OBSTACLE;



    //éDtermination de lé?tat àvenir du robot
    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;

    else if (positionObstacle == OBSTACLE_A_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;

    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;


    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;


    else if (positionObstacle == OBSTACLE_A_DROITE_1)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;

    else if (positionObstacle == OBSTACLE_EN_FACE_1)
        nextStateRobot = STATE_AVANCE;


    else if (positionObstacle == OBSTACLE_EN_FACE)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
    //Si l?on n?est pas dans la transition de lé?tape en cours
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

