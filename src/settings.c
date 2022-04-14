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

// Funksjon for å sette innstillinger tilbake til default, i vårt tilfelle defaults_bachelorfres 
void settings_restore(uint8_t restore_flag) {  
  if (restore_flag & SETTINGS_RESTORE_DEFAULTS) {
	settings.pulse_microseconds = DEFAULT_STEP_PULSE_MICROSECONDS;
	settings.stepper_idle_lock_time = DEFAULT_STEPPER_IDLE_LOCK_TIME;
	settings.step_invert_mask = DEFAULT_STEPPING_INVERT_MASK;
	settings.dir_invert_mask = DEFAULT_DIRECTION_INVERT_MASK;
	settings.status_report_mask = DEFAULT_STATUS_REPORT_MASK;
	settings.junction_deviation = DEFAULT_JUNCTION_DEVIATION;
	settings.arc_tolerance = DEFAULT_ARC_TOLERANCE;
	settings.homing_dir_mask = DEFAULT_HOMING_DIR_MASK;
	settings.homing_feed_rate = DEFAULT_HOMING_FEED_RATE;
	settings.homing_seek_rate = DEFAULT_HOMING_SEEK_RATE;
	settings.homing_debounce_delay = DEFAULT_HOMING_DEBOUNCE_DELAY;
	settings.homing_pulloff = DEFAULT_HOMING_PULLOFF;

	settings.flags = 0;
	if (DEFAULT_REPORT_INCHES) { settings.flags |= BITFLAG_REPORT_INCHES; }
	if (DEFAULT_INVERT_ST_ENABLE) { settings.flags |= BITFLAG_INVERT_ST_ENABLE; }
	if (DEFAULT_INVERT_LIMIT_PINS) { settings.flags |= BITFLAG_INVERT_LIMIT_PINS; }
	if (DEFAULT_SOFT_LIMIT_ENABLE) { settings.flags |= BITFLAG_SOFT_LIMIT_ENABLE; }
	if (DEFAULT_HARD_LIMIT_ENABLE) { settings.flags |= BITFLAG_HARD_LIMIT_ENABLE; }
	if (DEFAULT_HOMING_ENABLE) { settings.flags |= BITFLAG_HOMING_ENABLE; }
  
	settings.steps_per_mm[X_AXIS] = DEFAULT_X_STEPS_PER_MM;
	settings.steps_per_mm[Y_AXIS] = DEFAULT_Y_STEPS_PER_MM;
	settings.steps_per_mm[Z_AXIS] = DEFAULT_Z_STEPS_PER_MM;
	settings.max_rate[X_AXIS] = DEFAULT_X_MAX_RATE;
	settings.max_rate[Y_AXIS] = DEFAULT_Y_MAX_RATE;
	settings.max_rate[Z_AXIS] = DEFAULT_Z_MAX_RATE;
	settings.acceleration[X_AXIS] = DEFAULT_X_ACCELERATION;
	settings.acceleration[Y_AXIS] = DEFAULT_Y_ACCELERATION;
	settings.acceleration[Z_AXIS] = DEFAULT_Z_ACCELERATION;
	settings.max_travel[X_AXIS] = (-DEFAULT_X_MAX_TRAVEL);
	settings.max_travel[Y_AXIS] = (-DEFAULT_Y_MAX_TRAVEL);
	settings.max_travel[Z_AXIS] = (-DEFAULT_Z_MAX_TRAVEL);    

	write_global_settings();
  }
  
  if (restore_flag & SETTINGS_RESTORE_PARAMETERS) {
	uint8_t idx;
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


