/*!
****************************************************************************************************
* \file      tdot_giveaway.ino
*
* \ingroup   TDOT
*
*            Dieses Programm soll als Beispiel- oder Demoprogramm fuer unser Give-Away
*            am Tag der offenen Tuer vom SFZ Wangen dienen.
*
****************************************************************************************************
*/
/*!
****************************************************************************************************
* \defgroup TDOT     Tag der offenen Tuer 
****************************************************************************************************
*/
#include "tdot_farben.h"

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Moegliche Leuchteinstellungen
*/
/*------------------------------------------------------------------------------------------------*/
#define EINE_KERZE        0
#define EINE_TASCHENLAMPE 1
#define ZIEMLICH_BUNT     2
#define ROT_GRUEN_BLAU    3
#define BOOOOOOM          4
#define EIGENTLICH_EGAL   5

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     TdoT Pin Konfiguration
*/
/*------------------------------------------------------------------------------------------------*/
#define RGB_PIN_ROT        1
#define RGB_PIN_GRUEN      0
#define RGB_PIN_BLAU       4
#define TASTER_PIN         2
#define ZUFALLS_START_PIN  A1

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    Globale Variablen und Funktionsprototypen die man hier halt so braucht!
*/
/*------------------------------------------------------------------------------------------------*/
int wasBinIch;
int aktuelleFarbe = 0;

