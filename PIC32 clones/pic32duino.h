#ifndef _PIC32DUINO_H
#define _PIC32DUINO_H

//PIC32duino code
// - using PIC32MX1xx/2xx
// - free running core timer for ticks() (or tmr2, selected by the user)
// - free running tmr2 for pwm / output compare / input capture
//
// - version history
// - v2.0, 5/13/2021: original port
// - v2.1, 5/26/2021: implemented SystemCoreClockUpdate() that updates SystemCoreClock during initialization
//                    implemented systicks() from TMR2 ISR - optional (in addition to core timer)
// - v2.2, 5/27/2021: implemented i2c/rtcc
// - v2.3, 6/19/2021: added support for output compare (dah!)
// - v2.4, 5/29/2021: output compare routines no longer advance compare registers
// - v2.5, 5/24/2022: added support for C32 compiler
// - v2.6, 6/04/2022: support IO port A..G
//
//
//hardware configuration
//
//               PIC32MX1/2xx
//              |=====================|
//    Vcc       |                     |
//     |        |                AVdd |>---+--[1k]-->Vcc
//     |        |                     |  [.1u]
//     +-[10K]-<| MCLR           AVss |>---+-------->GND
//              |                     |
//              |                     |
//     +------->| OSCI           Vcap |>--[.1u]-+->GND
//  [Xtal]      |                     |         |
//     +-------<| OSCO           Vss  |>--------+
//              |                     |
//     +------->| SOSCI          RPB0 |>---------->Uart2TX
// [32,768Hz]   |                     |
//     +-------<| SOSCO           RB7 |>---------->LED
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
//

#if defined(__XC__)							//if we are using xc32
#include <xc.h>								//we use xc32
#elif defined(__C32__)						//otherwise, use c32
#include <p32xxxx.h>						//we use c32
#include <plib.h>							//plib functions on interrupts
#else
#error "PIC32Duino.h: unsupported compiler!"
#endif
#include <sys/attribs.h>					//attributes for interrupts
#include <stdint.h>							//we use uint types
#include <string.h>							//we use strcpy()

//hardware configuration
//oscillator configuration by user
//#define USE_MAIN							//use self-defined main() in user code
//#define USE_SYSTICK							//comment out if you want to use coretick for timing
#define F_XTAL				20000000ul		//crystal frequency, user-specified
#define F_SOSC				32768			//SOSC = 32768Hz, user-specified
//end user specification

//uart1 pin configuration
#define U1TX2RP()			PPS_U1TX_TO_RPB3()			//map u1tx pin to an rp pin: A0, B3, B4, B15, B7, C7, C0, C5
#define U1RX2RP()			PPS_U1RX_TO_RPA2()			//map u1rx pin to an rp pin: A2, B6, A4, B13, B2, C6, C1, C3

//uart2 pin configuration
#define U2TX2RP()			PPS_U2TX_TO_RPB0()			//u2tx pin: A3, B14, B0, B10, B9, C9, C2, C4
#define U2RX2RP()			PPS_U2RX_TO_RPA1()			//u2rx pin: A1, B5, B1, B11, B8, A8, C8, A9

//pwm/oc pin configuration
//#define PWM12RP()			PPS_OC1_TO_RPB7()			//oc1 pin: A0, B3, B4, B15, B7, C7, C0, C5
#define PWM22RP()			PPS_OC2_TO_RPB8()			//oc2 pin: A1, B5, B1, B11, B8, A8, C8, A9
#define PWM32RP()			PPS_OC3_TO_RPB9()			//oc3 pin: A3, B14, B0, B10, B9, C9, C2, C4
#define PWM42RP()			PPS_OC4_TO_RPA2()			//oc4 pin: A2, B6, A4, B13, B2, C6, C1, C3
#define PWM52RP()			PPS_OC5_TO_RPA4()			//oc5 pin: A2, B6, A4, B13, B2, C6, C1, C3

//input capture pin configuration
#define IC12RP()			PPS_IC1_TO_RPB6()			//ic1 pin: A2, B6, A4, B13, B2, C6, C1, C3
#define IC22RP()			PPS_IC2_TO_RPA3()			//ic2 pin: A3, B14, B0, B10, B9, C9, C2, C4
#define IC32RP()			PPS_IC3_TO_RPB8()			//ic3 pin: A1, B5, B1, B11, B8, A8, C8, A9
#define IC42RP()			PPS_IC4_TO_RPA0()			//ic4 pin: A0, B3, B4, B15, B7, C7, C0, C5
#define IC52RP()			PPS_IC5_TO_RPA2()			//ic5 pin: A2, B6, A4, B13, B2, C6, C1, C3

//spi
#define SCK1RP()										//not remappable
#define SDO1RP()			PPS_SDO1_TO_RPB1()			//sdo1 pin: A1, B5, B1, B11, B8, A8, C8, A9, A2, B6, A4, B13, B2, C6, C1, C3
#define SDI1RP()			PPS_SDI1_TO_RPA1()			//SDI1 pin: A1, B5, B1, B11, B8, A8, C8, A9
#define SCK2RP()										//not remappable
#define SDO2RP()			PPS_SDO2_TO_RPB1()			//sdo1 pin: A1, B5, B1, B11, B8, A8, C8, A9, A2, B6, A4, B13, B2, C6, C1, C3
#define SDI2RP()			PPS_SDI2_TO_RPA2()			//SDI1 pin: A2, B6, A4, B13, B2, C6, C1, C3

//extint pin configuration
//#define INT02RP()			PPS_INT1_TO_RPA3()			//int0 pin: fixed to rp7
#define INT12RP()			PPS_INT1_TO_RPB9()			//int0 pin: A3, B14, B0, B10, B9, C9, C2, C4
#define INT22RP()			PPS_INT2_TO_RPA2()			//int0 pin: A2, B6, A4, B13, B2, C6, C1, C3
#define INT32RP()			PPS_INT3_TO_RPA1()			//int0 pin: A1, B5, B1, B11, B8, A8, C8, A9
#define INT42RP()			PPS_INT4_TO_RPA0()			//int0 pin: A0, B3, B4, B15, B7, C7, C0, C5
//end pin configuration

#define F_CPU				(SystemCoreClock)			//=SYSCLK: cpu runs at this speed
#define F_PHB				((F_CPU) >> (OSCCONbits.PBDIV))		//peripheral block runs at F_PB - default = F_CPU / 8
#define F_FRC				8000000ul					//FRC frequency = 8Mhz, fixed
#define F_LPRC				(31250ul)					//LPRC frequency=31.25Khz, fixed

#define PWM_PR				0xffff						//pwm period - do not change

//port manipulation macros for PIC.
//#define IO_SET(port, bits)              port |= (bits)			//set bits on port
//#define IO_CLR(port, bits)              port &=~(bits)			//clear bits on port
//#define IO_FLP(port, bits)              port ^= (bits)			//flip bits on port
//#define IO_GET(port, bits)              ((port) & (bits))		//return bits on port
//#define IO_OUT(ddr, bits)               ddr &=~(bits)			//set bits as output
//#define IO_IN(ddr, bits)                ddr |= (bits)			//set bits as input

//if gpio_typedef is used
#define GIO_SET(port, bits)              port->LAT |= (bits)			//set bits on port
#define GIO_CLR(port, bits)              port->LAT &=~(bits)			//clear bits on port
#define GIO_FLP(port, bits)              port->LAT ^= (bits)			//flip bits on port
#define GIO_GET(port, bits)              ((port->PORT) & (bits))		//return bits on port
#define GIO_OUT(port, bits)              port->TRIS &=~(bits)			//set bits as output
#define GIO_IN(port, bits) 	            port->TRIS |= (bits)			//set bits as input

//fast port operations
#define FIO_SET(port, bits)              port->LATSET = (bits)			//set bits on port
#define FIO_CLR(port, bits)              port->LATCLR = (bits)			//clear bits on port
#define FIO_FLP(port, bits)              port->LATINV = (bits)			//flip bits on port
#define FIO_GET(port, bits)              ((port->PORT) & (bits))		//return bits on port
#define FIO_OUT(port, bits)              port->TRISCLR = (bits)			//set bits as output
#define FIO_IN(port, bits)               port->TRISSET = (bits)			//set bits as input

#define NOP()				Nop()                           //asm("nop")					//nop()
#define NOP2()				{NOP(); NOP();}
#define NOP4()				{NOP2(); NOP2();}
#define NOP8()				{NOP4(); NOP4();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP16()				{NOP8(); NOP8();}
#define NOP24()				{NOP16(); NOP8();}
#define NOP32()				{NOP16(); NOP16();}
#define NOP40()				{NOP32(); NOP8();}
#define NOP64()				{NOP32(); NOP32();}

#define sleep()				asm("sleep")					//put the mcu into sleep

