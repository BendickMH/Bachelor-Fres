/* 
  !! Settings.c og settings.c er noen av de "bibliotekene" vi burde se mer på og justere til vårt behov. mulig vi ikke trenger noe av det.
  !! Er også mulig vi kan hardkode inn det vi vil for settings, ettersom dette er en maskin med spesifikt bruk og instillinger og trenger ikke å være mottakelig for
  !! andre settings.
*/

#ifndef settings_h
#define settings_h

#include "main.h" // inkluder main.h som er executable vi uploader til arduino.

// !! REN KOPIERING FRA settings.h !!
// Define bit flag masks for the boolean settings in settings.flag.
#define BITFLAG_REPORT_INCHES      bit(0) // ? usikker om nødvendig, vi bruker mm
#define BITFLAG_INVERT_ST_ENABLE   bit(2)
#define BITFLAG_HARD_LIMIT_ENABLE  bit(3)
#define BITFLAG_HOMING_ENABLE      bit(4)
#define BITFLAG_SOFT_LIMIT_ENABLE  bit(5)
#define BITFLAG_INVERT_LIMIT_PINS  bit(6)
#define BITFLAG_INVERT_PROBE_PIN   bit(7) // ? usikker om nødvendig, vi bruker ikke probe

// Define status reporting boolean enable bit flags in settings.status_report_mask
#define BITFLAG_RT_STATUS_MACHINE_POSITION  bit(0)
#define BITFLAG_RT_STATUS_WORK_POSITION     bit(1)
#define BITFLAG_RT_STATUS_PLANNER_BUFFER    bit(2)
#define BITFLAG_RT_STATUS_SERIAL_RX         bit(3)
#define BITFLAG_RT_STATUS_LIMIT_PINS        bit(4)

// Define settings restore bitflags.
#define SETTINGS_RESTORE_ALL 0xFF // All bitflags
#define SETTINGS_RESTORE_DEFAULTS bit(0)
#define SETTINGS_RESTORE_PARAMETERS bit(1)
#define SETTINGS_RESTORE_STARTUP_LINES bit(2)
#define SETTINGS_RESTORE_BUILD_INFO bit(3)

// Define EEPROM memory address location values for Grbl settings and parameters
// NOTE: The Atmega328p has 1KB EEPROM. The upper half is reserved for parameters and
// the startup script. The lower half contains the global settings and space for future 
// developments.

// ? Dette føles svært nødvendig. mulig disse adressene kan endres. uansett bør det undersøkes

#define EEPROM_ADDR_GLOBAL         1U // Adressen er 1, U betyr at det skal tolkes som unsigned int (kan ikke ha negativ verdi så maks verdi er 4,292,967,295)
#define EEPROM_ADDR_PARAMETERS     512U
#define EEPROM_ADDR_STARTUP_BLOCK  768U
#define EEPROM_ADDR_BUILD_INFO     942U

// Define EEPROM address indexing for coordinate parameters
#define N_COORDINATE_SYSTEM 6  // Number of supported work coordinate systems (from index 1)
#define SETTING_INDEX_NCOORD N_COORDINATE_SYSTEM+1 // Total number of system stored (from index 0)
// NOTE: Work coordinate indices are (0=G54, 1=G55, ... , 6=G59)
#define SETTING_INDEX_G28    N_COORDINATE_SYSTEM    // Home position 1 // Lagring av hjemme posisjon 1.
#define SETTING_INDEX_G30    N_COORDINATE_SYSTEM+1  // Home position 2 // Lagring av hjemme posisjon 2.
// #define SETTING_INDEX_G92    N_COORDINATE_SYSTEM+2  // Coordinate offset (G92.2,G92.3 not supported)

// Define Grbl axis settings numbering scheme. Starts at START_VAL, every INCREMENT, over N_SETTINGS.
#define AXIS_N_SETTINGS          4
#define AXIS_SETTINGS_START_VAL  100 // NOTE: Reserving settings values >= 100 for axis settings. Up to 255.
#define AXIS_SETTINGS_INCREMENT  10  // Must be greater than the number of axis settings



// !! REN KOPIERING MEN NØDVENDIG FOR ANNET BRUK, MÅ SE VIDERE PÅ HVA SOM FAKTISK FOREGÅR !!
// TODO: Se mer på dette, hva er nødvendig og hva er ikke?

typedef struct {

  // Akse innstillinger // ? Settes opp et array med n(akser) antall plasser. slik at man kan stille inn for alle aksene
  float steps_per_mm[N_AXIS];
  float max_rate[N_AXIS];
  float acceleration[N_AXIS];
  float max_travel[N_AXIS];

  // Remaining Grbl settings
  uint8_t pulse_microseconds;
  uint8_t step_invert_mask;
  uint8_t dir_invert_mask;
  uint8_t stepper_idle_lock_time; // If max value 255, steppers do not disable.
  uint8_t status_report_mask; // Mask to indicate desired report data.
  float junction_deviation;
  float arc_tolerance;
  
  uint8_t flags;  // Contains default boolean settings

  uint8_t homing_dir_mask;
  float homing_feed_rate;
  float homing_seek_rate;
  uint16_t homing_debounce_delay;
  float homing_pulloff;
} settings_t;
extern settings_t settings;

// !! KOPIERING FERDIG !!

// Laster inn innstillinger fra EEPROM (EEPROM = electrically erasable programmable read-only memory ----> https://en.wikipedia.org/wiki/EEPROM)
void settings_init();

// Resetter settings tilbake til default verdier, om nødvendig
void settings_restore(uint8_t restore_flag);

// for å sette settings i command vinduet. dette er det som fanger opp når man skriver settings kommando i C# koden
uint8_t settings_store_global_setting(uint8_t parameter, float value);

// Lagrer protokoll linje variabelen som startup i EEPROM
void settings_store_startup_line(uint8_t n, char *line);

// Reads an EEPROM startup line to the protocol line variable // Leser EEPROM startup linjen til protokoll variabel
uint8_t settings_read_startup_line(uint8_t n, char *line);

// lagrer "build" info om maskinen, denne er definert av bruker // ? Unødvendig for vårt bruk, får se om dette kan fjernes
void settings_store_build_info(char *line);

// Leser "build" info om maskinen // ? Unødvendig for vårt bruk, får se om dette kan fjernes
uint8_t settings_read_build_info(char *line);

// Skriver valgt koordinat data til EEPROM // ? nødvendig for lagring av koordinater som hjem posisjon.
void settings_write_coord_data(uint8_t coord_select, float *coord_data);

// Leser valgt koordinat data fra EEPROM
uint8_t settings_read_coord_data(uint8_t coord_select, float *coord_data);

// !! HER ER STEP/DIR OPPSETT, MULIG VI MÅ GÅ OVER TIL DEN LØSNINGEN OM SPI IKKE FUNGERER SOM DET SKAL !!
// Returns the step pin mask according to Grbl's internal axis numbering
uint8_t get_step_pin_mask(uint8_t i);

// Returns the direction pin mask according to Grbl's internal axis numbering
uint8_t get_direction_pin_mask(uint8_t i);
// !!

// Returnerer limit pin masken iforhold til satt fra akse nummerering tidligere
uint8_t get_limit_pin_mask(uint8_t i);

#endif