void RGBFarbenEinstellen(int rot, int gruen, int blau);

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Arduino Setup
*
*            Wird beim Start des Programms (entweder nach dem uebertragen auf das Board oder 
*            nach dem die Stromversorgung angeschlossen wurde) einmalig aufgerufen, 
*            um z. B. Pins als Eingang oder Ausgang zu definieren.
*/
/*------------------------------------------------------------------------------------------------*/
void setup() {

  wasBinIch = BOOOOOOM;
                                                     
  /* Pin Ein- oder Ausgaenge als solche einstellen! */
  pinMode(RGB_PIN_ROT,   OUTPUT);
  pinMode(RGB_PIN_GRUEN, OUTPUT);
  pinMode(RGB_PIN_BLAU,  OUTPUT);
  pinMode(TASTER_PIN, INPUT);
  pinMode(ZUFALLS_START_PIN,  INPUT);
 
  /* entscheide was ich bin, wenn es eigentlich egal ist.... */
  randomSeed(analogRead(ZUFALLS_START_PIN));
  if(wasBinIch == EIGENTLICH_EGAL) {
    randomSeed(analogRead(ZUFALLS_START_PIN));
    wasBinIch = (int)random(EIGENTLICH_EGAL); 
  }
 
  /* Zeige durch rotes Blinken was ich gerade bin!  */
  for(int i=0; i<=wasBinIch; i++){
    RGBFarbenEinstellen(255, 0, 0);
    delay(500);
    RGBFarbenEinstellen(0, 0, 0);
    delay(500);
  }  
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Arduino Main Loop
*
*            Wird durchgehend immer wieder durchlaufen, solange das Arduino-Board eingeschaltet ist.
*/
/*------------------------------------------------------------------------------------------------*/
void loop() {
  
  if (wasBinIch == EINE_KERZE) {
    LeuchteWieEineKerze();
  } else  if (wasBinIch == ZIEMLICH_BUNT) {
    MaleAlleMeineFarben();  
  } else if (wasBinIch == EINE_TASCHENLAMPE) {
    MeineTaschenlampe();  
  } else if (wasBinIch == ROT_GRUEN_BLAU) {
    RotGruenBlau();
  } else if (wasBinIch == BOOOOOOM) {
    Booom();
  }
  
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Taschenlampe
*
*            Diese Funktion schaltet die Lampe ein, wenn der Taster gedrueckt ist
*            und eben aus wenn dieser losgelassen wird.
*/
/*------------------------------------------------------------------------------------------------*/
void MeineTaschenlampe(void) {
  
  /* Schaue nach, ob der Taster gedrueckt ist: */
  if (digitalRead(TASTER_PIN) == LOW) {
    /* Taschenlampe einschalten.... */
    RGBFarbenEinstellen(255, 255, 255);
  } else {
    /* ... oder ausschalten! */
    RGBFarbenEinstellen(0, 0, 0);
  }
  delay(100);
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Kerzen Simulation
*
*            Diese Funktion laesst die RGB LED wie eine Kerze flackern.
*/
/*------------------------------------------------------------------------------------------------*/
void LeuchteWieEineKerze(void) {
  
  RGBFarbenEinstellen(random(135, 255), random(135, 255), random(135, 255));
  delay(random(100));
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Lass die Lampe in verschiedener Farben leuchten.            
* 
*/
/*------------------------------------------------------------------------------------------------*/
void MaleAlleMeineFarben(void) {
  
  RGBFarbenEinstellen(AlleMeineHTMLFarben[aktuelleFarbe][0], 
                      AlleMeineHTMLFarben[aktuelleFarbe][1],
                      AlleMeineHTMLFarben[aktuelleFarbe][2]);

  /* Wurde das schwarze Ende der Farben erreicht? */
  if ((AlleMeineHTMLFarben[aktuelleFarbe][0] == 0x00) && 
      (AlleMeineHTMLFarben[aktuelleFarbe][1] == 0x00) &&
      (AlleMeineHTMLFarben[aktuelleFarbe][2] == 0x00)) {
    aktuelleFarbe = 0;      
  } else {
    aktuelleFarbe++;
  }
                           
  delay(random(50, 250));
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Nacheinander werden ROT, GRUEN und dann BLAU langsam heller
*            
*/
/*------------------------------------------------------------------------------------------------*/
void RotGruenBlau(void) {
  
  for (int rot=0; rot<255; rot++){
    RGBFarbenEinstellen(rot, 0, 0);
    delay(random(10, 55));
  }
  for (int rot=255; rot>0; rot--){
    RGBFarbenEinstellen(rot, 0, 0);
    delay(random(10, 55));
  }
 
  for (int gruen=0; gruen<255; gruen++){
    RGBFarbenEinstellen(0, gruen, 0);
    delay(random(10, 55));
  }
  for (int gruen=255; gruen>0; gruen--){
    RGBFarbenEinstellen(0, gruen, 0);
    delay(random(10, 55));
  }
  
  for (int blau=0; blau<255; blau++){
    RGBFarbenEinstellen(0, 0, blau);
    delay(random(10, 05));
  }
  for (int blau=255; blau>0; blau--){
    RGBFarbenEinstellen(0, 0, blau);
    delay(random(10, 55));
  } 

  RGBFarbenEinstellen(0, 0, 0);
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Soll so was wie eine tickende Bombe sein, welche dann explodiert!
*            
*/
/*------------------------------------------------------------------------------------------------*/
void Booom(void) {

  if (digitalRead(TASTER_PIN) == LOW) {
    for(int countdown=1000; countdown>50; countdown-=25){
      if (countdown > 700){
        RGBFarbenEinstellen(0, 255, 0);
      } else if (countdown > 400){
        RGBFarbenEinstellen(0, 0, 255  );
      } else {
        RGBFarbenEinstellen(255, 0, 0);
      }
      delay(countdown);
      RGBFarbenEinstellen(0, 0, 0);
      delay(countdown);
    }

    aktuelleFarbe = 0;
    do { 
      RGBFarbenEinstellen(AlleMeineHTMLFarben[aktuelleFarbe][0], 
                          AlleMeineHTMLFarben[aktuelleFarbe][1],
                          AlleMeineHTMLFarben[aktuelleFarbe][2]);
    
      /* Wurde das schwarze Ende der Farben erreicht? */
      if ((AlleMeineHTMLFarben[aktuelleFarbe][0] == 0x00) && 
          (AlleMeineHTMLFarben[aktuelleFarbe][1] == 0x00) &&
          (AlleMeineHTMLFarben[aktuelleFarbe][2] == 0x00)) {
        aktuelleFarbe = 0;      
      } else {
        aktuelleFarbe++;
      }
                               
      delay(random(50, 150));
    } while (aktuelleFarbe != 0);
    
  }  
  
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief     Farben der RGB einstellen
*
*            Diese Funktion setzt die PWM Ausgaenge für die Farben Rot, Gruen und Blau.
*            Die drei Parameter fuer die Farben sind dabei so angeordnet, das sie direkt 
*            dem HTML (Internet) Farbcode entsprechen.
*            Z.B. #FF0000 - das stellt rot dar also rot ist maximal(FF is 255 als Dezimalzahl) 
*            und gruen, blau sind 0.
*/
/*------------------------------------------------------------------------------------------------*/
void RGBFarbenEinstellen(int rot, int gruen, int blau)
{
  analogWrite(RGB_PIN_ROT, rot);
  analogWrite(RGB_PIN_GRUEN, gruen);
  analogWrite(RGB_PIN_BLAU, blau);  
}