#ifndef ei
#if defined(__XC__)
#define ei()				__builtin_enable_interrupts();	//asm volatile ("ei");	do {INTEnableInterrupts();	INTEnableSystemMultiVectoredInt();} while (0)	//__builtin_enable_interrupts()
#else
#define ei()				do {INTEnableInterrupts();	INTEnableSystemMultiVectoredInt();} while (0)	//__builtin_enable_interrupts()
#endif //__XC__
#endif

#ifndef di
#if defined(__XC__)
#define di()				__builtin_enable_interrupts();	//asm volatile ("di")	INTDisableInterrupts()			//__builtin_disable_interrupts()	//
#else
#define di()				do {INTDisableInterrupts(); /*INTDisableSystemMultiVectoredInt();*/} while (0)			//__builtin_disable_interrupts()	//
#endif		//__XC__
#endif

//for int status - C32 lacks certain functions available in XC32 as built-in functions
#if defined(__C32__)
#define __builtin_get_isr_state()			INTDisableInterrupts()
#define __builtin_set_isr_state(intStatus)	INTRestoreInterrupts(intStatus)
#endif		//__C32__

//unlock sysLOCK
#define SYS_UNLOCK(){SYSKEY=0x0; SYSKEY=0xAA996655; SYSKEY=0x556699AA; }

//lock sysLOCK
#define SYS_LOCK()	{SYSKEY=0x0; }

//unlock IOLOCK
#define IO_UNLOCK()	{SYSKEY=0x0; SYSKEY=0xAA996655; SYSKEY=0x556699AA; CFGCONbits.IOLOCK=0;}

//lock IOLOCK
#define IO_LOCK()	{SYSKEY=0x0; SYSKEY=0xAA996655; SYSKEY=0x556699AA; CFGCONbits.IOLOCK=1;}

//pps macros
//more on macro
//macros for remappable pins
//PPS input pins

//group 1
#define PPS_INT4_TO_RPA0()		INT4R = 0
#define PPS_INT4_TO_RPB3()		INT4R = 1
#define PPS_INT4_TO_RPB4()		INT4R = 2
#define PPS_INT4_TO_RPB15()		INT4R = 3
#define PPS_INT4_TO_RPB7()		INT4R = 4
#define PPS_INT4_TO_RPC7()		INT4R = 5
#define PPS_INT4_TO_RPC0()		INT4R = 6
#define PPS_INT4_TO_RPC5()		INT4R = 7

#define PPS_T2CK_TO_RPA0()		T2CKR = 0
#define PPS_T2CK_TO_RPB3()		T2CKR = 1
#define PPS_T2CK_TO_RPB4()		T2CKR = 2
#define PPS_T2CK_TO_RPB15()		T2CKR = 3
#define PPS_T2CK_TO_RPB7()		T2CKR = 4
#define PPS_T2CK_TO_RPC7()		T2CKR = 5
#define PPS_T2CK_TO_RPC0()		T2CKR = 6
#define PPS_T2CK_TO_RPC5()		T2CKR = 7

#define PPS_IC4_TO_RPA0()		IC4R = 0
#define PPS_IC4_TO_RPB3()		IC4R = 1
#define PPS_IC4_TO_RPB4()		IC4R = 2
#define PPS_IC4_TO_RPB15()		IC4R = 3
#define PPS_IC4_TO_RPB7()		IC4R = 4
#define PPS_IC4_TO_RPC7()		IC4R = 5
#define PPS_IC4_TO_RPC0()		IC4R = 6
#define PPS_IC4_TO_RPC5()		IC4R = 7

#define PPS_SS1I_TO_RPA0()		SS1R = 0
#define PPS_SS1I_TO_RPB3()		SS1R = 1
#define PPS_SS1I_TO_RPB4()		SS1R = 2
#define PPS_SS1I_TO_RPB15()		SS1R = 3
#define PPS_SS1I_TO_RPB7()		SS1R = 4
#define PPS_SS1I_TO_RPC7()		SS1R = 5
#define PPS_SS1I_TO_RPC0()		SS1R = 6
#define PPS_SS1I_TO_RPC5()		SS1R = 7

#define PPS_REFCLKI_TO_RPA0()		REFCLKIR = 0
#define PPS_REFCLKI_TO_RPB3()		REFCLKIR = 1
#define PPS_REFCLKI_TO_RPB4()		REFCLKIR = 2
#define PPS_REFCLKI_TO_RPB15()		REFCLKIR = 3
#define PPS_REFCLKI_TO_RPB7()		REFCLKIR = 4
#define PPS_REFCLKI_TO_RPC7()		REFCLKIR = 5
#define PPS_REFCLKI_TO_RPC0()		REFCLKIR = 6
#define PPS_REFCLKI_TO_RPC5()		REFCLKIR = 7


//group 2
#define PPS_INT3_TO_RPA1()		INT3R = 0
#define PPS_INT3_TO_RPB5()		INT3R = 1
#define PPS_INT3_TO_RPB1()		INT3R = 2
#define PPS_INT3_TO_RPB11()		INT3R = 3
#define PPS_INT3_TO_RPB8()		INT3R = 4
#define PPS_INT3_TO_RPA8()		INT3R = 5
#define PPS_INT3_TO_RPC8()		INT3R = 6
#define PPS_INT3_TO_RPA9()		INT3R = 7


#define PPS_T3CK_TO_RPA1()		T3CKR = 0
#define PPS_T3CK_TO_RPB5()		T3CKR = 1
#define PPS_T3CK_TO_RPB1()		T3CKR = 2
#define PPS_T3CK_TO_RPB11()		T3CKR = 3
#define PPS_T3CK_TO_RPB8()		T3CKR = 4
#define PPS_T3CK_TO_RPA8()		T3CKR = 5
#define PPS_T3CK_TO_RPC8()		T3CKR = 6
#define PPS_T3CK_TO_RPA9()		T3CKR = 7

#define PPS_IC3_TO_RPA1()		IC3R = 0
#define PPS_IC3_TO_RPB5()		IC3R = 1
#define PPS_IC3_TO_RPB1()		IC3R = 2
#define PPS_IC3_TO_RPB11()		IC3R = 3
#define PPS_IC3_TO_RPB8()		IC3R = 4
#define PPS_IC3_TO_RPA8()		IC3R = 5
#define PPS_IC3_TO_RPC8()		IC3R = 6
#define PPS_IC3_TO_RPA9()		IC3R = 7

#define PPS_U1CTS_TO_RPA1()		U1CTSR = 0
#define PPS_U1CTS_TO_RPB5()		U1CTSR = 1
#define PPS_U1CTS_TO_RPB1()		U1CTSR = 2
#define PPS_U1CTS_TO_RPB11()		U1CTSR = 3
#define PPS_U1CTS_TO_RPB8()		U1CTSR = 4
#define PPS_U1CTS_TO_RPA8()		U1CTSR = 5
#define PPS_U1CTS_TO_RPC8()		U1CTSR = 6
#define PPS_U1CTS_TO_RPA9()		U1CTSR = 7

#define PPS_U2RX_TO_RPA1()		U2RXR = 0
#define PPS_U2RX_TO_RPB5()		U2RXR = 1
#define PPS_U2RX_TO_RPB1()		U2RXR = 2
#define PPS_U2RX_TO_RPB11()		U2RXR = 3
#define PPS_U2RX_TO_RPB8()		U2RXR = 4
#define PPS_U2RX_TO_RPA8()		U2RXR = 5
#define PPS_U2RX_TO_RPC8()		U2RXR = 6
#define PPS_U2RX_TO_RPA9()		U2RXR = 7

#define PPS_SDI1_TO_RPA1()		SDI1R = 0
#define PPS_SDI1_TO_RPB5()		SDI1R = 1
#define PPS_SDI1_TO_RPB1()		SDI1R = 2
#define PPS_SDI1_TO_RPB11()		SDI1R = 3
#define PPS_SDI1_TO_RPB8()		SDI1R = 4
#define PPS_SDI1_TO_RPA8()		SDI1R = 5
#define PPS_SDI1_TO_RPC8()		SDI1R = 6
#define PPS_SDI1_TO_RPA9()		SDI1R = 7


//group 3
#define PPS_INT2_TO_RPA2()		INT2R = 0
#define PPS_INT2_TO_RPB6()		INT2R = 1
#define PPS_INT2_TO_RPA4()		INT2R = 2
#define PPS_INT2_TO_RPB13()		INT2R = 3
#define PPS_INT2_TO_RPB2()		INT2R = 4
#define PPS_INT2_TO_RPC6()		INT2R = 5
#define PPS_INT2_TO_RPC1()		INT2R = 6
#define PPS_INT2_TO_RPA3()		INT2R = 7


#define PPS_T4CK_TO_RPA2()		T4CKR = 0
#define PPS_T4CK_TO_RPB6()		T4CKR = 1
#define PPS_T4CK_TO_RPA4()		T4CKR = 2
#define PPS_T4CK_TO_RPB13()		T4CKR = 3
#define PPS_T4CK_TO_RPB2()		T4CKR = 4
#define PPS_T4CK_TO_RPC6()		T4CKR = 5
#define PPS_T4CK_TO_RPC1()		T4CKR = 6
#define PPS_T4CK_TO_RPA3()		T4CKR = 7

