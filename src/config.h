/*
    Instillinger som vi vil ha under compile/første oppstart.
    Instillinger som:
        baud rate
        smoothing
        akselerasjons rate osv

? Virker som en bra måte å få opp nødvendige konfigurasjoner på

*/

#ifndef config_h
#define config_h


#include "main.h"

// Hvilke default settings som skal brukes senere. 
#define DEFAULT_BACHELORFRES

// Seriell baud rate som skal bruker til seriell monitor og kommunikasjon
#define BAUD_RATE 115200

// Kommando karakterer // TODO: Må se videre på hva hvilke av disse som er nødvendig for oss, og hva de gjør
#define CMD_STATUS_REPORT '?'    
#define CMD_FEED_HOLD '!'
#define CMD_CYCLE_START '~'
#define CMD_RESET 0x18 // ctrl-x.
#define CMD_SAFETY_DOOR '@' // wat?

// Homing syklus
// Definert for å få en spesifikk hjemme syklus. 
// ? Her lagres en variabel som HOMING_CYCLE_X som en verdi 1<<?_AXIS.
// ?  Eksempel. 1<<Z_AXIS -> Z_AXIS = 2 -> 1 = 00000001. 00000001 << 2 -> 00000100 = 4 -> 1*2^2 = 4. så den får posisjon til tredje bitet.

#define HOMING_CYCLE_0 (1<<Z_AXIS) // Nødvendig for å få Z-aksen vekk
#define HOMING_CYCLE_1 (1<<X_AXIS) // kjører X for å kjører Y senere, på denne måten kan vi dele interrupt pin/limit switch pin for å sette hjem
#define HOMING_CYCLE_2 (1<<Y_AXIS) // kjører Y
// #define HOMINH_CYCLE_1 ((1<<X_AXIS)|(1<<Y_AXIS))   // Kan kjører dette for å kjøre X og Y samtidig

#define N_HOMING_LOCATE_CYCLE 1 // int 1-128

// Hvor mange startup linjer som skal kjøre ved startup. dette er stort sett settings som lagres i EEPROM
#define N_STARTUP_LINE 2 // int 1-2

// Nøyaktiget, antall desimaler
#define N_DECIMAL_COORDVALUE_MM   3 // Coordinate or position value in mm
#define N_DECIMAL_RATEVALUE_MM    0 // Rate or velocity value in mm/min
#define N_DECIMAL_SETTINGVALUE    3 // Decimals for floating point setting values


// For å få en smoothere akkselerasjon // ? Mulig ikke nødvendig med tmc stepper.
#define ACCELERATION_TICKS_PER_SECOND 100 // !! Endres etter behov

// En settings som smoother ut steps i lavere frekvens. så det ikke hakker like mye. // TODO: Se nærmere på hva og hvor dette ligger
#define ADAPTIVE_MULTI_AXIS_STEP_SMOOTHING // Aktivert, må kommentere ut for å fjerne

// Setter hvilken akse man får verkøyt offsett på. 
// siden vårt verktøy er på z_akse er det naturlig at det er der den får offset
#define TOOL_LENGTH_OFFSET_AXIS Z_AXIS

// !! Planleggings konfigurasjoner, for buer, linjer og annet. Disse er nødvendig for motion_control og planning

// Mest brukbart for laserkutter og 3dprinter
#define MINIMUM_JUNCTION_SPEED 0.0 //(mm/min)

// Feed rate er distanse per minutt. her blir minimum satt til 1mm per minut.
#define MINIMUM_FEED_RATE 1.0

// Antall bue iterasjoner med billig kalkulasjon før nøyaktig utregning.
#define N_ARC_CORRECTION 12 // int (1-255) kan økes for kjappere, senkes hvis dårlig "accuracy"

// For enklere og bedre sirkel/semi-sirkel planlegging. bør være større enn 1.2E-7 men ikke mye større enn 5E-7
#define ARC_ANGULAR_TRAVEL_EPSILON 5E-7 // Float (radians)

// Delay når maskinen "dweller", slik at kommandoer kan bli mottat
#define DWELL_TIME_STEP 50 // int 1-255 ms

/* 
    !! ------------------ !!
    !! ERROR SJEKKING HER !!
    !! ------------------ !!
*/

#endif