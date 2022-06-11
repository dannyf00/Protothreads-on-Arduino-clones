//PIC24duino code
// - using PIC24FJxxGA004/104, and GB004 family (GA002/004, GA102/104, and GB002/004 families)
// - free running timer2 for ticks, pwm and input capture
// -
// - version history
// - v2.0, 5/15/2021: simplified port
// - v2.1, 5/26/2021: implemented SystemCoreClockUpdate() - to be executed during mcu initialization or after oscillator reconfiguration
// - v2.2, 6/06/2021: implemented hardware CRC (16-bit only).
// - v2.3, 6/07/2021: revised rtcc implementation
// - v2.4, 6/16/2021: updated to support GB002/004 chips
// - v2.5, 6/19/2021: implemented output compare (dah!)
// - v2.6, 5/19/2022: output compare routines no longer advance compare registers
// - v2.7, 5/24/2022: simplified support for GA00x, GA10x, and GB00x devices
// - v2.8, 5/24/2022: added support for C30 compiler
// - v2.9, 6/04/2022: support IO port A..G
//
//
//               PIC24FJ
//              |=====================|
//    Vcc       |                     |
//     |        |                Vcap |>--[.1u]-+->GND
//     |        |                     |         |
//     +-[10K]-<| MCLR        DISVreg |>--------+
//              |                     |
//              |                     |
//     +------->| OSCI            Vdd |>--+------>Vcc
//  [Xtal]      |                     | [.1u]
//     +-------<| OSCO            Vss |>--+------>GND
//              |                     |
//              |                 RP0 |>---------->Uart2TX
//              |                     |
//              |                 RB5 |>---------->LED
//              |                     |
//              |                     |
//              |                     |
//              |                     |
//              |                     |
//              |                     |
//              |                     |
//              |                     |
//              |                     |
//              |=====================|
//
//
#include "pic24duino.h"					//we use pic24duino
#include "pt.h"							//we use proto threads

//hardware configuration
#define LED				PB5				//led pin
#define LED1_DLY		(F_CPU / 7)		//duration of delay
#define LED2_DLY		(F_CPU / 83)	//duration of delay
#define U2_DLY			(F_CPU/3)		//print to uart2 every second
#define U3_DLY			(F_CPU/1)		//print to uart2 every second
//end hardware configuration

//global defines

//global variables
struct pt pt1, pt2, pt3, pt4;			//protothreads 1/2/3

//thread 1
//blinking led at LED1_DLY interval
//no need to use while (1) loop
static int led1(struct pt *pt) {
	static uint32_t tick0=0;

	PT_BEGIN(pt);
	//while (1) {
		PT_WAIT_UNTIL(pt, ticks() - tick0 > LED1_DLY);	//hold execution until enough time has passed
		tick0+= LED1_DLY;						//advance the tick
		pinFlip(LED);							//task1=flip the led
	//}
	PT_END(pt);
}

//thread 2
//blinking the same led at LED2_DLY interval
//no need to use while (1) loop
static int led2(struct pt *pt) {
	static uint32_t tick0=0;

	PT_BEGIN(pt);
	//while (1) {
		PT_WAIT_UNTIL(pt, ticks() - tick0 > LED2_DLY);	//hold execution until enough time has passed
		tick0+= LED2_DLY;						//advance the tick
		pinFlip(LED);							//task2=flip the led
	//}
	PT_END(pt);
}

//thread 3
//print to uart
//OK to use while(1) loop
static int u2Msg(struct pt *pt) {
	static uint32_t tick0=0;

	PT_BEGIN(pt);
	while (1) {
		PT_WAIT_UNTIL(pt, ticks() - tick0 > U2_DLY);	//hold execution until enough time has passed
		tick0+= U2_DLY;							//advance the tick
		//u2Print("F_CPU=                    ", F_CPU);	//print msg
		uart2Puts("U2Msg Print... -> ");
		u2Print("tick0=                    ", tick0);	//print msg
		u2Println();									//print a line return
	}
	PT_END(pt);
}

//thread 4
//print to uart
//no need to use while (1) loop
static int u3Msg(struct pt *pt) {
	static uint32_t tick0=0;

	PT_BEGIN(pt);
	//while (1) {
		PT_WAIT_WHILE(pt, ticks() - tick0 < U3_DLY);	//hold execution until enough time has passed
		tick0+= U3_DLY;							//advance the tick
		//u2Print("F_CPU=                    ", F_CPU);	//print msg
		uart2Puts("U3Msg Print... -> ");
		u2Print("tick0=                    ", tick0);	//print msg
		u2Println();									//print a line return
	//}
	PT_END(pt);
}

//user defined set up code
void setup(void) {
    pinMode(LED, OUTPUT);				//led as output pin

    //initialize the uart
    //uart1Init(UART_BR9600);				//initialize uart1
    uart2Init(UART_BR9600);				//initialize uart2

	ei();
}

//user defined main loop
void loop(void) {
	//running through all threads
	led1(&pt1);						//pt1
	led2(&pt2);						//pt2
	u2Msg(&pt3);					//pt3
	u3Msg(&pt4);					//pt4
}