#define PPS_IC1_TO_RPA2()		IC1R = 0
#define PPS_IC1_TO_RPB6()		IC1R = 1
#define PPS_IC1_TO_RPA4()		IC1R = 2
#define PPS_IC1_TO_RPB13()		IC1R = 3
#define PPS_IC1_TO_RPB2()		IC1R = 4
#define PPS_IC1_TO_RPC6()		IC1R = 5
#define PPS_IC1_TO_RPC1()		IC1R = 6
#define PPS_IC1_TO_RPA3()		IC1R = 7

#define PPS_IC5_TO_RPA2()		IC5R = 0
#define PPS_IC5_TO_RPB6()		IC5R = 1
#define PPS_IC5_TO_RPA4()		IC5R = 2
#define PPS_IC5_TO_RPB13()		IC5R = 3
#define PPS_IC5_TO_RPB2()		IC5R = 4
#define PPS_IC5_TO_RPC6()		IC5R = 5
#define PPS_IC5_TO_RPC1()		IC5R = 6
#define PPS_IC5_TO_RPA3()		IC5R = 7

#define PPS_U1RX_TO_RPA2()		U1RXR = 0
#define PPS_U1RX_TO_RPB6()		U1RXR = 1
#define PPS_U1RX_TO_RPA4()		U1RXR = 2
#define PPS_U1RX_TO_RPB13()		U1RXR = 3
#define PPS_U1RX_TO_RPB2()		U1RXR = 4
#define PPS_U1RX_TO_RPC6()		U1RXR = 5
#define PPS_U1RX_TO_RPC1()		U1RXR = 6
#define PPS_U1RX_TO_RPA3()		U1RXR = 7

#define PPS_U2CTS_TO_RPA2()		U2CTSR = 0
#define PPS_U2CTS_TO_RPB6()		U2CTSR = 1
#define PPS_U2CTS_TO_RPA4()		U2CTSR = 2
#define PPS_U2CTS_TO_RPB13()	U2CTSR = 3
#define PPS_U2CTS_TO_RPB2()		U2CTSR = 4
#define PPS_U2CTS_TO_RPC6()		U2CTSR = 5
#define PPS_U2CTS_TO_RPC1()		U2CTSR = 6
#define PPS_U2CTS_TO_RPA3()		U2CTSR = 7

#define PPS_SDI2_TO_RPA2()		SDI2R = 0
#define PPS_SDI2_TO_RPB6()		SDI2R = 1
#define PPS_SDI2_TO_RPA4()		SDI2R = 2
#define PPS_SDI2_TO_RPB13()		SDI2R = 3
#define PPS_SDI2_TO_RPB2()		SDI2R = 4
#define PPS_SDI2_TO_RPC6()		SDI2R = 5
#define PPS_SDI2_TO_RPC1()		SDI2R = 6
#define PPS_SDI2_TO_RPA3()		SDI2R = 7

#define PPS_OCFB_TO_RPA2()		OCFBR = 0
#define PPS_OCFB_TO_RPB6()		OCFBR = 1
#define PPS_OCFB_TO_RPA4()		OCFBR = 2
#define PPS_OCFB_TO_RPB13()		OCFBR = 3
#define PPS_OCFB_TO_RPB2()		OCFBR = 4
#define PPS_OCFB_TO_RPC6()		OCFBR = 5
#define PPS_OCFB_TO_RPC1()		OCFBR = 6
#define PPS_OCFB_TO_RPA3()		OCFBR = 7

//group 4
#define PPS_INT1_TO_RPA3()		INT1R = 0
#define PPS_INT1_TO_RPB14()		INT1R = 1
#define PPS_INT1_TO_RPB0()		INT1R = 2
#define PPS_INT1_TO_RPB10()		INT1R = 3
#define PPS_INT1_TO_RPB9()		INT1R = 4
#define PPS_INT1_TO_RPC9()		INT1R = 5
#define PPS_INT1_TO_RPC2()		INT1R = 6
#define PPS_INT1_TO_RPC4()		INT1R = 7

#define PPS_T5CK_TO_RPA3()		T5CKR = 0
#define PPS_T5CK_TO_RPB14()		T5CKR = 1
#define PPS_T5CK_TO_RPB0()		T5CKR = 2
#define PPS_T5CK_TO_RPB10()		T5CKR = 3
#define PPS_T5CK_TO_RPB9()		T5CKR = 4
#define PPS_T5CK_TO_RPC9()		T5CKR = 5
#define PPS_T5CK_TO_RPC2()		T5CKR = 6
#define PPS_T5CK_TO_RPC4()		T5CKR = 7

#define PPS_IC2_TO_RPA3()		IC2R = 0
#define PPS_IC2_TO_RPB14()		IC2R = 1
#define PPS_IC2_TO_RPB0()		IC2R = 2
#define PPS_IC2_TO_RPB10()		IC2R = 3
#define PPS_IC2_TO_RPB9()		IC2R = 4
#define PPS_IC2_TO_RPC9()		IC2R = 5
#define PPS_IC2_TO_RPC2()		IC2R = 6
#define PPS_IC2_TO_RPC4()		IC2R = 7

#define PPS_SS2I_TO_RPA3()		SS2R = 0
#define PPS_SS2I_TO_RPB14()		SS2R = 1
#define PPS_SS2I_TO_RPB0()		SS2R = 2
#define PPS_SS2I_TO_RPB10()		SS2R = 3
#define PPS_SS2I_TO_RPB9()		SS2R = 4
#define PPS_SS2I_TO_RPC9()		SS2R = 5
#define PPS_SS2I_TO_RPC2()		SS2R = 6
#define PPS_SS2I_TO_RPC4()		SS2R = 7

#define PPS_OCFA_TO_RPA3()		OCFAR = 0
#define PPS_OCFA_TO_RPB14()		OCFAR = 1
#define PPS_OCFA_TO_RPB0()		OCFAR = 2
#define PPS_OCFA_TO_RPB10()		OCFAR = 3
#define PPS_OCFA_TO_RPB9()		OCFAR = 4
#define PPS_OCFA_TO_RPC9()		OCFAR = 5
#define PPS_OCFA_TO_RPC2()		OCFAR = 6
#define PPS_OCFA_TO_RPC4()		OCFAR = 7

//PPS output pins
//group 1
#define PPS_NC_TO_RPA0()		RPA0R = 0
#define PPS_U1TX_TO_RPA0()		RPA0R = 1
#define PPS_U2RTS_TO_RPA0()		RPA0R = 2
#define PPS_SS1_TO_RPA0()		RPA0R = 3
#define PPS_OC1_TO_RPA0()		RPA0R = 0b0101
#define PPS_C2OUT_TO_RPA0()		RPA0R = 0b0111

#define PPS_NC_TO_RPB3()		RPB3R = 0
#define PPS_U1TX_TO_RPB3()		RPB3R = 1
#define PPS_U2RTS_TO_RPB3()		RPB3R = 2
#define PPS_SS1_TO_RPB3()		RPB3R = 3
#define PPS_OC1_TO_RPB3()		RPB3R = 0b0101
#define PPS_C2OUT_TO_RPB3()		RPB3R = 0b0111

#define PPS_NC_TO_RPB4()		RPB4R = 0
#define PPS_U1TX_TO_RPB4()		RPB4R = 1
#define PPS_U2RTS_TO_RPB4()		RPB4R = 2
#define PPS_SS1_TO_RPB4()		RPB4R = 3
#define PPS_OC1_TO_RPB4()		RPB4R = 0b0101
#define PPS_C2OUT_TO_RPB4()		RPB4R = 0b0111

#define PPS_NC_TO_RPB15()		RPB15R = 0
#define PPS_U1TX_TO_RPB15()		RPB15R = 1
#define PPS_U2RTS_TO_RPB15()		RPB15R = 2
#define PPS_SS1_TO_RPB15()		RPB15R = 3
#define PPS_OC1_TO_RPB15()		RPB15R = 0b0101
#define PPS_C2OUT_TO_RPB15()		RPB15R = 0b0111

#define PPS_NC_TO_RPB7()		RPB7R = 0
#define PPS_U1TX_TO_RPB7()		RPB7R = 1
#define PPS_U2RTS_TO_RPB7()		RPB7R = 2
#define PPS_SS1_TO_RPB7()		RPB7R = 3
#define PPS_OC1_TO_RPB7()		RPB7R = 0b0101
#define PPS_C2OUT_TO_RPB7()		RPB7R = 0b0111

