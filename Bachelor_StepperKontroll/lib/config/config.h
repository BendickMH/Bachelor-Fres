/*
    Instillinger som vi vil ha under compile/første oppstart.
    Instillinger som:
        baud rate
        smoothing
        akselerasjons rate osv

*/

#ifndef config_h
#define config_h
// Ikke implementert enda, men må inkludere samlingen av bibliotek og oppsett, feks fra grbl #include "grbl.h", hvor grbl.h inneholder rekkefølgen og alt som skal kjøres

// Seriell baud rate
#define BAUD_RATE 115200

// Kommando karakterer
#define CMD_STATUS_REPORT '?'    // Må se videre på hva hvilke av disse som er nødvendig for oss.
#define CMD_FEED_HOLD '!'
#define CMD_CYCLE_START '~'
#define CMD_RESET 0x18 // ctrl-x.
#define CMD_SAFETY_DOOR '@'

// Homing syklus
// Definert for å få en spesifikk hjemme syklus.
#define HOMING_CYCLE_0 (1<<Z_AXIS) // Nødvendig for å få Z-aksen vekk
#define HOMING_CYCLE_1 (1<<X_AXIS) // kjører X for å kjører Y senere, på denne måten kan vi dele interrupt pin/limit switch pin for å sette hjem
#define HOMING_CYCLE_2 (1<<Y_AXIS) // kjører Y
// #define HOMINH_CYCLE_1 ((1<<X_AXIS)|(1<<Y_AXIS))   // Kan kjører dette for å kjøre X og Y samtidig