/* 

Her kjører vi de diverse xxxxx.h filene i riktig rekkefølge for å oppnå resultatet vi vil ha.

Denne metoden blir brukt grunnet minne begrensinger på arduino. Ved å lage flere forskjellige scripts som bruker #define, får man brukt mindre minne.
Det er fallgruver med denne metoden, men det har jeg ikke helt forstått meg på enda.

Rekkefølgen til #include xxxxx.h er viktig, og vil påvirke resultatet.

*/
#include <Arduino.h>
#include "config.h"
#include "settings.h"