#define PPS_NC_TO_RPC7()		RPC7R = 0
#define PPS_U1TX_TO_RPC7()		RPC7R = 1
#define PPS_U2RTS_TO_RPC7()		RPC7R = 2
#define PPS_SS1_TO_RPC7()		RPC7R = 3
#define PPS_OC1_TO_RPC7()		RPC7R = 0b0101
#define PPS_C2OUT_TO_RPC7()		RPC7R = 0b0111

#define PPS_NC_TO_RPC0()		RPC0R = 0
#define PPS_U1TX_TO_RPC0()		RPC0R = 1
#define PPS_U2RTS_TO_RPC0()		RPC0R = 2
#define PPS_SS1_TO_RPC0()		RPC0R = 3
#define PPS_OC1_TO_RPC0()		RPC0R = 0b0101
#define PPS_C2OUT_TO_RPC0()		RPC0R = 0b0111

#define PPS_NC_TO_RPC5()		RPC5R = 0
#define PPS_U1TX_TO_RPC5()		RPC5R = 1
#define PPS_U2RTS_TO_RPC5()		RPC5R = 2
#define PPS_SS1_TO_RPC5()		RPC5R = 3
#define PPS_OC1_TO_RPC5()		RPC5R = 0b0101
#define PPS_C2OUT_TO_RPC5()		RPC5R = 0b0111


//group 2
#define PPS_NC_TO_RPA1()		RPA1R = 0
#define PPS_SDO1_TO_RPA1()		RPA1R = 0b0011
#define PPS_SDO2_TO_RPA1()		RPA1R = 0b0100
#define PPS_OC2_TO_RPA1()		RPA1R = 0b0101
#define PPS_C3OUT_TO_RPA1()		RPA1R = 0b0111

#define PPS_NC_TO_RPB5()		RPB5R = 0
#define PPS_SDO1_TO_RPB5()		RPB5R = 0b0011
#define PPS_SDO2_TO_RPB5()		RPB5R = 0b0100
#define PPS_OC2_TO_RPB5()		RPB5R = 0b0101
#define PPS_C3OUT_TO_RPB5()		RPB5R = 0b0111

#define PPS_NC_TO_RPB1()		RPB1R = 0
#define PPS_SDO1_TO_RPB1()		RPB1R = 0b0011
#define PPS_SDO2_TO_RPB1()		RPB1R = 0b0100
#define PPS_OC2_TO_RPB1()		RPB1R = 0b0101
#define PPS_C3OUT_TO_RPB1()		RPB1R = 0b0111

#define PPS_NC_TO_RPB11()		RPB11R = 0
#define PPS_SDO1_TO_RPB11()		RPB11R = 0b0011
#define PPS_SDO2_TO_RPB11()		RPB11R = 0b0100
#define PPS_OC2_TO_RPB11()		RPB11R = 0b0101
#define PPS_C3OUT_TO_RPB11()		RPB11R = 0b0111

#define PPS_NC_TO_RPB8()		RPB8R = 0
#define PPS_SDO1_TO_RPB8()		RPB8R = 0b0011
#define PPS_SDO2_TO_RPB8()		RPB8R = 0b0100
#define PPS_OC2_TO_RPB8()		RPB8R = 0b0101
#define PPS_C3OUT_TO_RPB8()		RPB8R = 0b0111

#define PPS_NC_TO_RPA8()		RPA8R = 0
#define PPS_SDO1_TO_RPA8()		RPA8R = 0b0011
#define PPS_SDO2_TO_RPA8()		RPA8R = 0b0100
#define PPS_OC2_TO_RPA8()		RPA8R = 0b0101
#define PPS_C3OUT_TO_RPA8()		RPA8R = 0b0111

#define PPS_NC_TO_RPC8()		RPC8R = 0
#define PPS_SDO1_TO_RPC8()		RPC8R = 0b0011
#define PPS_SDO2_TO_RPC8()		RPC8R = 0b0100
#define PPS_OC2_TO_RPC8()		RPC8R = 0b0101
#define PPS_C3OUT_TO_RPC8()		RPA1R = 0b0111

#define PPS_NC_TO_RPA9()		RPA9R = 0
#define PPS_SDO1_TO_RPA9()		RPA9R = 0b0011
#define PPS_SDO2_TO_RPA9()		RPA9R = 0b0100
#define PPS_OC2_TO_RPA9()		RPA9R = 0b0101
#define PPS_C3OUT_TO_RPA9()		RPA9R = 0b0111


//group 3
#define PPS_NC_TO_RPA2()		RPA2R = 0
#define PPS_SDO1_TO_RPA2()		RPA2R = 0b0011
#define PPS_SDO2_TO_RPA2()		RPA2R = 0b0100
#define PPS_OC4_TO_RPA2()		RPA2R = 0b0101
#define PPS_OC5_TO_RPA2()		RPA2R = 0b0110
#define PPS_REFCLKO_TO_RPA2()		RPA2R = 0b0111

#define PPS_NC_TO_RPB6()		RPB6R = 0
#define PPS_SDO1_TO_RPB6()		RPB6R = 0b0011
#define PPS_SDO2_TO_RPB6()		RPB6R = 0b0100
#define PPS_OC4_TO_RPB6()		RPB6R = 0b0101
#define PPS_OC5_TO_RPB6()		RPB6R = 0b0110
#define PPS_REFCLKO_TO_RPB6()		RPB6R = 0b0111

#define PPS_NC_TO_RPA4()		RPA4R = 0
#define PPS_SDO1_TO_RPA4()		RPA4R = 0b0011
#define PPS_SDO2_TO_RPA4()		RPA4R = 0b0100
#define PPS_OC4_TO_RPA4()		RPA4R = 0b0101
#define PPS_OC5_TO_RPA4()		RPA4R = 0b0110
#define PPS_REFCLKO_TO_RPA4()		RPA4R = 0b0111

#define PPS_NC_TO_RPB13()		RPB13R = 0
#define PPS_SDO1_TO_RPB13()		RPB13R = 0b0011
#define PPS_SDO2_TO_RPB13()		RPB13R = 0b0100
#define PPS_OC4_TO_RPB13()		RPB13R = 0b0101
#define PPS_OC5_TO_RPB13()		RPB13R = 0b0110
#define PPS_REFCLKO_TO_RPB13()	RPB13R = 0b0111

#define PPS_NC_TO_RPB2()		RPB2R = 0
#define PPS_SDO1_TO_RPB2()		RPB2R = 0b0011
#define PPS_SDO2_TO_RPB2()		RPB2R = 0b0100
#define PPS_OC4_TO_RPB2()		RPB2R = 0b0101
#define PPS_OC5_TO_RPB2()		RPB2R = 0b0110
#define PPS_REFCLKO_TO_RPB2()		RPB2R = 0b0111

#define PPS_NC_TO_RPC6()		RPC6R = 0
#define PPS_SDO1_TO_RPC6()		RPC6R = 0b0011
#define PPS_SDO2_TO_RPC6()		RPC6R = 0b0100
#define PPS_OC4_TO_RPC6()		RPC6R = 0b0101
#define PPS_OC5_TO_RPC6()		RPC6R = 0b0110
#define PPS_REFCLKO_TO_RPC6()		RPC6R = 0b0111

#define PPS_NC_TO_RPC1()		RPC1R = 0
#define PPS_SDO1_TO_RPC1()		RPC1R = 0b0011
#define PPS_SDO2_TO_RPC1()		RPC1R = 0b0100
#define PPS_OC4_TO_RPC1()		RPC1R = 0b0101
#define PPS_OC5_TO_RPC1()		RPC1R = 0b0110
#define PPS_REFCLKO_TO_RPC1()		RPC1R = 0b0111

#define PPS_NC_TO_RPC3()		RPC3R = 0
#define PPS_SDO1_TO_RPC3()		RPC3R = 0b0011
#define PPS_SDO2_TO_RPC3()		RPC3R = 0b0100
#define PPS_OC4_TO_RPC3()		RPC3R = 0b0101
#define PPS_OC5_TO_RPC3()		RPC3R = 0b0110
#define PPS_REFCLKO_TO_RPC3()		RPC3R = 0b0111

//group 4
#define PPS_NC_TO_RPA3()		RPA3R = 0
#define PPS_U1RTS_TO_RPA3()		RPA3R = 0b0001
#define PPS_U2TX_TO_RPA3()		RPA3R = 0b0010
#define PPS_SS2_TO_RPA3()		RPA3R = 0b0100
#define PPS_OC3_TO_RPA3()		RPA3R = 0b0101
#define PPS_C1OUT_TO_RPA3()		RPA3R = 0b0111

#define PPS_NC_TO_RPB14()		RPB14R = 0
#define PPS_U1RTS_TO_RPB14()	RPB14R = 0b0001
#define PPS_U2TX_TO_RPB14()		RPB14R = 0b0010
#define PPS_SS2_TO_RPB14()		RPB14R = 0b0100
#define PPS_OC3_TO_RPB14()		RPB14R = 0b0101
#define PPS_C1OUT_TO_RPB14()	RPB14R = 0b0111

