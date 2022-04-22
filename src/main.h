/* 

Her kjører vi de diverse xxxxx.h filene i riktig rekkefølge for å oppnå resultatet vi vil ha.

Denne metoden blir brukt grunnet minne begrensinger på arduino. Ved å lage flere forskjellige scripts som bruker #define, får man brukt mindre minne.
Det er fallgruver med denne metoden, men det har jeg ikke helt forstått meg på enda.

Rekkefølgen til #include xxxxx.h er viktig, og vil påvirke resultatet.

? Dette virker som en veldig effektiv og fin måte å kjøre programmet strukturert på.

TODO: 1. Det som er kommentert ut er de filene som er hos grbl. vi burde sjekke ut alle filene og finne det som er nødvendig for oss. 
TODO: 2. Se NØYE over gcode, motion_control, planner, seriel, protocol, eeprom og stepper. Disse virker som de mest essentielle delene av programmet for vårt bruk.
*/
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
#include "system.h" // TODO: Luke ut unødvendig kode, forstå hva de gjør og hvorfor. Dette er håndtering av system. Er nok en del her vi kan se vekk i fra, vi må bare luke ut hva
#include "defaults.h" // Dette er en solid måte å sette grunninnstillinger til maskinen på. Vi burde se på måter vi kan endre det til å passe vårt program.
#include "cpu_map.h" // Dette er en solid måte å sette pins på, ser ingen grunn til å gjøre endringer.
#include "eeprom.h" // TODO: Greit å få på stell, arduino har 1kB EEPROM
#include "gcode.h"  // TODO: Lite vi kan gjøre her, annet enn å lage vår egen g-kode/kommando linje tolker. vi kan ta deler fra deres.
#include "limits.h" // TODO: Burde se på hvordan vi kan få dette til på egenhånd. Deres måte er optimalisert, men problematisk å forstå.
#include "motion_control.h" // TODO: 
#include "planner.h" // TODO: IKKE SETT PÅ
#include "print.h" // TODO: IKKE SETT PÅ
#include "protocol.h" // TODO: IKKE SETT PÅ
#include "report.h" // TODO: IKKE SETT PÅ
#include "serial.h" // TODO: IKKE SETT PÅ
#include "stepper.h" // TODO: IKKE SETT PÅ. VI BURDE NOK VURDERE STEP/DIR
#endif