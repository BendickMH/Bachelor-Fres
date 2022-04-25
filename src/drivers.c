#include "main.h"


void define_drivers(){  
// Oppsett av Motor drivere
TMC5160Stepper DRIVER_X = TMC5160Stepper(9,11,12,13); // CSN,MOSI,MISO,SCK
TMC5160Stepper DRIVER_Y = TMC5160Stepper(8,11,12,13); // CSN,MOSI,MISO,SCK
TMC5160Stepper DRIVER_Z = TMC5160Stepper(7,11,12,13); // CSN,MOSI,MISO,SCK
}



void setup_driver(){
    if (true)
    {
        DRIVER_X.AMAX() = DRIVER_X.AMAX(10000);
    }
}