#define PPS_NC_TO_RPB0()		RPB0R = 0
#define PPS_U1RTS_TO_RPB0()		RPB0R = 0b0001
#define PPS_U2TX_TO_RPB0()		RPB0R = 0b0010
#define PPS_SS2_TO_RPB0()		RPB0R = 0b0100
#define PPS_OC3_TO_RPB0()		RPB0R = 0b0101
#define PPS_C1OUT_TO_RPB0()		RPB0R = 0b0111

#define PPS_NC_TO_RPB10()		RPB10R = 0
#define PPS_U1RTS_TO_RPB10()	RPB10R = 0b0001
#define PPS_U2TX_TO_RPB10()		RPB10R = 0b0010
#define PPS_SS2_TO_RPB10()		RPB10R = 0b0100
#define PPS_OC3_TO_RPB10()		RPB10R = 0b0101
#define PPS_C1OUT_TO_RPB10()	RPB10R = 0b0111

#define PPS_NC_TO_RPB9()		RPB9R = 0
#define PPS_U1RTS_TO_RPB9()		RPB9R = 0b0001
#define PPS_U2TX_TO_RPB9()		RPB9R = 0b0010
#define PPS_SS2_TO_RPB9()		RPB9R = 0b0100
#define PPS_OC3_TO_RPB9()		RPB9R = 0b0101
#define PPS_C1OUT_TO_RPB9()		RPB9R = 0b0111

#define PPS_NC_TO_RPC9()		RPC9R = 0
#define PPS_U1RTS_TO_RPC9()		RPC9R = 0b0001
#define PPS_U2TX_TO_RPC9()		RPC9R = 0b0010
#define PPS_SS2_TO_RPC9()		RPC9R = 0b0100
#define PPS_OC3_TO_RPC9()		RPC9R = 0b0101
#define PPS_C1OUT_TO_RPC9()		RPC9R = 0b0111

#define PPS_NC_TO_RPC2()		RPC2R = 0
#define PPS_U1RTS_TO_RPC2()		RPC2R = 0b0001
#define PPS_U2TX_TO_RPC2()		RPC2R = 0b0010
#define PPS_SS2_TO_RPC2()		RPC2R = 0b0100
#define PPS_OC3_TO_RPC2()		RPC2R = 0b0101
#define PPS_C1OUT_TO_RPC2()		RPC2R = 0b0111

#define PPS_NC_TO_RPC4()		RPC4R = 0
#define PPS_U1RTS_TO_RPC4()		RPC4R = 0b0001
#define PPS_U2TX_TO_RPC4()		RPC4R = 0b0010
#define PPS_SS2_TO_RPC4()		RPC4R = 0b0100
#define PPS_OC3_TO_RPC4()		RPC4R = 0b0101
#define PPS_C1OUT_TO_RPC4()		RPC4R = 0b0111

//simple multiples
#define x1(val)				(val)								//multiply val by 1
#define x2(val)				(((val) << 1))						//multiply val by 2
#define x3(val)				(x2(val) + (val))					//multiply val by 3
#define x4(val)				(((val) << 2))						//multiply val by 4
#define x5(val)				(x4(val) + (val))					//multiply val by 5
#define x6(val)				(x4(val) + x2(val))					//multiply val by 6
#define x7(val)				(x6(val) + (val))					//multiply val by 7
#define x8(val)				((val) << 3)						//multiply val by 8
#define x9(val)				(x8(val) + (val))					//multiply val by 9

//multiples of 10s
#define x10(val)			(x8(val) + x2(val))					//multiply val by 10
#define x100(val)			(x10(x10(val)))						//multiply val by 100
#define x1000(val)			(x100(x10(val)))					//multiply val by 1000
#define x1k(val)			x1000(val)							//multiply val by 1000
#define x10k(val)			(x100(x100(val)))					//multiply val by 10000

#define x20(val)			(x2(x10(val)))
#define x30(val)			(x3(x10(val)))
#define x40(val)			(x4(x10(val)))
#define x50(val)			(x5(x10(val)))
#define x60(val)			(x6(x10(val)))
#define x70(val)			(x7(x10(val)))
#define x80(val)			(x8(x10(val)))
#define x90(val)			(x9(x10(val)))

//multiples of 100s
#define x200(val)			(x2(x100(val)))
#define x300(val)			(x3(x100(val)))
#define x400(val)			(x4(x100(val)))
#define x500(val)			(x5(x100(val)))
#define x600(val)			(x6(x100(val)))
#define x700(val)			(x7(x100(val)))
#define x800(val)			(x8(x100(val)))
#define x900(val)			(x9(x100(val)))

//custom definitions
#define x34(val)			(x30(val) + x4(val))				//multiply val by 34
#define x97(val)			(x90(val) + x7(val))				//multiply val by 97x

//gpio
//port structure
typedef struct {
	volatile uint32_t ANSEL;			//analog select
	volatile uint32_t ANSELCLR;        	//set to clear
	volatile uint32_t ANSELSET;        	//set to set
	volatile uint32_t ANSELINV;        	//set to flip

	volatile uint32_t TRIS;             //data direction register -> 0ffset 0x0000, little endian
	//volatile uint32_t RESERVED0[3];   //fill the space
	volatile uint32_t TRISCLR;          //set to clear
	volatile uint32_t TRISSET;          //set to set
	volatile uint32_t TRISINV;          //set to flip

	volatile uint32_t PORT;             //input data register
	//volatile uint32_t RESERVED1[3];     //fill the space
	volatile uint32_t PORTCLR;          //set to clear
	volatile uint32_t PORTSET;          //set to set
	volatile uint32_t PORTINV;          //set to flip

	volatile uint32_t LAT;              //output data register
	//volatile uint32_t RESERVED2[3];   //fill the space
	volatile uint32_t LATCLR;          	//set to clear
	volatile uint32_t LATSET;          	//set to set
	volatile uint32_t LATINV;          	//set to flip

	volatile uint32_t ODC;              //open drain configuration register. set to activate open drain
	//volatile uint32_t RESERVED3[3];     //fill the space
	volatile uint32_t ODCCLR;          //set to clear
	volatile uint32_t ODCSET;          //set to set
	volatile uint32_t ODCINV;          //set to flip

	volatile uint32_t CNPU;				//change notification weak pull-up
	//volatile uint32_t RESERVED4[3];   //fill the space
	volatile uint32_t CNPUCLR;          //set to clear
	volatile uint32_t CNPUSET;          //set to set
	volatile uint32_t CNPUINV;          //set to flip

	volatile uint32_t CNPD;				//change notification weak pull-down
	//volatile uint32_t RESERVED5[3];   //fill the space
	volatile uint32_t CNPDCLR;          //set to clear
	volatile uint32_t CNPDSET;          //set to set
	volatile uint32_t CNPDINV;          //set to flip

	volatile uint32_t CNCON;			//change notification control register (1<<15 to enable, 0<<15 to disable)
	volatile uint32_t RESERVED6[3];     //fill the space

	volatile uint32_t CNEN;				//change notification enable register (1->enable, 0->disable)
	//volatile uint32_t RESERVED7[3];   //fill the space
	volatile uint32_t CNENCLR;          //set to clear
	volatile uint32_t CNENSET;          //set to set
	volatile uint32_t CNENINV;          //set to flip

	volatile uint32_t CNSTAT;			//change notification status register (1->changed, 0->not changed)
	volatile uint32_t RESERVED8[3];     //fill the space

} GPIO_TypeDef;                         //port definition registers

#if defined(_PORTA)
#define GPIOA                           ((GPIO_TypeDef *) &ANSELA)
#endif

#if defined(_PORTB)
#define GPIOB                           ((GPIO_TypeDef *) &ANSELB)
#endif

#if defined(_PORTC)
#define GPIOC                           ((GPIO_TypeDef *) &ANSELC)
#endif

#if defined(_PORTD)
#define GPIOD                           ((GPIO_TypeDef *) &ANSELD)
#endif

#if defined(_PORTE)
#define GPIOE                           ((GPIO_TypeDef *) &ANSELE)
#endif

#if defined(_PORTF)
#define GPIOF                           ((GPIO_TypeDef *) &ANSELF)
#endif

#if defined(_PORTG)
#define GPIOG                           ((GPIO_TypeDef *) &ANSELG)
#endif
//end GPIO

//DevID
typedef struct {
	uint32_t DEVID:28;					//device id
	uint8_t  VER:4;						//version
} DevID_TypeDef;

#define PIC32ID							((DevID_TypeDef *) &DEVID)
//see https://github.com/sergev/pic32prog/blob/master/target.c for a list of PIC32 device IDs
//end devid

