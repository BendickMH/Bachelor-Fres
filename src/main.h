/* 

Her kjører vi de diverse xxxxx.h filene i riktig rekkefølge for å oppnå resultatet vi vil ha.

Denne metoden blir brukt grunnet minne begrensinger på arduino. Ved å lage flere forskjellige scripts som bruker #define, får man brukt mindre minne.
Det er fallgruver med denne metoden, men det har jeg ikke helt forstått meg på enda.

Rekkefølgen til #include xxxxx.h er viktig, og vil påvirke resultatet.

? Dette virker som en veldig effektiv og fin måte å kjøre programmet strukturert på.

TODO: 1. Det som er kommentert ut er de filene som er hos grbl men ikke hos oss. vi burde sjekke ut alle filene og finne det som er nødvendig for oss. 
TODO: 2. Se NØYE over gcode, motion_control, planner, seriel, protocol, eeprom og stepper. Disse virker som de mest essentielle delene av programmet for vårt bruk.
*/
// TODO: Må se nærmere på om hele bibliotek er nødvendig, eller om vi kan hente deler ut for å spare plass.
#ifndef main_h
#define main_h

// Nødvendige bibliotek // TODO: Legge inn #include <TMCStepper.h>, men får konflikter når den legges til. mulig vi må bruke step/dir for enklere bruk av drivere.

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <math.h>
#include <inttypes.h>    
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SPI.h>
#include <Stream.h>

// Selvlagde nødvendige filer
#include "config.h" // TODO: Luke ut unødvendig kode, forstå hva de gjør og hvorfor
#include "sharedVars.h" 
#include "settings.h" // ? Det virker nødvendig, men bør kammes over for å finne det faktisk nødvendige for vårt system
// #include "system.h" // TODO: Luke ut unødvendig kode, forstå hva de gjør og hvorfor
#include "defaults.h" // TODO: Luke ut unødvendig kode, forstå hva de gjør og hvorfor
#include "cpu_map.h" 
// #include "coolant_control.h" // ? Vi har ikke kjøle system, unødvendig
// #include "eeprom.h" // TODO: Greit å få på stell, arduino har 2kb EEPROM
// #include "gcode.h"  // TODO: 
// #include "limits.h" // TODO: 
// #include "motion_control.h" // TODO: 
// "planner.h" // TODO: 
// #include "print.h" // TODO: 
// #include "probe.h" // ? Vi burde ha probe, men tror ikke vi kommer til å komme til det punktet. Unødvendig?
// #include "protocol.h" 
// #include "report.h" 
// #include "serial.h" 
// #include "spindle_control.h" // ? Vi kan ikke kontrollere spindelen, det er bare et verktøy med AV/PÅ
// #include "stepper.h" // ? Vi har eget stepper motor driver bibliotek, mulig vi kan bruke deler av dette
#endif