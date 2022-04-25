#ifndef defaults_h
#define defaults_h

    // Default innstillinger for vår CNC Maskin, oppsettet er tatt fra grbl, men har blitt regnet på og undersøkt av oss
    // !! Viktig at vi regner på det da gutta !!

    // TODO: Se etter instillinger i forhold til listen

  // TODO: Dobbelt sjekke og teste om dette er korrekt
  #define DEFAULT_X_STEPS_PER_MM 3.4996 // Full steps per MM
  #define DEFAULT_Y_STEPS_PER_MM 3.4996 // Full steps per MM
  #define DEFAULT_Z_STEPS_PER_MM 4.5000 // Full steps per MM

  #define DEFAULT_STEP_PER_REVOLUTION 200 // Tilsvarer 1.8 grader rotasjon
  #define DEFAULT_MICROSTEP 256 // Ett mikrostep tilsvarer 0.00703125 grader rotasjon som igjen tilsvarer 0.0011161989941708 mm per mikrostep (I XY RETNING)

  #define DEFAULT_X_MAX_RATE 500.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 500.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 500.0 // mm/min

  // TODO: Finne ut hvordan dette sammenligner med TMCStepper Akselerasjon
  #define DEFAULT_X_ACCELERATION (10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2

 // TODO: Må legge inn riktige mål!
  #define DEFAULT_X_MAX_TRAVEL 500.0 // mm
  #define DEFAULT_Y_MAX_TRAVEL 750.0 // mm
  #define DEFAULT_Z_MAX_TRAVEL 80.0 // mm

  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 0
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK ((BITFLAG_RT_STATUS_MACHINE_POSITION)|(BITFLAG_RT_STATUS_WORK_POSITION))
  #define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 500.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm

#endif