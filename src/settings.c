/*
    !! Settings.c og settings.c er noen av de "bibliotekene" vi burde se mer på og justere til vårt behov. mulig vi ikke trenger noe av det
    !! er også mulig vi kan hardkode inn det vi vil for settings, ettersom dette er en maskin med spesifikt bruk og instillinger og trenger ikke å være mottakelig for
    !! andre settings.
*/

#include "main.h"

#define LINE_BUFFER_SIZE 80 // !! SKAL DEKLARERES I protocol.h AV EN ELLER ANNEN GRUNN, MEN JEG LA DEN HER FOR Å UNNGÅ PROBLEMER

settings_t settings;

// Funksjon for å lagre startup linjer til EEPROM
void settings_store_startup_line(uint8_t n, char *line) // Tar inn en int og en linje (*line peker på en annen variabel)
{
  uint32_t addr = n*(LINE_BUFFER_SIZE+1)+EEPROM_ADDR_STARTUP_BLOCK; // Finner adressen hvor den skal lagre linjene
  memcpy_to_eeprom_with_checksum(addr,(char*)line, LINE_BUFFER_SIZE); // Lagrer linjen i valgt adresse
}

// Funksjon for å lagre "build" info i EEPROM
void settings_store_build_info(char *line)
{
  memcpy_to_eeprom_with_checksum(EEPROM_ADDR_BUILD_INFO,(char*)line, LINE_BUFFER_SIZE); 
}

// Funksjon for å lagre koordinat data parametere i EEPROM
void settings_write_coord_data(uint8_t coord_select, float *coord_data)
{  
  uint32_t addr = coord_select*(sizeof(float)*N_AXIS+1) + EEPROM_ADDR_PARAMETERS;
  memcpy_to_eeprom_with_checksum(addr,(char*)coord_data, sizeof(float)*N_AXIS);
}

// Funksjon for å lagre globale settings i EEPROM
void write_global_settings() 
{
  memcpy_to_eeprom_with_checksum(EEPROM_ADDR_GLOBAL, (char*)&settings, sizeof(settings_t));
}

