/*

Dette er brukt til mapping av pinner på arduino, til senere referanse. Vi endrer nødvendige definerte variabler i forhold til hvordan pin oppsettet vårt blir ved sluttprodukt.

Det skal KUN defineres PINS

*/
// TODO: Sette pin nummer til riktig pin variabel etter kobling

// Seriell port pinner
#define SERIAL_RX      USART0_RX_vect
#define SERIAL_UDRE    USART0_UDRE_vect

// SPI Spesifikke pins og masker
#define SPI_DDR           DDRB
#define SPI_PORT      PORTB
#define SPI_PIN           PINB
#define STEP_EN_BIT       2 // Digital: 2
#define STEP_MOSI_BIT     5 // Digital: 11
#define STEP_MISO_BIT     6 // Digital: 12
#define STEP_SCK_BIT      7 // Digital: 13
#define SPI_MASK          ((1<<STEP_EN_BIT)|(1<<STEP_MOSI_BIT)|(1<<STEP_MISO_BIT)|(1<<STEP_SCK_BIT))

// Chip select pins og chip select maske
#define CSN_PORT          PORTH
#define CSN_DDR           DDRH
#define CSN_PIN           PINH
#define X_CSN_BIT         6 // Digital: 9
#define Y_CSN_BIT         5 // Digital: 8
#define Z_CSN_BIT         4 // Digital: 7
#define CSN_MASK         ((1<<X_CSN_BIT)|(1<<Y_CSN_BIT)|(1<<Z_CSN_BIT))

// Definerer bruker kontroll pinner
#define CONTROL_DDR       DDRK
#define CONTROL_PIN       PINK
#define CONTROL_PORT      PORTK
#define RESET_BIT         0  // Analog: 8
#define FEED_HOLD_BIT     1  // Analog: 9
#define CYCLE_START_BIT   2  // Analog: 10
#define SAFETY_DOOR_BIT   3  // Analog: 11
#define CONTROL_INT       PCIE2  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT2_vect
#define CONTROL_PCMSK     PCMSK2 // Pin change interrupt register
#define CONTROL_MASK      ((1<<RESET_BIT)|(1<<FEED_HOLD_BIT)|(1<<CYCLE_START_BIT)|(1<<SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK CONTROL_MASK // May be re-defined to only invert certain control pins.

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
#define LIMIT_DDR         DDRD
#define LIMIT_PIN         PIND
#define LIMIT_PORT        PORTD
#define X_LIMIT_MAX_BIT   0 // Com: 21
#define X_LIMIT_MIN_BIT   1 // Com: 20
#define Y_LIMIT_MAX_BIT   2 // Com: 19
#define Y_LIMIT_MIN_BIT   3 // Com: 18
#define LIMIT_MASK        ((1<<X_LIMIT_MAX_BIT)|(1<<X_LIMIT_MIN_BIT)|(1<<Y_LIMIT_MAX_BIT)|(1<<Y_LIMIT_MIN_BIT)) // All limit bits

#define LIMIT_INT         PCIE0  // Pin change interrupt enable pin // ? Vet ikke hva er
#define LIMIT_INT_vect    PCINT0_vect // noe her // ? vet ikke hva er
#define LIMIT_PCMSK       PCMSK0 // Pin change interrupt register // ? Vet ikke hva er