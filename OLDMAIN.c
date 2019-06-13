#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "pins.h"
#include "ttimer.h"


int main(void)
    {
        int8_t check = 0;
        int8_t i;
        int8_t split;
        tidInit();

        uart_init( 9600 ); // Initialize USB serial at 9600 baud


        setPins();
        timer2();

        TIM2_IRQHandler();

        while(1){

               split = readJoystick();

                if(split == 4) {
                    copyTime(2);
                } else if(split == 8) {
                    copyTime(3);
                } else if(split == 2) {
                    resetTimer();
                    check = 1;
                } else if(split == 1) {

                    if(check == 0) {
                    stopTime();
                    check = 1;

                }   else if(check == 1){
                    startTime();
                    check = 0;
                }
                }



            if (TID.mili == 0){
                if(TID.seconds < 10 && TID.minutes < 10 && TID.hours < 10){
                    gotoxy(0,0);
                    printf("Time since start:  0%d : 0%d : 0%d.",TID.hours,TID.minutes,TID.seconds);
                }
                else if(TID.minutes < 10 && TID.hours < 10){
                    gotoxy(0,0);
                    printf("Time since start:  0%d : 0%d : %d.",TID.hours,TID.minutes,TID.seconds);
                }
                else if(TID.hours < 10){
                    gotoxy(0,0);
                    printf("Time since start:  0%d : %d : %d.",TID.hours,TID.minutes,TID.seconds);

                }  else {
                    gotoxy(0,0);
                    printf("Time since start:  %d : %d : %d.",TID.hours,TID.minutes,TID.seconds);
                }
            }
        }





        while(1){}
}
