/*

Dette er brukt til mapping av pinner på arduino, til senere referanse. Vi endrer nødvendige definerte variabler i forhold til hvordan pin oppsettet vårt blir ved sluttprodukt.

Det skal KUN defineres PINS

? Dette virker som en bra måte å mappe pins på.
*/
// TODO: Sette pin nummer til riktig pin variabel etter kobling

// Seriell port pinner
#define SERIAL_RX USART_RX_vect
#define USART_UDRE_vect

// !! DETTE ER OM VI  PRØVER SPI, MEN DA MÅ VI FINNE EN LUDDIG MÅTE Å PROGGE DET PÅ !!
// Delte motor pinner
#define STEP_EN
#define STEP_MOSI
#define STEP_MISO
#define STEP_SCK
// X-Akse spesifikk pins
#define X_CSN
// Y-Akse spesifikk pins
#define Y_CSN
// Z-Akse spesifikk pins
#define Z_CSN


//    !! BURDE STERKT VURDERE STEP/DIR !!
// Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_DDR        DDRD
#define STEP_PORT       PORTD
#define X_STEP_BIT      2  // Uno Digital Pin 2 er anbefalt
#define Y_STEP_BIT      3  // Uno Digital Pin 3 er anbefalt
#define Z_STEP_BIT      4  // Uno Digital Pin 4 er anbefalt
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_DDR     DDRD
#define DIRECTION_PORT    PORTD
#define X_DIRECTION_BIT   5  // Uno Digital Pin 5
#define Y_DIRECTION_BIT   6  // Uno Digital Pin 6
#define Z_DIRECTION_BIT   7  // Uno Digital Pin 7
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_DDR    DDRB
#define STEPPERS_DISABLE_PORT   PORTB
#define STEPPERS_DISABLE_BIT    0  // Uno Digital Pin 8
#define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
#define LIMIT_DDR        DDRB
#define LIMIT_PIN        PINB
#define LIMIT_PORT       PORTB
#define X_LIMIT_BIT      1  // Uno Digital Pin 9
#define Y_LIMIT_BIT      2  // Uno Digital Pin 10
#ifdef VARIABLE_SPINDLE // Z Limit pin and spindle enabled swapped to access hardware PWM on Pin 11.  
  #define Z_LIMIT_BIT	   4 // Uno Digital Pin 12
#else
  #define Z_LIMIT_BIT    3  // Uno Digital Pin 11
#endif
#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
#define LIMIT_INT        PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect   PCINT0_vect 
#define LIMIT_PCMSK      PCMSK0 // Pin change interrupt register

// Limit switcher/Interrupts
#define X_LIMIT_MIN
#define Y_LIMIT_MIN

#define X_LIMIT_MAX
#define Y_LIMIT_MAX