//pre-requisite: FCKSM = CSECMD.
//NOSC bits 10..8
#define CLKNOSC_FRCDIV		(0b111 << 8)	//clock source = frc/
#define CLKNOSC_FRC16		(0b110 << 8)	//clock source = frc/16
#define CLKNOSC_LPRC		(0b101 << 8)	//clock source = lprc
#define CLKNOSC_SOSC		(0b100 << 8)	//clock source = sosc
#define CLKNOSC_POSCPLL		(0b011 << 8)	//clock source = hs, xt, ec + PLL
#define CLKNOSC_POSC		(0b010 << 8)	//clock source = hs, xt, ec
#define CLKNOSC_FRCPLL		(0b001 << 8)	//clock source = frc + PLL
#define CLKNOSC_FRC			(0b000 << 8)	//clock source = frc

//COSC bits 14..12
#define CLKCOSC_FRCDIV		(0b111 << 12)	//clock source = frc/
#define CLKCOSC_FRC16		(0b110 << 12)	//clock source = frc/16
#define CLKCOSC_LPRC		(0b101 << 12)	//clock source = lprc
#define CLKCOSC_SOSC		(0b100 << 12)	//clock source = sosc
#define CLKCOSC_POSCPLL		(0b011 << 12)	//clock source = hs, xt, ec + PLL
#define CLKCOSC_POSC		(0b010 << 12)	//clock source = hs, xt, ec
#define CLKCOSC_FRCPLL		(0b001 << 12)	//clock source = frc + PLL
#define CLKCOSC_FRC			(0b000 << 12)	//clock source = frc

//CLK FRCDIV bit 26..24
#define CLKFRCDIV_256		(0b111 << 24)	//frc divider = 256
#define CLKFRCDIV_64		(0b110 << 24)	//frc divider = 64
#define CLKFRCDIV_32		(0b101 << 24)	//frc divider = 32
#define CLKFRCDIV_16		(0b100 << 24)	//frc divider = 16
#define CLKFRCDIV_8			(0b011 << 24)	//frc divider = 8
#define CLKFRCDIV_4			(0b010 << 24)	//frc divider = 4
#define CLKFRCDIV_2			(0b001 << 24)	//frc divider = 2
#define CLKFRCDIV_1			(0b000 << 24)	//frc divider = 1

//CLK PLLDIV bit 29..27
#define CLKPLLDIV_256		(0b111 << 27)	//frc divider = 256
#define CLKPLLDIV_64		(0b110 << 27)	//frc divider = 64
#define CLKPLLDIV_32		(0b101 << 27)	//frc divider = 32
#define CLKPLLDIV_16		(0b100 << 27)	//frc divider = 16
#define CLKPLLDIV_8			(0b011 << 27)	//frc divider = 8
#define CLKPLLDIV_4			(0b010 << 27)	//frc divider = 4
#define CLKPLLDIV_2			(0b001 << 27)	//frc divider = 2
#define CLKPLLDIV_1			(0b000 << 27)	//frc divider = 1

//CLK PLLMULT bit 18..16
#define CLKPLLMULT_24		(0b111 << 16)	//frc divider = 256
#define CLKPLLMULT_21		(0b110 << 16)	//frc divider = 64
#define CLKPLLMULT_20		(0b101 << 16)	//frc divider = 32
#define CLKPLLMULT_19		(0b100 << 16)	//frc divider = 16
#define CLKPLLMULT_18		(0b011 << 16)	//frc divider = 8
#define CLKPLLMULT_17		(0b010 << 16)	//frc divider = 4
#define CLKPLLMULT_16		(0b001 << 16)	//frc divider = 2
#define CLKPLLMULT_15		(0b000 << 16)	//frc divider = 1

//global defines
extern uint32_t SystemCoreClock;			//sysclk = system core clock, updated by SystemCoreClockUpdate() after clock reconfiguration

//read sysclock back
//needs to be executed during mcu initialization or after oscillator reconfiguration
//returns SystemCoreClock
//Need to set fuse settings to ensure correct PLL operations
uint32_t SystemCoreClockUpdate(void);

//switch sysclock back
//return SystemCoreClock frequency
//bit 10-8 NOSC<2:0>: New Oscillator Selection bits
//111 = Internal Fast RC Oscillator (FRC) divided by OSCCON<FRCDIV> bits
//110 = Internal Fast RC Oscillator (FRC) divided by 16
//101 = Internal Low-Power RC (LPRC) Oscillator
//100 = Secondary Oscillator (SOSC)
//011 = Primary Oscillator with PLL module (XTPLL, HSPLL or ECPLL)
//010 = Primary Oscillator (XT, HS or EC)
//001 = Internal Fast Internal RC Oscillator with PLL module via Postscaler (FRCPLL)
//000 = Internal Fast Internal RC Oscillator (FRC)
//On Reset, these bits are set to the value of the FNOSC Configuration bits (DEVCFG1<2:0>).
uint32_t SystemCoreClockSwitch(uint8_t nosc);
#define SystemCoreClockFRC()		SystemCoreClockSwitch(0b000)
#define SystemCoreClockFRCPLL()	SystemCoreClockSwitch(0b001)
#define SystemCoreClockPOSC()		SystemCoreClockSwitch(0b010)
#define SystemCoreClockPOSCPLL()	SystemCoreClockSwitch(0b011)
#define SystemCoreClockSOSC()		SystemCoreClockSwitch(0b100)
#define SystemCoreClockLPRC()		SystemCoreClockSwitch(0b101)
#define SystemCoreClockFRC16()		SystemCoreClockSwitch(0b110)
#define SystemCoreClockFRCDIV()	SystemCoreClockSwitch(0b111)

//gpio definitions

//pin enum - matches GPIO_PinDef[]
typedef enum {
	PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
	PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
#if defined(_PORTC)
	PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
#endif		//_PORTC
	PMAX
} PIN_TypeDef;

//map pin number to GPIOx
typedef struct {
	GPIO_TypeDef *gpio;					//gpio for a pin
	uint16_t mask;						//pin mask - 16-bit port
} PIN2GPIO;

#define INPUT				0
#define OUTPUT				1			//(!INPUT)
#define INPUT_PULLUP		2

#define LOW					0
#define HIGH				(!LOW)

#define PI 					3.1415926535897932384626433832795
#define HALF_PI 			(PI / 2)							//1.5707963267948966192313216916398
#define TWO_PI 				(PI + PI)							//6.283185307179586476925286766559
#define DEG_TO_RAD 			(TWO_PI / 360)						//0.017453292519943295769236907684886
#define RAD_TO_DEG 			(360 / TWO_PI)						//57.295779513082320876798154814105
#define EULER 				2.718281828459045235360287471352	//Euler's number

#define SERIAL  			0x0
#define DISPLAY 			0x1

#define LSBFIRST 			0
#define MSBFIRST 			1									//(!LSBFIRST)							//1

#define CHANGE 				1
#define FALLING 			2
#define RISING 				3

#ifndef min
#define min(a,b) 			((a)<(b)?(a):(b))
#endif
#ifndef max
#define max(a,b) 			((a)>(b)?(a):(b))
#endif
#define abs(x) 				((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     		((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) 		((deg)*DEG_TO_RAD)
#define degrees(rad) 		((rad)*RAD_TO_DEG)
#define sq(x) 				((x)*(x))

#define interrupts() 		ei()
#define noInterrupts() 		di()

#define clockCyclesPerMillisecond() 	( F_CPU / 1000L )
#define clockCyclesPerMicrosecond() 	( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) 	( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) 	( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) 			((uint8_t) ((w) & 0xff))
#define highByte(w) 		((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) 	((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
#define bit(n)				(1ul<<(n))

#define false				0
#define true				(!false)

//characters
#define isAlphaNumeric(c)	isalnum(c)
#define isAlpha(c)			isalpha(c)
#define isAscii(c)			isascii(c)
#define isWhitespace(c)		isblank(c)
#define isControl(c)		iscntrl(c)
#define isDigit(c)			isdigit(c)
#define isGraph(c)			isgraph(c)
#define isLowerCase(c)		islower(c)
#define isPrintable(c)		isprint(c)
#define isPunct(c)			ispunct(c)
#define isSpace(c)			isspace(c)
#define isUpperCase(c)		isupper(c)
#define isHexadecimalDigit(c)	isxdigit(c)

//external setup/loop - defined by user
extern void setup(void);
extern void loop(void);

//random number
#define randomSeed(seed)	srand(seed)
#define random(max)			random2(0, max)
#define random2(min, max)	((min) + (int32_t) ((max) - (min)) * rand() / 32768)

//GPIO
//flip the pin
#define pinFlip(pin)		digitalWrite(pin, !digitalRead(pin))
void pinMode(PIN_TypeDef pin, uint8_t mode);
void digitalWrite(PIN_TypeDef pin, uint8_t mode);
int digitalRead(PIN_TypeDef pin);

//time base
#if defined(USE_SYSTICK)
#define ticks()				systicks()			//use tmr2 as tick / systick generator
#else
#define ticks()				coreticks()			//use core timer as tick generator
#endif	//USE_SYSTICK

