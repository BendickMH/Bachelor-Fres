/*

Dette er brukt til mapping av pinner på arduino, til senere referanse. Vi endrer nødvendige definerte variabler i forhold til hvordan pin oppsettet vårt blir ved sluttprodukt.

Det skal KUN defineres PINS

*/


// Seriell port pinner
#define SERIAL_RX USART_RX_vect
#define USART_UDRE_vect

// Delte motor pinner
#define STEP_EN
#define STEP_MOSI
#define STEP_MISO
#define STEP_SCK

// X-Akse spesifikk pins
#define X_CN

// Y-Akse spesifikk pins
#define Y_CN

// Z-Akse spesifikk pins
#define Z_CN

// Limit switcher/Interrupts
#define X_LIMIT_MIN
#define Y_LIMIT_MIN

#define X_LIMIT_MAX
#define Y_LIMIT_MAX
