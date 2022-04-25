/*

Dette er brukt til mapping av pinner på arduino, til senere referanse. Vi endrer nødvendige definerte variabler i forhold til hvordan pin oppsettet vårt blir ved sluttprodukt.

Det skal KUN defineres PINS

*/
// TODO: Sette pin nummer til riktig pin variabel etter kobling

// Seriell port pinner
#define SERIAL_RX USART_RX_vect
#define USART_UDRE_vect

// SPI Spesifikke pins og masker
#define SPI_DDR DDRB
#define SPI_COM_PORT PORTB
#define STEP_EN_BIT 2 // Digital: 2
#define STEP_MOSI_BIT 5 // Digital: 11
#define STEP_MISO_BIT 6 // Digital: 12
#define STEP_SCK_BIT 7 // Digital: 13
#define SPI_MASK ((1<<STEP_EN_BIT)|(1<<STEP_MOSI_BIT)|(1<<STEP_MISO_BIT)|(1<<STEP_SCK_BIT))

// Chip select pins og chip select maske
#define SPI_CSN_PORT PORTH
#define X_CSN_BIT 6 // Digital: 9
#define Y_CSN_BIT 5 // Digital: 8
#define Z_CSN_BIT 4 // Digital: 7
#define CSN_MASK  ((1<<X_CSN_BIT)|(1<<Y_CSN_BIT)|(1<<Z_CSN_BIT))

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
#define LIMIT_DDR        DDRD
#define LIMIT_PIN        PIND
#define LIMIT_PORT       PORTD
#define X_LIMIT_MAX_BIT   //Com: 21
#define X_LIMIT_MIN_BIT  // Com: 20
#define Y_LIMIT_MAX_BIT  // Com: 19
#define Y_LIMIT_MIN_BIT  // Com: 18
#define LIMIT_MASK       ((1<<X_LIMIT_MAX_BIT)|(1<<X_LIMIT_MIN_BIT)|(1<<Y_LIMIT_MAX_BIT)|(1<<Y_LIMIT_MIN_BIT)) // All limit bits
#define LIMIT_INT        PCIE0  // Pin change interrupt enable pin // ? Vet ikke hva er
#define LIMIT_INT_vect   PCINT0_vect // noe her // ? vet ikke hva er
#define LIMIT_PCMSK      PCMSK0 // Pin change interrupt register // ? Vet ikke hva er