#define coreticks()			(2*_CP0_GET_COUNT())	//core timer advances every 2 ticks
#define coretick_init()		coretimer_init()		//for compatability with older syntax
uint32_t systicks(void);							//use tmr2 as systick
#define millis()			(ticks() / cyclesPerMillisecond())
#define micros()			(ticks() / cyclesPerMicrosecond())
void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);
#define cyclesPerMicrosecond()			(F_CPU / 1000000ul)
#define cyclesPerMillisecond()			(F_CPU / 1000)

//advanced IO
//void tone(void);									//tone frequency specified by F_TONE in STM8Sduino.h
//void noTone(void);
//shiftin/out: bitOrder = MSBFIRST or LSBFIRST
uint8_t shiftIn(PIN_TypeDef dataPin, PIN_TypeDef clockPin, uint8_t bitOrder);
void shiftOut(PIN_TypeDef dataPin, PIN_TypeDef clockPin, uint8_t bitOrder, uint8_t val);
uint32_t pulseIn(PIN_TypeDef pin, uint8_t state);		//wait for a pulse and return timing

//pwm output
//dc = 0x00..0x0fff for pwm2/3/4/5, 0x00..0xffff for pwm1
//RP4=PWM1, RP12=PWM2, RP13=PWM3, RP14=PWM4, RP15=PWM5
void analogWrite(uint8_t pin, uint16_t dc);

//analog read on ADC1
//read DRL first for right aligned results
//uint16_t analogRead(uint8_t pin);

//analog reference - default to AVdd-AVss
//Vref sources: 0->Vref = AVdd-AVss, 1->Vref+-AVss, 2->AVdd-Vref-, 3->Vref+ - Vref-
//void analogReference(uint8_t Vref);

//interrupts
//install external interrupt handler
//mode 1: falling edge, 0: rising edge
//void attachInterrupt(uint8_t intx, void (*isrptr) (void), uint8_t mode);
//void detachInterrupt(uint8_t intx);

//change notification interrupts
//install user CN interrupt handler
//void attachCNInterrupt(void (*isrptr) (void));
//void detachCNInterrupt(void);
//void activateCNInterrupt(uint8_t cnx, uint8_t pue);
//void deactivateCNInterrupt(uint8_t cnx);

//global variables

//core timer
//initialize core timer - used for ticks()
void coretimer_init(void);
//set core timer period
uint32_t coretimer_setpr(uint32_t pr);
uint32_t coretimer_getpr();
//install core timer isr
void coretimerAttachISR(void (*isrptr)(void));

//reset the mcu
void mcuInit(void);

//empty interrupt handler
void empty_handler(void);


//#define Mhz					000000ul	//suffix for Mhz
#define F_UART				(F_PHB)	//8Mhz		//crystal frequency
#define UART_BR300			300ul		//buadrate=300
#define UART_BR600			600ul		//buadrate=600
#define UART_BR1200			1200ul		//buadrate=1200
#define UART_BR2400			2400ul		//buadrate=2400
#define UART_BR4800			4800ul		//buadrate=4800
#define UART_BR9600			9600ul		//buadrate=9600
#define UART_BR19200		19200ul		//buadrate=19200
#define UART_BR38400		38400ul		//buadrate=38400
#define UART_BR57600		57600ul		//buadrate=57600
#define UART_BR115200		115200ul	//buadrate=115200

//for uart1
void uart1Init(unsigned long baud_rate);	//initiate the hardware usart
void uart1Putch(char ch);					//send a char
void uart1Puts(char *str);					//send a string
void uart1Putline(char *ln);				//send a string + line return
uint8_t uart1Getch(void);					//read a char from usart
uint16_t uart1Available(void);				//test if data rx is available
uint16_t uart1Busy(void);					//test if uart tx is busy
void u1Print(char *str, int32_t dat);		//print to uart1
#define u1Println()			uart1Puts("\r\n")
//for compatability
#define uart1Put(ch)		uart1Putch(ch)
#define uart1Get()			uart1Getch()


//for uart2
void uart2Init(unsigned long baud_rate);	//initiate the hardware usart
void uart2Putch(char ch);					//send a char
void uart2Puts(char *str);					//send a string
void uart2Putline(char *ln);				//send a string + line return
uint8_t uart2Getch(void);					//read a char from usart
uint16_t uart2Available(void);				//test if data rx is available
uint16_t uart2Busy(void);					//test if uart tx is busy
void u2Print(char *str, int32_t dat);		//print to uart2
#define u2Println()			uart2Puts("\r\n")
//for compatability
#define uart2Put(ch)		uart2Putch(ch)
#define uart2Get()			uart2Getch()


//end Serial

//tmr1 prescaler
#define TMR1_PS1x			0x00
#define TMR1_PS8x			0x01
#define TMR1_PS64x			0x02
#define TMR1_PS256x			0x03
#define TMR1_PSMASK			TMR1_PS256x

//tmr2-5 prescaler
#define TMR_PS1x			0x00
#define TMR_PS2x			0x01
#define TMR_PS4x			0x02
#define TMR_PS8x			0x03
#define TMR_PS16x			0x04
#define TMR_PS32x			0x05
#define TMR_PS64x			0x06
#define TMR_PS256x			0x07
#define TMR_PSMASK			TMR_PS256x

#define TMR_IPDEFAULT		2
#define TMR_ISDEFAULT		0

void tmr1Init(uint8_t ps, uint16_t period);		//initialize the timer1 (16bit)
void tmr1AttachISR(void (*isrptr)(void));		//activate the isr handler
void tmr2Init(uint8_t ps, uint16_t period);		//initialize the timer2 (16bit)
void tmr2AttachISR(void (*isrptr)(void));		//activate the isr handler
void tmr3Init(uint8_t ps, uint16_t period);		//initialize the timer1 (16bit)
void tmr3AttachISR(void (*isrptr)(void));		//activate the isr handler
void tmr4Init(uint8_t ps, uint16_t period);		//initialize the timer2 (16bit)
void tmr4AttachISR(void (*isrptr)(void));		//activate the isr handler
void tmr5Init(uint8_t ps, uint16_t period);		//initialize the timer1 (16bit)
void tmr5AttachISR(void (*isrptr)(void));		//activate the isr handler
void tmr23Init(uint8_t ps, uint32_t period);		//initialize the timer1 (16bit)
void tmr23AttachISR(void (*isrptr)(void));		//activate the isr handler
uint32_t tmr23Get(void);						//read tmr23
void tmr45Init(uint8_t ps, uint32_t period);		//initialize the timer1 (16bit)
void tmr45AttachISR(void (*isrptr)(void));		//activate the isr handler
uint32_t tmr45Get(void);						//read tmr45

//pwm / oc
//initialize pwm1
void pwm1Init(void);
#define pwm1SetDC(dc)			do {OC1RS = (dc);} while (0)
#define pwm1GetDC()				(OC1RS)

//initialize pwm2
void pwm2Init(void);
#define pwm2SetDC(dc)			do {OC2RS = (dc);} while (0)
#define pwm2GetDC()				(OC2RS)

//initialize pwm3
void pwm3Init(void);
#define pwm3SetDC(dc)			do {OC3RS = (dc);} while (0)
#define pwm3GetDC()				(OC3RS)

//initialize pwm4
void pwm4Init(void);
#define pwm4SetDC(dc)			do {OC4RS = (dc);} while (0)
#define pwm4GetDC()				(OC4RS)

//initialize pwm5
void pwm5Init(void);
#define pwm5SetDC(dc)			do {OC5RS = (dc);} while (0)
#define pwm5GetDC()				(OC5RS)

//adc
//adc channels
#define ADC_AN0						0			//AN0 / RA0
#define ADC_AN1						1			//AN1 / RA1
#define ADC_AN2						2			//AN2 / RB0
#define ADC_AN3						3			//AN3 / RB1
#define ADC_AN4						4			//AN4 / RB2
#define ADC_AN5						5			//AN5 / RB3
#define ADC_AN6						6			//AN6 / RC0
#define ADC_AN7						7			//AN7 / RC1
#define ADC_AN8						8			//AN8 / RC2
#define ADC_AN9						9			//AN9 / RB15
#define ADC_AN10					10			//AN10/ RB14
#define ADC_AN11					11			//AN11/ RB13
#define ADC_AN12					12			//AN12/ RB12
#define ADC_AN13					13			//CTMUT
#define ADC_AN14					14			//internal reference IVref
#define ADC_AN15					15			//Open

//rest the adc
//automatic sampling (ASAM=1), manual conversion
void adcInit(void);

//read the adc
uint16_t analogRead(uint16_t ch);
//end ADC

//output compare
#define OC_IPDEFAULT		2
#define OC_ISDEFAULT		0

