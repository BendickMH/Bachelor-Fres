/*

Dette er brukt til mapping av pinner på arduino, til senere referanse. Vi endrer nødvendige definerte variabler i forhold til hvordan pin oppsettet vårt blir ved sluttprodukt.

Det skal KUN defineres PINS

? Dette virker som en bra måte å mappe pins på.
*/
// TODO: Sette pin nummer til riktig pin variabel etter kobling

// Seriell port pinner
#define SERIAL_RX USART_RX_vect
#define USART_UDRE_vect

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

// Limit switcher/Interrupts
#define X_LIMIT_MIN
#define Y_LIMIT_MIN

#define X_LIMIT_MAX
#define Y_LIMIT_MAX
