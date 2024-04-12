#include "mbed.h"
#include "arm_book_lib.h"

#define TEST_C  0
#define TEST_CPP  1
#define TEST_X  (TEST_C)

int main()
{
    // El concepto de clases se incluye en C++, por lo tanto las clases DigitalIn y DigitalOut no deber'ia utilizarse para usar solo C
   // Haciendo step in se verifica que funciones de las librerias usan las clases usadas y se reemplaza para igualar el comportamiento 
    #if(TEST_X == TEST_CPP)
        DigitalIn gasDetector(D2);
        DigitalIn overTempDetector(D3);
        DigitalIn alarmOffButton(BUTTON1);

        DigitalOut alarmLed(LED1);

        gasDetector.mode(PullDown);
        overTempDetector.mode(PullDown);

        alarmLed = OFF;

        bool alarmState = OFF;

        while (true) {

            if ( gasDetector || overTempDetector ) {
                alarmState = ON;
            }

            alarmLed = alarmState;

            if ( alarmOffButton ) {
                alarmState = OFF;
            }
        }
    #endif

    //Como ventaja es menos abstacto y el entendimiento del programa es mayor en cuanto a saber que hace a bajo nivel
    //Como desventaja es claramente mas sencillo utilizar clases de C++, ahorrando codigo y siendo mas claro

    #if(TEST_X == TEST_C)
        PinName gasDetectorPin = D2;
        PinName overTempDetectorPin = D3;
        PinName alarmOffButtonPin = BUTTON1;

        PinName alarmLedPin = LED1;

        gpio_t gasDetectorPinObj;
        gpio_t overTempDetectorPinObj;
        gpio_t alarmOffButtonPinObj;
        gpio_t alarmLedPinObj;

        gpio_init_in_ex(&gasDetectorPinObj, gasDetectorPin, PullDown);
        gpio_init_in_ex(&overTempDetectorPinObj, overTempDetectorPin, PullDown);
        gpio_init_in(&alarmOffButtonPinObj, alarmOffButtonPin);
        gpio_init_out(&alarmLedPinObj, alarmLedPin);

        gpio_write(&alarmLedPinObj, OFF);

        bool alarmState = OFF;

        while (true) {

            if ( gpio_read(&gasDetectorPinObj) == 1 || gpio_read(&overTempDetectorPinObj) == 1){
                alarmState = ON;
                printf("gasDetector: %d\n", gpio_read(&gasDetectorPinObj);
                printf("overTempDetector: %d\n", gpio_read(&overTempDetectorPinObj);
                printf("alarmLED: %d\n", gpio_read(&alarmLedPinObj);
            }

            gpio_write(&alarmLedPinObj, alarmState);

            if ( gpio_read(&alarmOffButtonPinObj) == 1) {
                alarmState = OFF;
                printf("gasDetector: %d\n", gpio_read(&gasDetectorPinObj);
                printf("overTempDetector: %d\n", gpio_read(&overTempDetectorPinObj);
                printf("alarmLED: %d\n", gpio_read(&alarmLedPinObj);
            }
        }
    #endif
}