void oc1Init(uint16_t pr);						//initialize output compare
void oc1AttachISR(void (*isrptr)(void));		//activate usr isr
void oc2Init(uint16_t pr);						//initialize output compare
void oc2AttachISR(void (*isrptr)(void));		//activate usr isr
void oc3Init(uint16_t pr);						//initialize output compare
void oc3AttachISR(void (*isrptr)(void));		//activate usr isr
void oc4Init(uint16_t pr);						//initialize output compare
void oc4AttachISR(void (*isrptr)(void));		//activate usr isr
void oc5Init(uint16_t pr);						//initialize output compare
void oc5AttachISR(void (*isrptr)(void));		//activate usr isr

//input capture

#define IC_IPDEFAULT		1
#define IC_ISDEFAULT		0

//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic1Init(void);
void ic1AttachISR(void (*isrptr)(void));		//activate user ptr
//uint16_t ic1Get(void);							//read buffer value
#define ic1Get()			IC1BUF				//read buffer value

void ic2Init(void);
void ic2AttachISR(void (*isrptr)(void));		//activate user ptr
//uint16_t ic2Get(void);							//read buffer value
#define ic2Get()			IC2BUF				//read buffer value

void ic3Init(void);
void ic3AttachISR(void (*isrptr)(void));		//activate user ptr
//uint16_t ic3Get(void);							//read buffer value
#define ic3Get()			IC3BUF				//read buffer value

void ic4Init(void);
void ic4AttachISR(void (*isrptr)(void));		//activate user ptr
//uint16_t ic4Get(void);							//read buffer value
#define ic4Get()			IC4BUF				//read buffer value

void ic5Init(void);
void ic5AttachISR(void (*isrptr)(void));		//activate user ptr
//uint16_t ic5Get(void);							//read buffer value
#define ic5Get()			IC5BUF				//read buffer value
//end input capture

//extint
#define INT_IPDEFAULT		6
#define INT_ISDEFAULT		0

void int0Init(void);							//initialize the module
void int0AttachISR(void (*isrptr) (void));		//attach user isr

void int1Init(void);							//initialize the module
void int1AttachISR(void (*isrptr) (void));		//attach user isr

void int2Init(void);							//initialize the module
void int2AttachISR(void (*isrptr) (void));		//attach user isr

void int3Init(void);							//initialize the module
void int3AttachISR(void (*isrptr) (void));		//attach user isr

void int4Init(void);							//initialize the module
void int4AttachISR(void (*isrptr) (void));		//attach user isr
//end extint

//spi

void spi1Init(uint32_t br);						//reset the spi
#define spi1Busy()			(SPI1STATbits.SPITBF)	//transmit buffer full, must wait before writing to SPIxBUF
#define spi1Available()		(!SPI1STATbits.SPIRBE)	//receive buffer not empty -> there is data
#define spi1Write(dat)		SPI1BUF = (dat)		//send data via spi
#define spi1Read()			(SPI1BUF)			//read from the buffer

void spi2Init(uint32_t br);						//reset the spi
#define spi2Busy()			(SPI2STATbits.SPITBF)	//transmit buffer full, must wait before writing to SPIxBUF
#define spi2Available()		(!SPI2STATbits.SPIRBE)	//receive buffer not empty -> there is data
#define spi2Write(dat)		SPI2BUF = (dat)		//send data via spi
#define spi2Read()			(SPI2BUF)			//read from the buffer

//end spi

//i2c
#define I2C_ACK			0
#define I2C_NOACK		1
#define I2C_CMD_WRITE	0
#define I2C_CMD_READ	1

//i2c1
//#define F_I2C1			100000ul		//I2C frequency
void i2c1Init(uint32_t bps);			//initialize the i2c
void i2c1Start(void);					//send a start condition
void i2c1Stop(void);					//send a stop condition
void i2c1Restart(void);					//send a restart condition
//#define i2c1Wait()		do {while (I2C1CON & 0x1f); while (I2C1STATbits.TRSTAT);} while (0)		//wait for i2c
unsigned char i2c1Write(unsigned char dat);			//send i2c
unsigned char i2c1Read(unsigned char ack);			//read i2c

//i2c2
//#define F_I2C2			100000ul		//I2C frequency
void i2c2Init(uint32_t bps);			//initialize the i2c
void i2c2Start(void);					//send a start condition
void i2c2Stop(void);					//send a stop condition
void i2c2Restart(void);					//send a restart condition
//#define i2c1Wait()		do {while (I2C2CON & 0x1f); while (I2C2STATbits.TRSTAT);} while (0)		//wait for i2c
unsigned char i2c2Write(unsigned char dat);			//send i2c
unsigned char i2c2Read(unsigned char ack);			//read i2c
//end i2c

//RTCC
void RTCCInit(void);							//initialize the RTCC
#define RTCCGetTime()		(RTCTIME)			//get rtc time
#define RTCCGetSec()		((RTCTIME >> 8) & 0xff)
#define RTCCGetMin()		((RTCTIME >> 16)& 0xff)
#define RTCCGetHour()		((RTCTIME >> 24)& 0xff)
uint32_t RTCCSetTime(uint32_t val);				//set time
#define RTCCGetDate()		(RTCDATE)			//get rtc date
#define RTCCGetWDay()		(RTCDATE & 0x07)
#define RTCCGetDay()		((RTCDATE >> 8) & 0xff)
#define RTCCGetMonth()		((RTCDATE >> 16)& 0xff)
#define RTCCGetYear()		((RTCDATE >> 24)& 0xff)

uint32_t RTCCSetDate(uint32_t val);				//set date
uint32_t RTCCSetCal(uint32_t offset);			//set calibration
//int32_t RTCCGetCal(void);						//read the calibration
#define RTCCGetCal()		(RTCCONbits.CAL)
//end RTCC

//cnint
#define CN_IPDEFAULT		1
#define CN_ISDEFAULT		0

void cnaInit(uint16_t pins);					//initialize change notification
void cnaAttachISR(void (*isrptr) (void));		//attach user isr
void cnbInit(uint16_t pins);					//initialize change notification
void cnbAttachISR(void (*isrptr) (void));		//attach user isr
#if defined(_PORTC)
void cncInit(uint16_t pins);					//initialize change notification
void cncAttachISR(void (*isrptr) (void));		//attach user isr
#endif		//_PORTC
//end cnint

//comparator voltage reference
//initialize the comparator
void CVrefInit(void);
#define CVrefSet(range)		CVRCONbits.CVR=(range)
#define CVrefGet()			(CVRCONbits.CVR)
#define CVrefOE()			CVRCONbits.CVROE=1
#define CVrefOD()			CVRCONbits.CVROE=0
//end comparator voltage reference

//comparator
//end comparator
//initialize comparator
void CM1Init(void);
#define CM1OUT()			(CM1CONbits.COUT)	//comparator output status
#define CM1INA()			CM1CONbits.CREF= 0	//non-inverting input. 0->CxINA, 1->CVref
#define CM1CVref()			CM1CONbits.CREF= 1	//non-inverting input. 0->CxINA, 1->CVref
#define CM1INB()			CM1CONbits.CCH = 0	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM1INC()			CM1CONbits.CCH = 1	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM1IND()			CM1CONbits.CCH = 2	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM1INIref()			CM1CONbits.CCH = 3	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM1OE()				CM1CONbits.COE = 1	//1->enaboe the output, 0->disable the output
#define CM1OD()				CM1CONbits.COE = 0	//1->enaboe the output, 0->disable the output

//initialize comparator
void CM2Init(void);
#define CM2OUT()			(CM2CONbits.COUT)	//comparator output status
#define CM2INA()			CM2CONbits.CREF= 0	//non-inverting input. 0->CxINA, 1->CVref
#define CM2CVref()			CM2CONbits.CREF= 1	//non-inverting input. 0->CxINA, 1->CVref
#define CM2INB()			CM2CONbits.CCH = 0	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM2INC()			CM2CONbits.CCH = 1	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM2IND()			CM2CONbits.CCH = 2	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM2INIref()			CM2CONbits.CCH = 3	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM2OE()				CM2CONbits.COE = 1	//1->enaboe the output, 0->disable the output
#define CM2OD()				CM2CONbits.COE = 0	//1->enaboe the output, 0->disable the output

//initialize comparator
void CM3Init(void);
#define CM3OUT()			(CM3CONbits.COUT)	//comparator output status
#define CM3INA()			CM3CONbits.CREF= 0	//non-inverting input. 0->CxINA, 1->CVref
#define CM3CVref()			CM3CONbits.CREF= 1	//non-inverting input. 0->CxINA, 1->CVref
#define CM3INB()			CM3CONbits.CCH = 0	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM3INC()			CM3CONbits.CCH = 1	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM3IND()			CM3CONbits.CCH = 2	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM3INIref()			CM3CONbits.CCH = 3	//inverting input. 0->CxINB, 1->CxINC, 2->CxIND, 3->CxIref
#define CM3OE()				CM3CONbits.COE = 1	//1->enaboe the output, 0->disable the output
#define CM3OD()				CM3CONbits.COE = 0	//1->enaboe the output, 0->disable the output

#endif