// Funksjon for å sette innstillinger tilbake til default, i vårt tilfelle defaults_bachelorfres // !! Funksjonen får error fordi default ikke blir definert førts, må finne løsning
void settings_restore(uint8_t restore_flag) {  
  if (restore_flag & SETTINGS_RESTORE_DEFAULTS) {
	settings.pulse_microseconds = DEFAULT_STEP_PULSE_MICROSECONDS; // Setter som definert i defaults_bachelorfres
	settings.stepper_idle_lock_time = DEFAULT_STEPPER_IDLE_LOCK_TIME; // Setter som definert i defaults_bachelorfres
	settings.step_invert_mask = DEFAULT_STEPPING_INVERT_MASK; // Setter som definert i defaults_bachelorfres
	settings.dir_invert_mask = DEFAULT_DIRECTION_INVERT_MASK; // Setter som definert i defaults_bachelorfres
	settings.status_report_mask = DEFAULT_STATUS_REPORT_MASK; // Setter som definert i defaults_bachelorfres
	settings.junction_deviation = DEFAULT_JUNCTION_DEVIATION; // Setter som definert i defaults_bachelorfres
	settings.arc_tolerance = DEFAULT_ARC_TOLERANCE; // Setter som definert i defaults_bachelorfres
	settings.homing_dir_mask = DEFAULT_HOMING_DIR_MASK; // Setter som definert i defaults_bachelorfres
	settings.homing_seek_rate = DEFAULT_HOMING_SEEK_RATE; // Setter som definert i defaults_bachelorfres
	settings.homing_feed_rate = DEFAULT_HOMING_FEED_RATE; // Setter som definert i defaults_bachelorfres
	settings.homing_debounce_delay = DEFAULT_HOMING_DEBOUNCE_DELAY; // Setter som definert i defaults_bachelorfres
	settings.homing_pulloff = DEFAULT_HOMING_PULLOFF; // Setter som definert i defaults_bachelorfres

	settings.flags = 0;
	if (DEFAULT_REPORT_INCHES) { settings.flags |= BITFLAG_REPORT_INCHES; } // Setter settings.flags lik 1 om ett av bittene er lik 1
	if (DEFAULT_INVERT_ST_ENABLE) { settings.flags |= BITFLAG_INVERT_ST_ENABLE; } // Setter settings.flags lik 1 om ett av bittene er lik 1
	if (DEFAULT_INVERT_LIMIT_PINS) { settings.flags |= BITFLAG_INVERT_LIMIT_PINS; } // Setter settings.flags lik 1 om ett av bittene er lik 1
	if (DEFAULT_SOFT_LIMIT_ENABLE) { settings.flags |= BITFLAG_SOFT_LIMIT_ENABLE; } // Setter settings.flags lik 1 om ett av bittene er lik 1
	if (DEFAULT_HARD_LIMIT_ENABLE) { settings.flags |= BITFLAG_HARD_LIMIT_ENABLE; } // Setter settings.flags lik 1 om ett av bittene er lik 1
	if (DEFAULT_HOMING_ENABLE) { settings.flags |= BITFLAG_HOMING_ENABLE; } // Setter settings.flags lik 1 om ett av bittene er lik 1
  
	settings.steps_per_mm[X_AXIS] = DEFAULT_X_STEPS_PER_MM; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.steps_per_mm[Y_AXIS] = DEFAULT_Y_STEPS_PER_MM; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.steps_per_mm[Z_AXIS] = DEFAULT_Z_STEPS_PER_MM; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.max_rate[X_AXIS] = DEFAULT_X_MAX_RATE; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.max_rate[Y_AXIS] = DEFAULT_Y_MAX_RATE; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.max_rate[Z_AXIS] = DEFAULT_Z_MAX_RATE; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.acceleration[X_AXIS] = DEFAULT_X_ACCELERATION; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.acceleration[Y_AXIS] = DEFAULT_Y_ACCELERATION; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.acceleration[Z_AXIS] = DEFAULT_Z_ACCELERATION; // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.max_travel[X_AXIS] = (-DEFAULT_X_MAX_TRAVEL); // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.max_travel[Y_AXIS] = (-DEFAULT_Y_MAX_TRAVEL); // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres
	settings.max_travel[Z_AXIS] = (-DEFAULT_Z_MAX_TRAVEL);  // Setter Hastighet, Akselerasjon og andre settings som definert i defaults_bachelorfres   

	write_global_settings(); // kjører funksjonen write_global_settings(), Les mer om hva den gjør i settings.c
  }
  
  if (restore_flag & SETTINGS_RESTORE_PARAMETERS) {
	uint8_t idx; // lager index variabel
	float coord_data[N_AXIS];
	memset(&coord_data, 0, sizeof(coord_data));
	for (idx=0; idx <= SETTING_INDEX_NCOORD; idx++) { settings_write_coord_data(idx, coord_data); }
  }
  
  if (restore_flag & SETTINGS_RESTORE_STARTUP_LINES) {
	#if N_STARTUP_LINE > 0
	eeprom_put_char(EEPROM_ADDR_STARTUP_BLOCK, 0);
	#endif
	#if N_STARTUP_LINE > 1
	eeprom_put_char(EEPROM_ADDR_STARTUP_BLOCK+(LINE_BUFFER_SIZE+1), 0);
	#endif
  }
  
  if (restore_flag & SETTINGS_RESTORE_BUILD_INFO) { eeprom_put_char(EEPROM_ADDR_BUILD_INFO , 0); }
}

// Funksjon for å lese startup linjen som er lagret i EEPROM.
uint8_t settings_read_startup_line(uint8_t n, char *line)
{
  uint32_t addr = n*(LINE_BUFFER_SIZE+1)+EEPROM_ADDR_STARTUP_BLOCK;
  if (!(memcpy_from_eeprom_with_checksum((char*)line, addr, LINE_BUFFER_SIZE))) {
    // Reset line with default value
    line[0] = 0; // Empty line
    settings_store_startup_line(n, line);
    return(false);
  }
  return(true);
}

// Reads startup line from EEPROM. Updated pointed line string data.
uint8_t settings_read_build_info(char *line)
{
  if (!(memcpy_from_eeprom_with_checksum((char*)line, EEPROM_ADDR_BUILD_INFO, LINE_BUFFER_SIZE))) {
    // Reset line with default value
    line[0] = 0; // Empty line
    settings_store_build_info(line);
    return(false);
  }
  return(true);
}


// Read selected coordinate data from EEPROM. Updates pointed coord_data value.
uint8_t settings_read_coord_data(uint8_t coord_select, float *coord_data)
{
  uint32_t addr = coord_select*(sizeof(float)*N_AXIS+1) + EEPROM_ADDR_PARAMETERS;
  if (!(memcpy_from_eeprom_with_checksum((char*)coord_data, addr, sizeof(float)*N_AXIS))) {
    // Reset with default zero vector
    clear_vector_float(coord_data); 
    settings_write_coord_data(coord_select,coord_data);
    return(false);
  }
  return(true);
}  


// Initialize the config subsystem
void settings_init() {
  if(!read_global_settings()) {
    settings_restore(SETTINGS_RESTORE_ALL); // Force restore all EEPROM data.
  }
}
