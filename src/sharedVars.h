/*

Delte variabler og funksjoner til diverse andre kildefiler

*/

#ifndef sharedVars_h
#define sharedVars_h

#define false 0
#define true 1


// Akse variabler
#define N_AXIS 3 // antall akser vi har
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

// CoreXY motor assignments // TODO: må sjekke opp i hva dette egentlig er, og om vi trenger det
#ifdef COREXY
    #define A_MOTOR X_AXIS // Må være X
    #define B_MOTOR Y_AXIS // Må være Y
#endif

// Konverteringer (Ikke så veldig behjelpelig for oss)
#define MM_PER_INCH (25.40)
#define INCH_PER_MM (0.0393701)
#define TICKS_PER_MICROSECOND (F_CPU/1000000)


// Makroer
#define clear_vector(a) memset(a, 0, sizeof(a))
#define clear_vector_float(a) memset(a, 0.0, sizeof(float)*N_AXIS)
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

// Bitfielding og masking, C++ greier // TODO: må lese mer på det. mye handler om shifting av bits, sjekking av bits osv. HVOR BRUKES DETTE?!
#define bit(n) (1<<n) // Venstre shifter bitet feks 0001 -> 0010, shifter like mye som andre operanden, i dette tilfellet n ganger
#define bit_true_atomic(x,mask) {uint8_t sreg = SREG; cli(); (x) |= (mask); SREG = sreg; }
#define bit_false_atomic(x,mask) {uint8_t sreg = SREG; cli(); (x) &= ~(mask); SREG = sreg; }
#define bit_toggle_atomic(x,mask) {uint8_t sreg = SREG; cli(); (x) ^= (mask); SREG = sreg; }
#define bit_true(x,mask) (x) |= (mask)
#define bit_false(x,mask) (x) &= ~(mask)
#define bit_istrue(x,mask) ((x & mask) != 0)
#define bit_isfalse(x,mask) ((x & mask) == 0)

// Read a floating point value from a string. Line points to the input buffer, char_counter 
// is the indexer pointing to the current character of the line, while float_ptr is 
// a pointer to the result variable. Returns true when it succeeds

uint8_t read_float(char *line, uint8_t *char_counter, float *float_ptr);

// Delays variable-defined milliseconds. Compiler compatibility fix for _delay_ms().

void delay_ms(uint16_t ms);

// Delays variable-defined microseconds. Compiler compatibility fix for _delay_us().
void delay_us(uint32_t us);

// Computes hypotenuse, avoiding avr-gcc's bloated version and the extra error checking.
float hypot_f(float x, float y);







#endif