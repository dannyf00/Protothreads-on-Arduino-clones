#include "pic32duino.h"				//pic32duino for PIC32MX1xx/2xx chips
//#include "config.h"						//configuration words
//configuration settings
//PIC32MX110/120/130/150/170, PIC32MX210/220/230/250/270

#if   	defined(__32MX110F016B_H) || defined(__32MX110F016C_H) || defined(__32MX110F016D_H) || \
		defined(__32MX120F032B_H) || defined(__32MX120F032C_H) || defined(__32MX120F032D_H) || defined(__32MX120F064H_H) || \
		defined(__32MX130F064B_H) || defined(__32MX130F064C_H) || defined(__32MX130F064D_H) || defined(__32MX130F128H_H) || defined(__32MX130F128L_H) || \
		defined(__32MX150F128B_H) || defined(__32MX150F128C_H) || defined(__32MX150F128D_H) || defined(__32MX150F256H_H) || defined(__32MX150F256L_H) || \
		defined(__32MX170F256B_H) ||                              defined(__32MX170F256D_H) || defined(__32MX170F256H_H) || defined(__32MX170F256L_H) || \
		defined(__32MX210F016B_H) || defined(__32MX210F016C_H) || defined(__32MX210F016D_H) || \
		defined(__32MX220F032B_H) || defined(__32MX220F032C_H) || defined(__32MX220F032D_H) || \
		defined(__32MX230F064B_H) || defined(__32MX230F064C_H) || defined(__32MX230F064D_H) || defined(__32MX230F128H_H) || defined(__32MX230F128L_H) || \
		defined(__32MX250F128B_H) || defined(__32MX250F128C_H) || defined(__32MX250F128D_H) || defined(__32MX250F256H_H) || defined(__32MX250F256L_H) || \
		defined(__32MX270F256B_H) ||                              defined(__32MX270F256D_H) || defined(__32MX270F256H_H) || defined(__32MX270F256L_H)

#pragma config FNOSC = FRC						//oscillator selection bits = FRC/FRCPLL/PRI/PRIPLL/SOSC/LPRC/FRCDIV16/FRCDIV,
#pragma config FSOSCEN = ON						//secondary oscillator off/ON
#pragma config IESO = OFF						//internal/external switch-over
#pragma config POSCMOD = HS						//primary oscilator configuration = OFF/HS/XT/EC
//PLL configuration.
//F_SYSCLK = F_OSC / FPLLIDIV * FPLLMUL / FPLLODIV.
#pragma config FPLLIDIV = DIV_2					//PLL input divider=DIV_1/2/3/4/5/6/10/12 (4Mhz < F_OSC / FPLLIDIV < 5Mhz)
#pragma config FPLLMUL = MUL_16					//PLL multiplier=MUL_15/16/17/18/19/20/21/24
#pragma config FPLLODIV = DIV_4					//PLL output divider=DIV_1/2/4/8/16/32/64/256
//end PLL configuration
//F_PBDIV = F_SYSCLK / FPBDIV
#pragma config FPBDIV = DIV_8					//peripheral bus clock divider = 8x
#pragma config OSCIOFNC = OFF, FCKSM = CSECMD	//clock output disabled, clock switching disabled
#pragma config ICESEL = ICS_PGx1				//RESERVED				//use PGD1/PGC1,
#pragma config PMDL1WAY = OFF, IOL1WAY = OFF	//peripheral configuration allows multiple configuration (OFF) or one configuration (ON), PPS allows multiple configuration (OFF)/one configuration(ON)
#pragma config FUSBIDIO = OFF, FVBUSONIO = OFF	//USBID pin controoled by port functions (OFF)/or USB module (ON), Vbuson pin controlled by port function (OFF)/USB module (ON)
#pragma config FWDTEN = OFF, WDTPS = PS32768	//watchdog timer disabled, watchdog timer prescaler = 32768
#pragma config WINDIS = OFF, FWDTWINSZ = WINSZ_75		//watchdog timer window disabled, watchdog timer window size =75%
#pragma config PWP = OFF, BWP = OFF, CP = OFF	//boot flash write-protection off, power-on protection off, code protection off
//#pragma config DEBUG = OFF					//OFF = debugger disabled. ON = debugger enabled -> *****needs to be unchecked to run code under pic32prog + pickit2*****
#pragma config JTAGEN = OFF						//jtag off

//set up usb divider
#if		defined(__32MX210F016B_H) || defined(__32MX210F016C_H) || defined(__32MX210F016D_H) || \
		defined(__32MX220F032B_H) || defined(__32MX220F032C_H) || defined(__32MX220F032D_H) || \
		defined(__32MX230F064B_H) || defined(__32MX230F064C_H) || defined(__32MX230F064D_H) || defined(__32MX230F128H_H) || defined(__32MX230F128L_H) || \
		defined(__32MX250F128B_H) || defined(__32MX250F128C_H) || defined(__32MX250F128D_H) || defined(__32MX250F256H_H) || defined(__32MX250F256L_H) || \
		defined(__32MX270F256B_H) ||                              defined(__32MX270F256D_H) || defined(__32MX270F256H_H) || defined(__32MX270F256L_H)
#pragma config UPLLIDIV = DIV_1, UPLLEN = OFF	//USB PLL div=1, USB PLL enable=off/on
#endif

/*PIC32MX130F064B
Peripheral Module Disable Configuration:
 PMDL1WAY = OFF Allow multiple reconfigurations
PMDL1WAY = ON Allow only one reconfiguration

Peripheral Pin Select Configuration:
 IOL1WAY = OFF Allow multiple reconfigurations
IOL1WAY = ON Allow only one reconfiguration

USB USID Selection:
 FUSBIDIO = OFF Controlled by Port Function
FUSBIDIO = ON Controlled by the USB Module

USB VBUS ON Selection:
 FVBUSONIO = OFF Controlled by Port Function
FVBUSONIO = ON Controlled by USB Module

PLL Input Divider:
 FPLLIDIV = DIV_1 1x Divider
FPLLIDIV = DIV_2 2x Divider
FPLLIDIV = DIV_3 3x Divider
FPLLIDIV = DIV_4 4x Divider
FPLLIDIV = DIV_5 5x Divider
FPLLIDIV = DIV_6 6x Divider
FPLLIDIV = DIV_10 10x Divider
FPLLIDIV = DIV_12 12x Divider

PLL Multiplier:
 FPLLMUL = MUL_15 15x Multiplier
FPLLMUL = MUL_16 16x Multiplier
FPLLMUL = MUL_17 17x Multiplier
FPLLMUL = MUL_18 18x Multiplier
FPLLMUL = MUL_19 19x Multiplier
FPLLMUL = MUL_20 20x Multiplier
FPLLMUL = MUL_21 21x Multiplier
FPLLMUL = MUL_24 24x Multiplier

System PLL Output Clock Divider:
 FPLLODIV = DIV_1 PLL Divide by 1
FPLLODIV = DIV_2 PLL Divide by 2
FPLLODIV = DIV_4 PLL Divide by 4
FPLLODIV = DIV_8 PLL Divide by 8
FPLLODIV = DIV_16 PLL Divide by 16
FPLLODIV = DIV_32 PLL Divide by 32
FPLLODIV = DIV_64 PLL Divide by 64
FPLLODIV = DIV_256 PLL Divide by 256

Oscillator Selection Bits:
 FNOSC = FRC Fast RC Osc (FRC)
FNOSC = FRCPLL Fast RC Osc with PLL
FNOSC = PRI Primary Osc (XT,HS,EC)
FNOSC = PRIPLL Primary Osc w/PLL (XT+,HS+,EC+PLL)
FNOSC = SOSC Low Power Secondary Osc (SOSC)
FNOSC = LPRC Low Power RC Osc (LPRC)
FNOSC = FRCDIV16 Fast RC Osc w/Div-by-16 (FRC/16)
FNOSC = FRCDIV Fast RC Osc w/Div-by-N (FRCDIV)

Secondary Oscillator Enable:
 FSOSCEN = OFF Disabled
FSOSCEN = ON Enabled

Internal/External Switch Over:
 IESO = OFF Disabled
IESO = ON Enabled

Primary Oscillator Configuration:
 POSCMOD = EC External clock mode
POSCMOD = XT XT osc mode
POSCMOD = HS HS osc mode
POSCMOD = OFF Primary osc disabled

CLKO Output Signal Active on the OSCO Pin:
 OSCIOFNC = ON Enabled
OSCIOFNC = OFF Disabled

Peripheral Clock Divisor:
 FPBDIV = DIV_1 Pb_Clk is Sys_Clk/1
FPBDIV = DIV_2 Pb_Clk is Sys_Clk/2
FPBDIV = DIV_4 Pb_Clk is Sys_Clk/4
FPBDIV = DIV_8 Pb_Clk is Sys_Clk/8

Clock Switching and Monitor Selection:
 FCKSM = CSECME Clock Switch Enable, FSCM Enabled
FCKSM = CSECMD Clock Switch Enable, FSCM Disabled
FCKSM = CSDCMD Clock Switch Disable, FSCM Disabled

Watchdog Timer Postscaler:
 WDTPS = PS1 1:1
WDTPS = PS2 1:2
WDTPS = PS4 1:4
WDTPS = PS8 1:8
WDTPS = PS16 1:16
WDTPS = PS32 1:32
WDTPS = PS64 1:64
WDTPS = PS128 1:128
WDTPS = PS256 1:256
WDTPS = PS512 1:512
WDTPS = PS1024 1:1024
WDTPS = PS2048 1:2048
WDTPS = PS4096 1:4096
WDTPS = PS8192 1:8192
WDTPS = PS16384 1:16384
WDTPS = PS32768 1:32768
WDTPS = PS65536 1:65536
WDTPS = PS131072 1:131072
WDTPS = PS262144 1:262144
WDTPS = PS524288 1:524288
WDTPS = PS1048576 1:1048576

Watchdog Timer Window Enable:
 WINDIS = ON Watchdog Timer is in Window Mode
WINDIS = OFF Watchdog Timer is in Non-Window Mode

Watchdog Timer Enable:
 FWDTEN = OFF WDT Disabled (SWDTEN Bit Controls)
FWDTEN = ON WDT Enabled

Watchdog Timer Window Size:
 FWDTWINSZ = WINSZ_75 Window Size is 75%
FWDTWINSZ = WINSZ_50 Window Size is 50%
FWDTWINSZ = WINSZ_37 Window Size is 37.5%
FWDTWINSZ = WISZ_25 Window Size is 25%

Background Debugger Enable:
 DEBUG = ON Debugger is Enabled
DEBUG = OFF Debugger is Disabled

JTAG Enable:
 JTAGEN = OFF JTAG Disabled
JTAGEN = ON JTAG Port Enabled

ICE/ICD Comm Channel Select:
 ICESEL = RESERVED Reserved
ICESEL = ICS_PGx3 Communicate on PGEC3/PGED3
ICESEL = ICS_PGx2 Communicate on PGEC2/PGED2
ICESEL = ICS_PGx1 Communicate on PGEC1/PGED1

Program Flash Write Protect:
 PWP = PWP32K First 32K
PWP = PWP31K First 31K
PWP = PWP30K First 30K
PWP = PWP29K First 29K
PWP = PWP28K First 28K
PWP = PWP27K First 27K
PWP = PWP26K First 26K
PWP = PWP25K First 25K
PWP = PWP24K First 24K
PWP = PWP23K First 23K
PWP = PWP22K First 22K
PWP = PWP21K First 21K
PWP = PWP20K First 20K
PWP = PWP19K First 19K
PWP = PWP18K First 18K
PWP = PWP17K First 17K
PWP = PWP16K First 16K
PWP = PWP15K First 15K
PWP = PWP14K First 14K
PWP = PWP13K First 13K
PWP = PWP12K First 12K
PWP = PWP11K First 11K
PWP = PWP10K First 10K
PWP = PWP9K First 9K
PWP = PWP8K First 8K
PWP = PWP7K First 7K
PWP = PWP6K First 6K
PWP = PWP5K First 5K
PWP = PWP4K First 4K
PWP = PWP3K First 3K
PWP = PWP2K First 2K
PWP = PWP1K First 1K
PWP = OFF Disable

Boot Flash Write Protect bit:
 BWP = ON Protection Enabled
BWP = OFF Protection Disabled

Code Protect:
 CP = ON Protection Enabled
CP = OFF Protection Disabled
*/
#else
#warning: PIC32duino.c: no device configure bits specified
#endif	//pic32mx1xx/2xx

//global defines

//global variables
//declare pins
//ALL PINS ARE MAPPED, WHETHER THEY EXIST OR NOT
//SO MAKE SURE THAT THE PINS YOU PICKED ACTUALLY EXIST FOR YOUR PACKAGE
//Pin  0.. 7 -> GPIOA
//Pin  8..15 -> GPIOB
const PIN2GPIO GPIO_PinDef[]= {
	{GPIOA, 1<<0},						//PICduino Pin  0 = RP0/PB0/CHIP PIN4
	{GPIOA, 1<<1},						//PICduino Pin  1 = RP1/PB1/CHIP PIN5
	{GPIOA, 1<<2},						//PICduino Pin  2 = RP2/PB2/CHIP PIN6
	{GPIOA, 1<<3},						//PICduino Pin  3 = RP3/PB3/CHIP PIN7
	{GPIOA, 1<<4},						//PICduino Pin  4 = RP4/PB4/CHIP PIN11
	{GPIOA, 1<<5},						//PICduino Pin  5 = RP5/PB5/CHIP PIN14
	{GPIOA, 1<<6},						//PICduino Pin  6 = RP6/PB6/CHIP PIN15
	{GPIOA, 1<<7},						//PICduino Pin  7 = RP7/PB7/CHIP PIN16
	{GPIOA, 1<<8},						//PICduino Pin  8 = RP8/PB8/CHIP PIN17
	{GPIOA, 1<<9},						//PICduino Pin  9 = RP9/PB9/CHIP PIN18
	{GPIOA, 1<<10},						//PICduino Pin 10 = RP10/PB10/CHIP PIN21
	{GPIOA, 1<<11},						//PICduino Pin 11 = RP11/PB11/CHIP PIN22
	{GPIOA, 1<<12},						//PICduino Pin 12 = RP12/PB12/CHIP PIN23
	{GPIOA, 1<<13},						//PICduino Pin 13 = RP13/PB13/CHIP PIN24
	{GPIOA, 1<<14},						//PICduino Pin 14 = RP14/PB14/CHIP PIN25
	{GPIOA, 1<<15},						//PICduino Pin 15 = RP15/PB15/CHIP PIN26

	{GPIOB, 1<<0},						//PICduino Pin 16 = RP0/PB0/CHIP PIN4
	{GPIOB, 1<<1},						//PICduino Pin 17 = RP1/PB1/CHIP PIN5
	{GPIOB, 1<<2},						//PICduino Pin 18 = RP2/PB2/CHIP PIN6
	{GPIOB, 1<<3},						//PICduino Pin 19 = RP3/PB3/CHIP PIN7
	{GPIOB, 1<<4},						//PICduino Pin 20 = RP4/PB4/CHIP PIN11
	{GPIOB, 1<<5},						//PICduino Pin 21 = RP5/PB5/CHIP PIN14
	{GPIOB, 1<<6},						//PICduino Pin 22 = RP6/PB6/CHIP PIN15
	{GPIOB, 1<<7},						//PICduino Pin 23 = RP7/PB7/CHIP PIN16
	{GPIOB, 1<<8},						//PICduino Pin 24 = RP8/PB8/CHIP PIN17
	{GPIOB, 1<<9},						//PICduino Pin 25 = RP9/PB9/CHIP PIN18
	{GPIOB, 1<<10},						//PICduino Pin 26 = RP10/PB10/CHIP PIN21
	{GPIOB, 1<<11},						//PICduino Pin 27 = RP11/PB11/CHIP PIN22
	{GPIOB, 1<<12},						//PICduino Pin 28 = RP12/PB12/CHIP PIN23
	{GPIOB, 1<<13},						//PICduino Pin 29 = RP13/PB13/CHIP PIN24
	{GPIOB, 1<<14},						//PICduino Pin 30 = RP14/PB14/CHIP PIN25
	{GPIOB, 1<<15},						//PICduino Pin 31 = RP15/PB15/CHIP PIN26

#if defined(GPIOC)
	{GPIOC, 1<<0},						//PICduino Pin 32 = RP0/PB0/CHIP PIN4
	{GPIOC, 1<<1},						//PICduino Pin 33 = RP1/PB1/CHIP PIN5
	{GPIOC, 1<<2},						//PICduino Pin 34 = RP2/PB2/CHIP PIN6
	{GPIOC, 1<<3},						//PICduino Pin 35 = RP3/PB3/CHIP PIN7
	{GPIOC, 1<<4},						//PICduino Pin 36 = RP4/PB4/CHIP PIN11
	{GPIOC, 1<<5},						//PICduino Pin 37 = RP5/PB5/CHIP PIN14
	{GPIOC, 1<<6},						//PICduino Pin 38 = RP6/PB6/CHIP PIN15
	{GPIOC, 1<<7},						//PICduino Pin 39 = RP7/PB7/CHIP PIN16
	{GPIOC, 1<<8},						//PICduino Pin 40 = RP8/PB8/CHIP PIN17
	{GPIOC, 1<<9},						//PICduino Pin 41 = RP9/PB9/CHIP PIN18
	{GPIOC, 1<<10},						//PICduino Pin 42 = RP10/PB10/CHIP PIN21
	{GPIOC, 1<<11},						//PICduino Pin 43 = RP11/PB11/CHIP PIN22
	{GPIOC, 1<<12},						//PICduino Pin 44 = RP12/PB12/CHIP PIN23
	{GPIOC, 1<<13},						//PICduino Pin 45 = RP13/PB13/CHIP PIN24
	{GPIOC, 1<<14},						//PICduino Pin 46 = RP14/PB14/CHIP PIN25
	{GPIOC, 1<<15},						//PICduino Pin 47 = RP15/PB15/CHIP PIN26
#endif	//GPIOC

#if defined(GPIOD)
	{GPIOD, 1<<0},						//PICduino Pin 32 = RP0/PB0/CHIP PIN4
	{GPIOD, 1<<1},						//PICduino Pin 33 = RP1/PB1/CHIP PIN5
	{GPIOD, 1<<2},						//PICduino Pin 34 = RP2/PB2/CHIP PIN6
	{GPIOD, 1<<3},						//PICduino Pin 35 = RP3/PB3/CHIP PIN7
	{GPIOD, 1<<4},						//PICduino Pin 36 = RP4/PB4/CHIP PIN11
	{GPIOD, 1<<5},						//PICduino Pin 37 = RP5/PB5/CHIP PIN14
	{GPIOD, 1<<6},						//PICduino Pin 38 = RP6/PB6/CHIP PIN15
	{GPIOD, 1<<7},						//PICduino Pin 39 = RP7/PB7/CHIP PIN16
	{GPIOD, 1<<8},						//PICduino Pin 40 = RP8/PB8/CHIP PIN17
	{GPIOD, 1<<9},						//PICduino Pin 41 = RP9/PB9/CHIP PIN18
	{GPIOD, 1<<10},						//PICduino Pin 42 = RP10/PB10/CHIP PIN21
	{GPIOD, 1<<11},						//PICduino Pin 43 = RP11/PB11/CHIP PIN22
	{GPIOD, 1<<12},						//PICduino Pin 44 = RP12/PB12/CHIP PIN23
	{GPIOD, 1<<13},						//PICduino Pin 45 = RP13/PB13/CHIP PIN24
	{GPIOD, 1<<14},						//PICduino Pin 46 = RP14/PB14/CHIP PIN25
	{GPIOD, 1<<15},						//PICduino Pin 47 = RP15/PB15/CHIP PIN26
#endif	//GPIOD

#if defined(GPIOE)
	{GPIOE, 1<<0},						//PICduino Pin 32 = RP0/PB0/CHIP PIN4
	{GPIOE, 1<<1},						//PICduino Pin 33 = RP1/PB1/CHIP PIN5
	{GPIOE, 1<<2},						//PICduino Pin 34 = RP2/PB2/CHIP PIN6
	{GPIOE, 1<<3},						//PICduino Pin 35 = RP3/PB3/CHIP PIN7
	{GPIOE, 1<<4},						//PICduino Pin 36 = RP4/PB4/CHIP PIN11
	{GPIOE, 1<<5},						//PICduino Pin 37 = RP5/PB5/CHIP PIN14
	{GPIOE, 1<<6},						//PICduino Pin 38 = RP6/PB6/CHIP PIN15
	{GPIOE, 1<<7},						//PICduino Pin 39 = RP7/PB7/CHIP PIN16
	{GPIOE, 1<<8},						//PICduino Pin 40 = RP8/PB8/CHIP PIN17
	{GPIOE, 1<<9},						//PICduino Pin 41 = RP9/PB9/CHIP PIN18
	{GPIOE, 1<<10},						//PICduino Pin 42 = RP10/PB10/CHIP PIN21
	{GPIOE, 1<<11},						//PICduino Pin 43 = RP11/PB11/CHIP PIN22
	{GPIOE, 1<<12},						//PICduino Pin 44 = RP12/PB12/CHIP PIN23
	{GPIOE, 1<<13},						//PICduino Pin 45 = RP13/PB13/CHIP PIN24
	{GPIOE, 1<<14},						//PICduino Pin 46 = RP14/PB14/CHIP PIN25
	{GPIOE, 1<<15},						//PICduino Pin 47 = RP15/PB15/CHIP PIN26
#endif	//GPIOE

#if defined(GPIOF)
	{GPIOF, 1<<0},						//PICduino Pin 32 = RP0/PB0/CHIP PIN4
	{GPIOF, 1<<1},						//PICduino Pin 33 = RP1/PB1/CHIP PIN5
	{GPIOF, 1<<2},						//PICduino Pin 34 = RP2/PB2/CHIP PIN6
	{GPIOF, 1<<3},						//PICduino Pin 35 = RP3/PB3/CHIP PIN7
	{GPIOF, 1<<4},						//PICduino Pin 36 = RP4/PB4/CHIP PIN11
	{GPIOF, 1<<5},						//PICduino Pin 37 = RP5/PB5/CHIP PIN14
	{GPIOF, 1<<6},						//PICduino Pin 38 = RP6/PB6/CHIP PIN15
	{GPIOF, 1<<7},						//PICduino Pin 39 = RP7/PB7/CHIP PIN16
	{GPIOF, 1<<8},						//PICduino Pin 40 = RP8/PB8/CHIP PIN17
	{GPIOF, 1<<9},						//PICduino Pin 41 = RP9/PB9/CHIP PIN18
	{GPIOF, 1<<10},						//PICduino Pin 42 = RP10/PB10/CHIP PIN21
	{GPIOF, 1<<11},						//PICduino Pin 43 = RP11/PB11/CHIP PIN22
	{GPIOF, 1<<12},						//PICduino Pin 44 = RP12/PB12/CHIP PIN23
	{GPIOF, 1<<13},						//PICduino Pin 45 = RP13/PB13/CHIP PIN24
	{GPIOF, 1<<14},						//PICduino Pin 46 = RP14/PB14/CHIP PIN25
	{GPIOF, 1<<15},						//PICduino Pin 47 = RP15/PB15/CHIP PIN26
#endif	//GPIOF

#if defined(GPIOG)
	{GPIOG, 1<<0},						//PICduino Pin 32 = RP0/PB0/CHIP PIN4
	{GPIOG, 1<<1},						//PICduino Pin 33 = RP1/PB1/CHIP PIN5
	{GPIOG, 1<<2},						//PICduino Pin 34 = RP2/PB2/CHIP PIN6
	{GPIOG, 1<<3},						//PICduino Pin 35 = RP3/PB3/CHIP PIN7
	{GPIOG, 1<<4},						//PICduino Pin 36 = RP4/PB4/CHIP PIN11
	{GPIOG, 1<<5},						//PICduino Pin 37 = RP5/PB5/CHIP PIN14
	{GPIOG, 1<<6},						//PICduino Pin 38 = RP6/PB6/CHIP PIN15
	{GPIOG, 1<<7},						//PICduino Pin 39 = RP7/PB7/CHIP PIN16
	{GPIOG, 1<<8},						//PICduino Pin 40 = RP8/PB8/CHIP PIN17
	{GPIOG, 1<<9},						//PICduino Pin 41 = RP9/PB9/CHIP PIN18
	{GPIOG, 1<<10},						//PICduino Pin 42 = RP10/PB10/CHIP PIN21
	{GPIOG, 1<<11},						//PICduino Pin 43 = RP11/PB11/CHIP PIN22
	{GPIOG, 1<<12},						//PICduino Pin 44 = RP12/PB12/CHIP PIN23
	{GPIOG, 1<<13},						//PICduino Pin 45 = RP13/PB13/CHIP PIN24
	{GPIOG, 1<<14},						//PICduino Pin 46 = RP14/PB14/CHIP PIN25
	{GPIOG, 1<<15},						//PICduino Pin 47 = RP15/PB15/CHIP PIN26
#endif	//GPIOG
};

//set up core timer
//global variables
uint32_t SystemCoreClock=F_FRC;					//System core clock, in Hz, = SYSCLK, updated by SystemCoreClockUpdate()
volatile uint32_t systick_count=0;				//systick counter

//read sysclock back
//needs to be executed during mcu initialization or after oscillator reconfiguration
//returns SystemCoreClock
//Need to set fuse settings to ensure correct PLL operations
uint32_t SystemCoreClockUpdate(void) {
	uint32_t tmp=F_FRC;									//read osccon

	switch (OSCCON & CLKCOSC_FRCDIV) {				//read current oscillator bits
	case CLKCOSC_FRCDIV: 						//FRCDIV
		tmp = F_FRC;
		switch (OSCCON & CLKFRCDIV_256) {
		case CLKFRCDIV_256:
			tmp /=256;
			break;
		case CLKFRCDIV_64:
			tmp /= 64;
			break;
		case CLKFRCDIV_32:
			tmp /= 32;
			break;
		case CLKFRCDIV_16:
			tmp /= 16;
			break;
		case CLKFRCDIV_8:
			tmp /=  8;
			break;
		case CLKFRCDIV_4:
			tmp /=  4;
			break;
		case CLKFRCDIV_2:
			tmp /=  2;
			break;
		case CLKFRCDIV_1:
			tmp /=  1;
			break;
		}
		break;
	case CLKCOSC_FRC16:							//FRC / 16
		tmp = F_FRC / 16;
		break;
	case CLKCOSC_LPRC:							//LPRC
		tmp = F_LPRC;
		break;
	case CLKCOSC_SOSC:							//SOSC
		tmp = F_SOSC;
		break;
	case CLKCOSC_POSCPLL:						//Posc + PLL
		tmp = F_XTAL;
		//read FPLLIDIV
		switch (DEVCFG2bits.FPLLIDIV) {
		case 0b111:
			tmp /= 12;
			break;
		case 0b110:
			tmp /= 10;
			break;
		case 0b101:
			tmp /= 6;
			break;
		case 0b100:
			tmp /= 5;
			break;
		case 0b011:
			tmp /= 4;
			break;
		case 0b010:
			tmp /= 3;
			break;
		case 0b001:
			tmp /= 2;
			break;		//default
		case 0b000:
			tmp /= 1;
			break;
		}
		//read the multipliers first
		switch (OSCCON & CLKPLLMULT_24) {
		case CLKPLLMULT_24:
			tmp *= 24;
			break;
		case CLKPLLMULT_21:
			tmp *= 21;
			break;
		case CLKPLLMULT_20:
			tmp *= 20;
			break;
		case CLKPLLMULT_19:
			tmp *= 19;
			break;
		case CLKPLLMULT_18:
			tmp *= 18;
			break;
		case CLKPLLMULT_17:
			tmp *= 17;
			break;
		case CLKPLLMULT_16:
			tmp *= 16;
			break;
		case CLKPLLMULT_15:
			tmp *= 15;
			break;
		}
		//read the divider
		switch (OSCCON & CLKPLLDIV_256) {
		case CLKPLLDIV_256:
			tmp /=256;
			break;
		case CLKPLLDIV_64:
			tmp /= 64;
			break;
		case CLKPLLDIV_32:
			tmp /= 32;
			break;
		case CLKPLLDIV_16:
			tmp /= 16;
			break;
		case CLKPLLDIV_8:
			tmp /=  8;
			break;
		case CLKPLLDIV_4:
			tmp /=  4;
			break;
		case CLKPLLDIV_2:
			tmp /=  2;
			break;
		case CLKPLLDIV_1:
			tmp /=  1;
			break;
		}
		break;
	case CLKCOSC_POSC: 							//Posc
		tmp = F_XTAL;
		break;
	case CLKCOSC_FRCPLL:						//FRCPLL
		tmp = F_FRC;							//FRC input PLL divider set to DIV_2 in config bits
		//read FPLLIDIV
		switch (DEVCFG2bits.FPLLIDIV) {
		case 0b111:
			tmp /= 12;
			break;
		case 0b110:
			tmp /= 10;
			break;
		case 0b101:
			tmp /= 6;
			break;
		case 0b100:
			tmp /= 5;
			break;
		case 0b011:
			tmp /= 4;
			break;
		case 0b010:
			tmp /= 3;
			break;
		case 0b001:
			tmp /= 2;
			break;		//default
		case 0b000:
			tmp /= 1;
			break;
		}
		//read the multipliers first
		switch (OSCCON & CLKPLLMULT_24) {
		case CLKPLLMULT_24:
			tmp *= 24;
			break;
		case CLKPLLMULT_21:
			tmp *= 21;
			break;
		case CLKPLLMULT_20:
			tmp *= 20;
			break;
		case CLKPLLMULT_19:
			tmp *= 19;
			break;
		case CLKPLLMULT_18:
			tmp *= 18;
			break;
		case CLKPLLMULT_17:
			tmp *= 17;
			break;
		case CLKPLLMULT_16:
			tmp *= 16;
			break;
		case CLKPLLMULT_15:
			tmp *= 15;
			break;
		}
		//read the divider
		switch (OSCCON & CLKPLLDIV_256) {
		case CLKPLLDIV_256:
			tmp /= 256;
			break;
		case CLKPLLDIV_64:
			tmp /= 64;
			break;
		case CLKPLLDIV_32:
			tmp /= 32;
			break;
		case CLKPLLDIV_16:
			tmp /= 16;
			break;
		case CLKPLLDIV_8:
			tmp /=  8;
			break;
		case CLKPLLDIV_4:
			tmp /=  4;
			break;
		case CLKPLLDIV_2:
			tmp /=  2;
			break;
		case CLKPLLDIV_1:
			tmp /=  1;
			break;
		}
		break;
	case CLKCOSC_FRC: 							//internal oscillator
		tmp = F_FRC;
		break;
	}
	return SystemCoreClock = tmp;					//update _F_CPU
}

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
//cannot run in 16-bit mode
uint32_t SystemCoreClockSwitch(uint8_t nosc) {
	unsigned int tmp=__builtin_get_isr_state();								//read current isr state

	//disable interrupt and dma
	di();
	do {
		//perform the unlock sequency
		SYSKEY = 0xAA996655;
		SYSKEY = 0x556699AA;
		//sett the nosc bits
		OSCCONbits.NOSC = nosc;						//set the nosc bits
		OSCCONbits.OSWEN = 1;						//1->initiate the switch
		SYSKEY = 0x33333333;						//relock the osccon
	} while (OSCCONbits.OSWEN);						//1->switch not successful
	ei();
	__builtin_set_isr_state(tmp);					//restore isr state
	return SystemCoreClockUpdate();
}

//initialize core timer compare / period
uint32_t _coretimer_pr=0;							//core timer period
static void (* _coretimer_isrptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//initialize core timer - used for ticks()
void coretimer_init(void) {
	//reset the handler
	_coretimer_isrptr = empty_handler;

	//do nothing as the core timer is always running

	//clear the flag
	//IFS0CLR = _IFS0_CTIF_MASK;

	//disable core timer interrupt
	// Set up core timer interrupt
	// clear core timer interrupt flag
	IFS0CLR = _IFS0_CTIF_MASK;
	// set core time interrupt priority of 2
	IPC0CLR = _IPC0_CTIP_MASK;
	IPC0SET = (2 << _IPC0_CTIP_POSITION);
	// set core time interrupt subpriority of 0
	IPC0CLR = _IPC0_CTIS_MASK;
	IPC0SET = (0 << _IPC0_CTIS_POSITION);
	// disenable core timer interrupt
	IEC0CLR = _IEC0_CTIE_MASK;
	IEC0CLR = (1 << _IEC0_CTIE_POSITION);

	//_coretimer_isrptr=empty_handler;
}

//set core timer period
uint32_t coretimer_setpr(uint32_t pr) {
	_coretimer_pr = pr / 2;
	_CP0_SET_COMPARE(_CP0_GET_COMPARE() + _coretimer_pr);
	return coreticks();
}

//get core timer period
uint32_t coretimer_getpr(void) {
	return _coretimer_pr;
}

//core timer isr
void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void) {
	IFS0CLR = _IFS0_CTIF_MASK;						//clear the flag
	_CP0_SET_COMPARE(_CP0_GET_COMPARE() + _coretimer_pr);				//flag cleared when COMPARE is written
	//execute user handler
	_coretimer_isrptr();
}

//install core timer isr
void coretimerAttachISR(void (*isrptr)(void)) {
	_coretimer_isrptr=isrptr;						//activate the isr handler
	IFS0CLR = _IFS0_CTIF_MASK;						//clear the flag
	IEC0SET = (1 << _IEC0_CTIE_POSITION);			//enable the interrupt
}


//reset the mcu
//FRCDIV set to 1:1
//PBDIV set to 1:1
void mcuInit(void) {
	//initialize the core timer
	coretimer_init();

	/* Set the system and peripheral bus speeds and enable the program cache*/

	//SYSTEMConfigPerformance( F_CPU );

	//mOSCSetPBDIV( OSC_PB_DIV_2 );

	//clock defaults to FRC
	//set PBDIV to 1:1
	//unlock sequency
	//SYSKEY = 0x0; 									// ensure OSCCON is locked
	//SYSKEY = 0xAA996655; 								// Write Key1 to SYSKEY
	//SYSKEY = 0x556699AA; 								// Write Key2 to SYSKEY
	SYS_UNLOCK();
	// OSCCON is now unlocked
	// make the desired change
	//OSCCON = (OSCCON &~0x00180000ul) | (0x00 & 0x00180000ul);	//or to set through config bits
	OSCCONbits.PBDIV = 0;								//PBDIV: 0->1:1, 1->2:1, 2->4:1, 3->8:1 (default(
	//configure rcdiv for FRCDIV
	OSCCONbits.FRCDIV = 1;								//front rc divider (0..7->1:1..128:1). 0->1:1, 1->2:1 (default)
	//lock sequency
	//SYSKEY = 0x00;									//write any value to lock
	SYS_LOCK();

	//turn off all peripherals
	PMD1=0xffff;
	PMD2=0xffff;
	PMD3=0xffff;
	PMD4=0xffff;
	PMD5=0xffff;
	PMD6=0xffff;

	//all pins digital
	ANSELA = 0x0000;
	ANSELB = 0x0000;
#if defined(_PORTC)
	ANSELC = 0x0000;
#endif

	//disable interrupts
	//__builtin_disable_interrupts();			//disable interrupts
	//INTDisableInterrupts();
	//enable multivector mode
	//INTCONbits.MVEC = 1;						//1=enable multiple vector
	//__builtin_enable_interrupts();			//enable interrupts
	//INTEnableInterrupts();
	//INTEnableSystemMultiVectoredInt();
	INTCONbits.MVEC = 1;						//1=enable multi-vectored interrupts, 0=disable

	//initialize tmr2 for pwm generation / systick timer
	PMD4bits.T2MD = 0;							//0->enable the peripheral, 1->disable the peripheral
	T2CON = 0x0000;                 			//stop timer
	T2CONbits.TCKPS = 0;						//set the prescaler: 0->1:1
	T2CONbits.TCS = 0;             				//use internal instruction clock from F_PHB
	T2CONbits.TGATE = 0;            			//no gating
	T2CONbits.T32 = 0;							//0->16 bit mode, 1->32 bit mode
	TMR2 = 0;
	PR2 = PWM_PR;								//set pwm period
	IFS0bits.T2IF = 0;							//reset the flag
	IEC0bits.T2IE = 1;							//0->disable tmr2 isr, 1->enable tmr2 isr (for systick generation)
	IPC2bits.T2IP = TMR_IPDEFAULT;
	IPC2bits.T2IS = TMR_ISDEFAULT;
	T2CONbits.TON = 1;             				//turn on the timer

	//update sysclk
	SystemCoreClockUpdate();					//update SystemCoreClock


	//enable global interrupts
	ei();										//testing
}

//empty interrupt handler
void empty_handler(void) {
	//do nothing here
}

//C main loop
int main(void) {

	mcuInit();						//reset the mcu
	setup();						//run the setup code
	while (1) {
		loop();						//run the default loop
	}
}

//Arduino Functions: GPIO
//set a pin mode to INPUT or OUTPUT
//no error checking on PIN
inline void pinMode(PIN_TypeDef pin, uint8_t mode) {
	if (mode==INPUT) FIO_IN(GPIO_PinDef[pin].gpio, GPIO_PinDef[pin].mask);
	else FIO_OUT(GPIO_PinDef[pin].gpio, GPIO_PinDef[pin].mask);
}

//set / clear a pin
inline void digitalWrite(PIN_TypeDef pin, uint8_t val) {
	if (val==LOW) FIO_CLR(GPIO_PinDef[pin].gpio, GPIO_PinDef[pin].mask);
	else FIO_SET(GPIO_PinDef[pin].gpio, GPIO_PinDef[pin].mask);
}

//read a pin
inline int digitalRead(PIN_TypeDef pin) {
	return (FIO_GET(GPIO_PinDef[pin].gpio, GPIO_PinDef[pin].mask))?HIGH:LOW;
}
//end GPIO

//ticks()
//Arduino Functions: Time
//normally use coretimer
uint32_t systicks(void) {
	uint32_t m;
	uint16_t f;

	do {
		m=systick_count;
		f=TMR2;
	} while (m ^ systick_count);
	return (m | f);

}

//return timer ticks


//delay millisseconds
void delay(uint32_t ms) {
	uint32_t start_time = ticks();
	ms *= cyclesPerMillisecond();
	while (ticks() - start_time < ms) continue;
}

//delay micros seconds
void delayMicroseconds(uint32_t us) {
	uint32_t start_time = ticks();
	us *= cyclesPerMicrosecond();
	while (ticks() - start_time < us) continue;
}
//end Time

//uart1
//initialize usart: high baudrate (brgh=1), 16-bit baudrate (brg16=1)
//baudrate=Fxtal/(4*(spbrg+1))
//spbrg=(Fxtal/4/baudrate)-1
//tx/rx pins to be assumed in gpio mode
//data bits: 	8
//parity: 		none
//stop bits: 	1
//Xon/Xoff:		none
void uart1Init(unsigned long baud_rate) {
	//enable the pins
#if defined(U1RX2RP)
	U1RX2RP();					//PPS_U1RX_TO_RP(U1RX_RP);
#endif

#if defined(U1TX2RP)
	U1TX2RP();					//PPS_U1TX_TO_RP();
#endif


	//disable md bits
	PMD5bits.U1MD = 0;				//power up the module

	//U2MODEbits register
	//bit 15 UARTEN: UARTx Enable bit(1)
	//1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>
	//0 = UARTx is disabled; all UARTx pins are controlled by PORT latches; UARTx power consumption is	minimal
	U1MODEbits.UARTEN=1;	//enable the uart module
	//bit 14 Unimplemented: Read as `0'
	//bit 13 USIDL: Stop in Idle Mode bit
	//1 = Discontinue module operation when device enters Idle mode
	//0 = Continue module operation in Idle mode
	//bit 12 IREN: IrDAr Encoder and Decoder Enable bit(2)
	//1 = IrDA encoder and decoder enabled
	//0 = IrDA encoder and decoder disabled
	U1MODEbits.IREN = 0;		//disable irda
	U1MODEbits.RTSMD = 0;		//1=in simplex mode. 0 = no flow control
	//bit 11 RTSMD: Mode Selection for UxRTS Pin bit
	//1 = UxRTS pin in Simplex mode
	//0 = UxRTS pin in Flow Control mode
	//bit 10 Unimplemented: Read as `0'
	//bit 9-8 UEN1:UEN0: UARTx Enable bits(3)
	//11 = UxTX, UxRX and BCLKx pins are enabled and used; UxCTS pin controlled by PORT latches
	//10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
	//01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin controlled by PORT latches
	//00 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLKx pins controlled by PORT latches
	U1MODEbits.UEN = 0;								//U1MODEbits.UEN1=0, U2MODEbits.UEN0=0;
	//bit 7 WAKE: Wake-up on Start Bit Detect During Sleep Mode Enable bit
	//1 = UARTx will continue to sample the UxRX pin; interrupt generated on falling edge, bit cleared in hardware on following rising edge
	//0 = No wake-up enabled
	U1MODEbits.WAKE = 0;
	//bit 6 LPBACK: UARTx Loopback Mode Select bit
	//1 = Enable Loopback mode
	//0 = Loopback mode is disabled
	U1MODEbits.LPBACK = 0;
	//bit 5 ABAUD: Auto-Baud Enable bit
	//1 = Enable baud rate measurement on the next character - requires reception of a Sync field (55h); cleared in hardware upon completion
	//0 = Baud rate measurement disabled or completed
	U1MODEbits.ABAUD = 0;
	//bit 4 RXINV: Receive Polarity Inversion bit
	//1 = UxRX Idle state is `0'
	//0 = UxRX Idle state is `1'
	U1MODEbits.RXINV = 0;
	//bit 3 BRGH: High Baud Rate Enable bit
	//1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
	//0 = BRG generates 16 clocks per bit period (16x baud clock, Standard mode)
	U1MODEbits.BRGH = 1;
	//bit 2-1 PDSEL1:PDSEL0: Parity and Data Selection bits
	//11 = 9-bit data, no parity
	//10 = 8-bit data, odd parity
	//01 = 8-bit data, even parity
	//00 = 8-bit data, no parity
	U1MODEbits.PDSEL = 0;							//U1MODEbits.PDSEL1=0, U1MODEbits.PDSEL0=0;
	//bit 0 STSEL: Stop Bit Selection bit
	//1 = Two Stop bits
	//0 = One Stop bit
	U1MODEbits.STSEL=0;
	//Note 1: If UARTEN = 1, the peripheral inputs and outputs must be configured to an available RPn pin. See
	//Section 10.4 "Peripheral Pin Select" for more information.
	//2: This feature is only available for the 16x BRG mode (BRGH = 0).
	//3: Bit availability depends on pin availability.


	//BAUDCON
	U1BRG = F_UART / 4 / baud_rate - 1;				//set lower byte of brg.

	//disable interrupts

	//set up status register
//#if defined(UxTX2RP)				//tx is used
	IFS1bits.U1TXIF = 0;						//clera the flag
	IEC1bits.U1TXIE = 0;						//disable the interrupt

	//bit 15,13 UTXISEL1:UTXISEL0: Transmission Interrupt Mode Selection bits
	//11 = Reserved; do not use
	//10 = Interrupt when a character is transferred to the Transmit Shift Register (TSR) and as a result, the transmit buffer becomes empty
	//01 = Interrupt when the last character is shifted out of the Transmit Shift Register; all transmit operations are completed
	//00 = Interrupt when a character is transferred to the Transmit Shift Register (this implies there is at least one character open in the transmit buffer)
	U1STAbits.UTXISEL = 0;			//U1STAbits.UTXISEL1=0, U1STAbits.UTXISEL0=0;
//#endif
	//bit 14 UTXINV: IrDAr Encoder Transmit Polarity Inversion bit
	//If IREN = 0:
	//1 = UxTX Idle `0'
	//0 = UxTX Idle `1'
	//If IREN = 1:
	//1 = UxTX Idle `1'
	//0 = UxTX Idle `0'
	U1STAbits.UTXINV=0;
	//bit 12 Unimplemented: Read as `0'
	//bit 11 UTXBRK: Transmit Break bit
	//1 = Send Sync Break on next transmission - Start bit, followed by twelve `0' bits, followed by Stop bit;	cleared by hardware upon completion
	//0 = Sync Break transmission disabled or completed
	U1STAbits.UTXBRK=0;
	//bit 10 UTXEN: Transmit Enable bit(1)
	//1 = Transmit enabled, UxTX pin controlled by UARTx
	//0 = Transmit disabled, any pending transmission is aborted and buffer is reset. UxTX pin controlled by the PORT register.
#if defined(U1TX2RP)
	U1STAbits.UTXEN=1;
#else
	U1STAbits.UTXEN=0;
#endif
#if defined(U1RX2RP)
	U1STAbits.URXEN=1;
#else
	U1STAbits.URXEN=0;
#endif
	//bit 9 UTXBF: Transmit Buffer Full Status bit (read-only)
	//1 = Transmit buffer is full
	//0 = Transmit buffer is not full, at least one more character can be written
	//bit 8 TRMT: Transmit Shift Register Empty bit (read-only)
	//1 = Transmit Shift Register is empty and transmit buffer is empty (the last transmission has completed)
	//0 = Transmit Shift Register is not empty, a transmission is in progress or queued
//#if defined(UxRX2RP)
	IFS1bits.U1RXIF = 0;						//clear the flag
	IEC1bits.U1RXIE = 0;						//disable the interrupt

	//bit 7-6 URXISEL1:URXISEL0: Receive Interrupt Mode Selection bits
	//11 = Interrupt is set on RSR transfer, making the receive buffer full (i.e., has 4 data characters)
	//10 = Interrupt is set on RSR transfer, making the receive buffer 3/4 full (i.e., has 3 data characters)
	//0x = Interrupt is set when any character is received and transferred from the RSR to the receive buffer. Receive buffer has one or more characters.
	U1STAbits.URXISEL = 0;						//U1STAbits.URXISEL1 = 0, U1STAbits.URXISEL0 = 0;
//#endif
	//bit 5 ADDEN: Address Character Detect bit (bit 8 of received data = 1)
	//1 = Address Detect mode enabled. If 9-bit mode is not selected, this does not take effect.
	//0 = Address Detect mode disabled
	//bit 4 RIDLE: Receiver Idle bit (read-only)
	//1 = Receiver is Idle
	//0 = Receiver is active
	//bit 3 PERR: Parity Error Status bit (read-only)
	//1 = Parity error has been detected for the current character (character at the top of the receive FIFO)
	//0 = Parity error has not been detected
	//bit 2 FERR: Framing Error Status bit (read-only)
	//1 = Framing error has been detected for the current character (character at the top of the receive FIFO)
	//0 = Framing error has not been detected
	//bit 1 OERR: Receive Buffer Overrun Error Status bit (clear/read-only)
	//1 = Receive buffer has overflowed
	//0 = Receive buffer has not overflowed (clearing a previously set OERR bit (1 ? 0 transition) will reset the receiver buffer and the RSR to the empty state)
	//bit 0 URXDA: Receive Buffer Data Available bit (read-only)
	//1 = Receive buffer has data; at least one more character can be read
	//0 = Receive buffer is empty
	//REGISTER 17-2: U1STAbits: UARTx STATUS AND CONTROL REGISTER (CONTINUED)
	//Note 1: If UARTEN = 1, the peripheral inputs and outputs must be configured to an available RPn pin. See
	//Section 10.4 "Peripheral Pin Select" for more information.

}

void uart1Putch(char ch) {
	//Wait for TXREG Buffer to become available
	//while(!TXIF);			//wait for prior transmission to finish
	//USART_WAIT(U1STAbits.TRMT);		//wait for TRMT to be 0 = transmission done
	while (U1STAbits.UTXBF) continue;	//wait if the tx buffer is full

	//Write data
	U1TXREG=ch;				//load up the tx register

	//USART_WAIT(!U1STAbits.TRMT);
	//while(!TRMT);			//wait for the transmission to finish
	//don't use txif as this is not back-to-back transmission
	//USART_WAIT(!IFS1bits.U1TXIF);		//wait for the falg
	//IFS1bits.U1TXIF = 0;				//reset the flag
}

//put a string
void uart1Puts(char *str) {
	while(*str) {
		uart1Putch(*str++);	//send the ch and advance the pointer
	}
}

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

//put a line termined with ln
void uart1Putline(char *ln) {
	//USARTWriteString(ln);
	uart1Puts(ln);
	//USARTWriteString("\r\n");
	uart1Puts((char *)"\r\n");
}

//get the received char
uint8_t uart1Getch(void) {
	return U1RXREG;		//return it
}

//test if data rx is available
uint16_t uart1Available(void) {
	return U1STAbits.URXDA;
}

//test if uart tx is busy
uint16_t uart1Busy(void) {
	return U1STAbits.UTXBF;
}

//print to uart1
void u1Print(char *str, int32_t dat) {
	char uRAM[40];						//transmission buffer, 40-1 char max

	strcpy(uRAM, str);					//copy to uram
	if (dat < 0) {
		uRAM[6]='-';
		dat = -dat;
	}
	uRAM[19]='0'+(dat % 10);
	dat /= 10;
	uRAM[18]='0'+(dat % 10);
	dat /= 10;
	uRAM[17]='0'+(dat % 10);
	dat /= 10;
	uRAM[16]=',';	//'0'+(dat % 10); dat /= 10;
	uRAM[15]='0'+(dat % 10);
	dat /= 10;
	uRAM[14]='0'+(dat % 10);
	dat /= 10;
	uRAM[13]='0'+(dat % 10);
	dat /= 10;
	uRAM[12]=',';	//'0'+(dat % 10); dat /= 10;
	uRAM[11]='0'+(dat % 10);
	dat /= 10;
	uRAM[10]='0'+(dat % 10);
	dat /= 10;
	uRAM[ 9]='0'+(dat % 10);
	dat /= 10;
	uRAM[ 8]=',';	//'0'+(dat % 10); dat /= 10;
	uRAM[ 7]='0'+(dat % 10);
	dat /= 10;
	uart1Puts(uRAM);	//send a message on uart1
}

//uart2
//initialize usart: high baudrate (brgh=1), 16-bit baudrate (brg16=1)
//baudrate=Fxtal/(4*(spbrg+1))
//spbrg=(Fxtal/4/baudrate)-1
//tx/rx pins to be assumed in gpio mode
//data bits: 	8
//parity: 		none
//stop bits: 	1
//Xon/Xoff:		none
void uart2Init(unsigned long baud_rate) {
	//enable the pins
#if defined(U2RX2RP)
	U2RX2RP();					//PPS_U1RX_TO_RP(U1RX_RP);
#endif

#if defined(U2TX2RP)
	U2TX2RP();					//PPS_U1TX_TO_RP();
#endif


	//disable md bits
	PMD5bits.U2MD = 0;				//power up the module

	//U2MODEbits register
	//bit 15 UARTEN: UARTx Enable bit(1)
	//1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>
	//0 = UARTx is disabled; all UARTx pins are controlled by PORT latches; UARTx power consumption is	minimal
	U2MODEbits.UARTEN=1;	//enable the uart module
	//bit 14 Unimplemented: Read as `0'
	//bit 13 USIDL: Stop in Idle Mode bit
	//1 = Discontinue module operation when device enters Idle mode
	//0 = Continue module operation in Idle mode
	//bit 12 IREN: IrDAr Encoder and Decoder Enable bit(2)
	//1 = IrDA encoder and decoder enabled
	//0 = IrDA encoder and decoder disabled
	U2MODEbits.IREN = 0;		//disable irda
	U2MODEbits.RTSMD = 0;		//1=in simplex mode. 0 = no flow control
	//bit 11 RTSMD: Mode Selection for UxRTS Pin bit
	//1 = UxRTS pin in Simplex mode
	//0 = UxRTS pin in Flow Control mode
	//bit 10 Unimplemented: Read as `0'
	//bit 9-8 UEN1:UEN0: UARTx Enable bits(3)
	//11 = UxTX, UxRX and BCLKx pins are enabled and used; UxCTS pin controlled by PORT latches
	//10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
	//01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin controlled by PORT latches
	//00 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLKx pins controlled by PORT latches
	U2MODEbits.UEN = 0;								//U2MODEbits.UEN1=0, U2MODEbits.UEN0=0;
	//bit 7 WAKE: Wake-up on Start Bit Detect During Sleep Mode Enable bit
	//1 = UARTx will continue to sample the UxRX pin; interrupt generated on falling edge, bit cleared in hardware on following rising edge
	//0 = No wake-up enabled
	U2MODEbits.WAKE = 0;
	//bit 6 LPBACK: UARTx Loopback Mode Select bit
	//1 = Enable Loopback mode
	//0 = Loopback mode is disabled
	U2MODEbits.LPBACK = 0;
	//bit 5 ABAUD: Auto-Baud Enable bit
	//1 = Enable baud rate measurement on the next character - requires reception of a Sync field (55h); cleared in hardware upon completion
	//0 = Baud rate measurement disabled or completed
	U2MODEbits.ABAUD = 0;
	//bit 4 RXINV: Receive Polarity Inversion bit
	//1 = UxRX Idle state is `0'
	//0 = UxRX Idle state is `1'
	U2MODEbits.RXINV = 0;
	//bit 3 BRGH: High Baud Rate Enable bit
	//1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
	//0 = BRG generates 16 clocks per bit period (16x baud clock, Standard mode)
	U2MODEbits.BRGH = 1;
	//bit 2-1 PDSEL1:PDSEL0: Parity and Data Selection bits
	//11 = 9-bit data, no parity
	//10 = 8-bit data, odd parity
	//01 = 8-bit data, even parity
	//00 = 8-bit data, no parity
	U2MODEbits.PDSEL = 0;							//U2MODEbits.PDSEL1=0, U2MODEbits.PDSEL0=0;
	//bit 0 STSEL: Stop Bit Selection bit
	//1 = Two Stop bits
	//0 = One Stop bit
	U2MODEbits.STSEL=0;
	//Note 1: If UARTEN = 1, the peripheral inputs and outputs must be configured to an available RPn pin. See
	//Section 10.4 "Peripheral Pin Select" for more information.
	//2: This feature is only available for the 16x BRG mode (BRGH = 0).
	//3: Bit availability depends on pin availability.


	//BAUDCON
	U2BRG = F_UART / 4 / baud_rate - 1;				//set lower byte of brg

	//disable interrupts
//#if defined(UxTX2RP)
	IFS1bits.U2TXIF = 0;						//clera the flag
	IEC1bits.U2TXIE = 0;						//disable the interrupt

	//set up status register
	//bit 15,13 UTXISEL1:UTXISEL0: Transmission Interrupt Mode Selection bits
	//11 = Reserved; do not use
	//10 = Interrupt when a character is transferred to the Transmit Shift Register (TSR) and as a result, the transmit buffer becomes empty
	//01 = Interrupt when the last character is shifted out of the Transmit Shift Register; all transmit operations are completed
	//00 = Interrupt when a character is transferred to the Transmit Shift Register (this implies there is at least one character open in the transmit buffer)
	U2STAbits.UTXISEL = 0;						//U2STAbits.UTXISEL1=0, U2STAbits.UTXISEL0=0;
//#endif
	//bit 14 UTXINV: IrDAr Encoder Transmit Polarity Inversion bit
	//If IREN = 0:
	//1 = UxTX Idle `0'
	//0 = UxTX Idle `1'
	//If IREN = 1:
	//1 = UxTX Idle `1'
	//0 = UxTX Idle `0'
	U2STAbits.UTXINV=0;
	//bit 12 Unimplemented: Read as `0'
	//bit 11 UTXBRK: Transmit Break bit
	//1 = Send Sync Break on next transmission - Start bit, followed by twelve `0' bits, followed by Stop bit;	cleared by hardware upon completion
	//0 = Sync Break transmission disabled or completed
	U2STAbits.UTXBRK=0;
	//bit 10 UTXEN: Transmit Enable bit(1)
	//1 = Transmit enabled, UxTX pin controlled by UARTx
	//0 = Transmit disabled, any pending transmission is aborted and buffer is reset. UxTX pin controlled by the PORT register.
#if defined(U2TX2RP)
	U2STAbits.UTXEN=1;
#else
	U2STAbits.UTXEN=0;
#endif
#if defined(U2RX2RP)
	U2STAbits.URXEN=1;
#else
	U2STAbits.URXEN=0;
#endif
	//bit 9 UTXBF: Transmit Buffer Full Status bit (read-only)
	//1 = Transmit buffer is full
	//0 = Transmit buffer is not full, at least one more character can be written
	//bit 8 TRMT: Transmit Shift Register Empty bit (read-only)
	//1 = Transmit Shift Register is empty and transmit buffer is empty (the last transmission has completed)
	//0 = Transmit Shift Register is not empty, a transmission is in progress or queued
//#if defined(UxRX2RP)
	IFS1bits.U2RXIF = 0;						//clear the flag
	IEC1bits.U2RXIE = 0;						//disable the interrupt

	//bit 7-6 URXISEL1:URXISEL0: Receive Interrupt Mode Selection bits
	//11 = Interrupt is set on RSR transfer, making the receive buffer full (i.e., has 4 data characters)
	//10 = Interrupt is set on RSR transfer, making the receive buffer 3/4 full (i.e., has 3 data characters)
	//0x = Interrupt is set when any character is received and transferred from the RSR to the receive buffer. Receive buffer has one or more characters.
	U2STAbits.URXISEL = 0;						//U2STAbits.URXISEL1 = 0, U2STAbits.URXISEL0 = 0;
//#endif
	//bit 5 ADDEN: Address Character Detect bit (bit 8 of received data = 1)
	//1 = Address Detect mode enabled. If 9-bit mode is not selected, this does not take effect.
	//0 = Address Detect mode disabled
	//bit 4 RIDLE: Receiver Idle bit (read-only)
	//1 = Receiver is Idle
	//0 = Receiver is active
	//bit 3 PERR: Parity Error Status bit (read-only)
	//1 = Parity error has been detected for the current character (character at the top of the receive FIFO)
	//0 = Parity error has not been detected
	//bit 2 FERR: Framing Error Status bit (read-only)
	//1 = Framing error has been detected for the current character (character at the top of the receive FIFO)
	//0 = Framing error has not been detected
	//bit 1 OERR: Receive Buffer Overrun Error Status bit (clear/read-only)
	//1 = Receive buffer has overflowed
	//0 = Receive buffer has not overflowed (clearing a previously set OERR bit (1 ? 0 transition) will reset the receiver buffer and the RSR to the empty state)
	//bit 0 URXDA: Receive Buffer Data Available bit (read-only)
	//1 = Receive buffer has data; at least one more character can be read
	//0 = Receive buffer is empty
	//REGISTER 17-2: U1STAbits: UARTx STATUS AND CONTROL REGISTER (CONTINUED)
	//Note 1: If UARTEN = 1, the peripheral inputs and outputs must be configured to an available RPn pin. See
	//Section 10.4 "Peripheral Pin Select" for more information.

}

void uart2Putch(char ch) {
	while (U2STAbits.UTXBF) continue;	//wait if the tx buffer is full

	//Write data
	U2TXREG=ch;				//load up the tx register

	//while(!TRMT);			//wait for the transmission to finish
	//don't use txif as this is not back-to-back transmission
	//USART_WAIT(U1STAbits.TRMT);
}

void uart2Puts(char *str) {
	while(*str) {
		uart2Putch(*str++);	//send the ch and advance the pointer
	}
}

/*

Writes a line of text to USART and goes to new line
The new line is Windows style CR/LF pair.

This will work on Hyper Terminal Only NOT on Linux

*/

void uart2Putline(char *ln) {
	//USARTWriteString(ln);
	uart2Puts(ln);
	//USARTWriteString("\r\n");
	uart2Puts((char *)"\r\n");
}

uint8_t uart2Getch(void) {
	//while(!RCIF); RCIF=0;		//Wait for a byte
	//USART_WAIT(U1STAbits.TRMT);		//wait for the prior transmission to end

	return U2RXREG;		//return it
}

//test if data rx is available
uint16_t uart2Available(void) {
	return U2STAbits.URXDA;
}

//test if uart tx is busy
uint16_t uart2Busy(void) {
	return U2STAbits.UTXBF;
}

//print to uart2
void u2Print(char *str, int32_t dat) {
	char uRAM[40];						//transmission buffer, 40-1 char max

	strcpy(uRAM, str);					//copy to uram
	if (dat < 0) {
		uRAM[6]='-';
		dat = -dat;
	}
	uRAM[19]='0'+(dat % 10);
	dat /= 10;
	uRAM[18]='0'+(dat % 10);
	dat /= 10;
	uRAM[17]='0'+(dat % 10);
	dat /= 10;
	uRAM[16]=',';	//'0'+(dat % 10); dat /= 10;
	uRAM[15]='0'+(dat % 10);
	dat /= 10;
	uRAM[14]='0'+(dat % 10);
	dat /= 10;
	uRAM[13]='0'+(dat % 10);
	dat /= 10;
	uRAM[12]=',';	//'0'+(dat % 10); dat /= 10;
	uRAM[11]='0'+(dat % 10);
	dat /= 10;
	uRAM[10]='0'+(dat % 10);
	dat /= 10;
	uRAM[ 9]='0'+(dat % 10);
	dat /= 10;
	uRAM[ 8]=',';	//'0'+(dat % 10); dat /= 10;
	uRAM[ 7]='0'+(dat % 10);
	dat /= 10;
	uart2Puts(uRAM);	//send a message on uart1
}
//end Serial

//tmr1
//global variables
static void (* _tmr1_isrptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//interrupt service routine
void __ISR(_TIMER_1_VECTOR/*, TxIPL*/) _T1Interrupt(void) {
	IFS0bits.T1IF=0;							//clear tmr1 interrupt flag
	_tmr1_isrptr();								//execute user tmr1 isr
}

//initialize the timer1 (16bit)
void tmr1Init(uint8_t ps, uint16_t period) {
	_tmr1_isrptr=empty_handler;					//point to default handler

	PMD4bits.T1MD = 0;							//enable power to tmr
	T1CONbits.TON = 0;							//turn off rtc1
	T1CONbits.TCS = 0;							//use internal clock = Fosc
	//T1CONbits.T32 = 0;						//0->16 bit timer, 1->32bit timer
	T1CONbits.TCKPS=ps & TMR1_PSMASK;			//set prescaler to 1:1
	T1CONbits.TGATE = 0;						//rtc1 gate disabled
	TMR1 = 0;									//reset the timer/counter
	PR1=period-0;								//minimum rtc resolution is 1ms
	IFS0bits.T1IF = 0;							//reset the flag
	IEC0bits.T1IE = 0;							//rtc1 interrupt off
	T1CONbits.TON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr1AttachISR(void (*isrptr)(void)) {
	_tmr1_isrptr=isrptr;						//activate the isr handler
	IPC1bits.T1IP = TMR_IPDEFAULT;
	IPC1bits.T1IS = TMR_ISDEFAULT;
	IFS0bits.T1IF = 0;							//reset the flag
	IEC0bits.T1IE = 1;							//rtc1 interrupt on
}

//tmr2
//global variables
static void (* _tmr2_isrptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//interrupt service routine
void __ISR(_TIMER_2_VECTOR/*, TxIPL*/) _T2Interrupt(void) {
	IFS0bits.T2IF=0;							//clear tmr1 interrupt flag
	systick_count+= 1ul<<16;					//T2 runs in 16 bit mode, 1:1 prescaler
	_tmr2_isrptr();								//execute user tmr2 isr
}

//initialize the timer2 (16bit)
void tmr2Init(uint8_t ps, uint16_t period) {
	_tmr2_isrptr=empty_handler;					//point to default handler
	systick_count=0;							//reset systick

	PMD4bits.T2MD = 0;							//enable power to tmr
	T2CONbits.TON = 0;							//turn off rtc1
	T2CONbits.TCS = 0;							//use internal clock = Fosc
	T2CONbits.T32 = 0;							//0->16 bit timer, 1->32bit timer
	T2CONbits.TCKPS=ps & TMR_PSMASK;			//set prescaler to 1:1
	T2CONbits.TGATE = 0;						//rtc1 gate disabled
	TMR2 = 0;									//reset the timer/counter
	PR2=period-0;								//minimum rtc resolution is 1ms
	IFS0bits.T2IF = 0;							//reset the flag
	IEC0bits.T2IE = 0;							//rtc1 interrupt off
	T2CONbits.TON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr2AttachISR(void (*isrptr)(void)) {
	_tmr2_isrptr=isrptr;						//activate the isr handler
	IPC2bits.T2IP = TMR_IPDEFAULT;
	IPC2bits.T2IS = TMR_ISDEFAULT;
	IFS0bits.T2IF = 0;							//reset the flag
	IEC0bits.T2IE = 1;							//rtc1 interrupt on
}

//tmr3
//global variables
static void (* _tmr3_isrptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//interrupt service routine
void __ISR(_TIMER_3_VECTOR/*, TxIPL*/) _T3Interrupt(void) {
	IFS0bits.T3IF=0;							//clear tmr1 interrupt flag
	_tmr3_isrptr();								//execute user tmr1 isr
}

//initialize the timer3 (16bit)
void tmr3Init(uint8_t ps, uint16_t period) {
	_tmr3_isrptr=empty_handler;					//point to default handler

	PMD4bits.T3MD = 0;							//enable power to tmr
	T3CONbits.TON = 0;							//turn off rtc1
	T3CONbits.TCS = 0;							//use internal clock = Fosc
	//T3CONbits.T32 = 0;						//0->16 bit timer, 1->32bit timer
	T3CONbits.TCKPS=ps & TMR_PSMASK;			//set prescaler to 1:1
	T3CONbits.TGATE = 0;						//rtc1 gate disabled
	TMR3 = 0;									//reset the timer/counter
	PR3=period-0;								//minimum rtc resolution is 1ms
	IFS0bits.T3IF = 0;							//reset the flag
	IEC0bits.T3IE = 0;							//rtc1 interrupt off
	T3CONbits.TON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr3AttachISR(void (*isrptr)(void)) {
	_tmr3_isrptr=isrptr;						//activate the isr handler
	IPC3bits.T3IP = TMR_IPDEFAULT;
	IPC3bits.T3IS = TMR_ISDEFAULT;
	IFS0bits.T3IF = 0;							//reset the flag
	IEC0bits.T3IE = 1;							//rtc1 interrupt on
}

//tmr4
//global variables
static void (* _tmr4_isrptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//interrupt service routine
void __ISR(_TIMER_4_VECTOR/*, TxIPL*/) _T4Interrupt(void) {
	IFS0bits.T4IF=0;							//clear tmr1 interrupt flag
	_tmr4_isrptr();								//execute user tmr1 isr
}

//initialize the timer4 (16bit)
void tmr4Init(uint8_t ps, uint16_t period) {
	_tmr4_isrptr=empty_handler;					//point to default handler

	PMD4bits.T4MD = 0;							//enable power to tmr
	T4CONbits.TON = 0;							//turn off rtc1
	T4CONbits.TCS = 0;							//use internal clock = Fosc
	T4CONbits.T32 = 0;							//0->16 bit timer, 1->32bit timer
	T4CONbits.TCKPS=ps & TMR_PSMASK;			//set prescaler to 1:1
	T4CONbits.TGATE = 0;						//rtc1 gate disabled
	TMR4 = 0;									//reset the timer/counter
	PR4=period-0;								//minimum rtc resolution is 1ms
	IFS0bits.T4IF = 0;							//reset the flag
	IEC0bits.T4IE = 0;							//rtc1 interrupt off
	T4CONbits.TON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr4AttachISR(void (*isrptr)(void)) {
	_tmr4_isrptr=isrptr;						//activate the isr handler
	IPC4bits.T4IP = TMR_IPDEFAULT;
	IPC4bits.T4IS = TMR_ISDEFAULT;
	IFS0bits.T4IF = 0;							//reset the flag
	IEC0bits.T4IE = 1;							//rtc1 interrupt on
}

//tmr5
//global variables
static void (* _tmr5_isrptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//interrupt service routine
void __ISR(_TIMER_5_VECTOR/*, TxIPL*/) _T5Interrupt(void) {
	IFS0bits.T5IF=0;							//clear tmr1 interrupt flag
	_tmr5_isrptr();								//execute user tmr1 isr
}

//initialize the timer5 (16bit)
void tmr5Init(uint8_t ps, uint16_t period) {
	_tmr5_isrptr=empty_handler;					//point to default handler

	PMD4bits.T5MD = 0;							//enable power to tmr
	T5CONbits.TON = 0;							//turn off rtc1
	T5CONbits.TCS = 0;							//use internal clock = Fosc
	//T5CONbits.T32 = 0;						//0->16 bit timer, 1->32bit timer
	T5CONbits.TCKPS=ps & TMR_PSMASK;			//set prescaler to 1:1
	T5CONbits.TGATE = 0;						//rtc1 gate disabled
	TMR5 = 0;									//reset the timer/counter
	PR5=period-0;								//minimum rtc resolution is 1ms
	IFS0bits.T5IF = 0;							//reset the flag
	IEC0bits.T5IE = 0;							//rtc1 interrupt off
	T5CONbits.TON = 1;							//turn on rtc1
}

//activate the isr handler
void tmr5AttachISR(void (*isrptr)(void)) {
	_tmr5_isrptr=isrptr;						//activate the isr handler
	IPC5bits.T5IP = TMR_IPDEFAULT;
	IPC5bits.T5IS = TMR_ISDEFAULT;
	IFS0bits.T5IF = 0;							//reset the flag
	IEC0bits.T5IE = 1;							//rtc1 interrupt on
}

//32-bit timer
//tmr2 as lsw, tmr3 as msw
void tmr23Init(uint8_t ps, uint32_t period) {
	tmr2Init(ps, period);
	tmr3Init(ps, period >> 16);
	T2CONbits.T32 = 1;							//1->32-bit timer

	//write to TMR2/PR2 in 32-bit mode
	TMR2 = 0;
	PR2 = period-0;					//TMR2 = TMR3 = 0;							//reset the counters
}

//read 32-bit timer
uint32_t tmr23Get(void) {
	uint16_t tmr2, tmr3;

	//perform a double read
	do {
		tmr3 = TMR3;
		tmr2 = TMR2;
	} while (tmr3 ^ TMR3);

	return ((uint32_t) tmr3 << 16) | tmr2;
}

#define tmr23AttachISR(isr)		tmr3AttachISR(isr)

//tmr4 as lsw, tmr5 as msw
void tmr45Init(uint8_t ps, uint32_t period) {
	tmr4Init(ps, period);
	tmr5Init(ps, period >> 16);
	T4CONbits.T32 = 1;							//1->32-bit timer

	//write to TMR4/PR4 in 32-bit mode
	TMR4 = 0;
	PR2 = period-0;					//TMR4 = TMR5 = 0;							//reset the counters
}

//read 32-bit timer
uint32_t tmr45Get(void) {
	uint16_t tmr4, tmr5;

	//perform a double read
	do {
		tmr5 = TMR5;
		tmr4 = TMR4;
	} while (tmr5 ^ TMR5);

	return ((uint32_t) tmr5 << 16) | tmr4;
}

#define tmr45AttachISR(isr)		tmr5AttachISR(isr)

//end Timer

//define pwm functions
//time base is Timer2, defined in mcu_init()

//pwm1/oc1
//reset pwm
void pwm1Init(void) {
	//power up the pwm module
	PMD3bits.OC1MD = 0;						//0->turn on the peripheral, 1->turn off the peripheral

#if defined(PWM12RP)
	//assign the output pins
	PWM12RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC1CON = 0x0000;
	//OC1CON2 = 0x0000;
	OC1CONbits.OCM = 0x06;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled
	OC1CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	OC1R = OC1RS = 0;						//reset the duty cycle registers
	OC1CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}


//pwm2/oc2
//reset pwm
void pwm2Init(void) {
	//power up the pwm module
	PMD3bits.OC2MD = 0;						//0->turn on the peripheral, 1->turn off the peripheral

#if defined(PWM22RP)
	//assign the output pins
	PWM22RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC2CON = 0x0000;
	//OC2CON2 = 0x0000;
	OC2CONbits.OCM = 0x06;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled
	OC2CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	OC2R = OC2RS = 0;						//reset the duty cycle registers
	OC2CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}

//pwm3/oc3
//reset pwm
void pwm3Init(void) {
	//power up the pwm module
	PMD3bits.OC3MD = 0;						//0->turn on the peripheral, 1->turn off the peripheral

#if defined(PWM32RP)
	//assign the output pins
	PWM32RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC3CON = 0x0000;
	//OC3CON2 = 0x0000;
	OC3CONbits.OCM = 0x06;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled
	OC3CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	OC3R = OC3RS = 0;						//reset the duty cycle registers
	OC3CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}


//pwm4/oc4
//reset pwm
void pwm4Init(void) {
	//power up the pwm module
	PMD3bits.OC4MD = 0;						//0->turn on the peripheral, 1->turn off the peripheral

#if defined(PWM42RP)
	//assign the output pins
	PWM42RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC4CON = 0x0000;
	//OC4CON2 = 0x0000;
	OC4CONbits.OCM = 0x06;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled
	OC4CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	OC4R = OC4RS = 0;						//reset the duty cycle registers
	OC4CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}


//pwm5/oc5
//reset pwm
void pwm5Init(void) {
	//power up the pwm module
	PMD3bits.OC5MD = 0;						//0->turn on the peripheral, 1->turn off the peripheral

#if defined(PWM52RP)
	//assign the output pins
	PWM52RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC5CON = 0x0000;
	//OC5CON2 = 0x0000;
	OC5CONbits.OCM = 0x06;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled
	OC5CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	OC5R = OC5RS = 0;						//reset the duty cycle registers
	OC5CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}

//end pwm/oc

//adc module
//rest the adc
//automatic sampling (ASAM=1), manual conversion
void adcInit(void) {
	PMD1bits.AD1MD = 0;						//0->enable peripheral, 1->disable peripheral
	//turn off the adc
	AD1CON1bits.ON = 0;				//0->adc off, 1->adc on

	//configure the adc
	AD1CON1 = 0;
	AD1CON2 = 0;
	AD1CON3 = 0;
#if 1
	AD1CON1 = 	(0<<15) |			//0->adc off, 1->adc on
				(0<<14) |			//0->continue adc operation in debug, 1->freeze operation when cpu enters debug
				(0<<13) |			//0->continue operation in idle, 1->stop operation in idle
				(0<< 8) |			//0->16-bit int, 1->16-bit signed, 2->fractional 16-bit, 3->signed fractional 16-bit, 4->32-bit int, 5->signed 32-bit int, 6->fractional 32-bit int, 7->signed fractional 32-bit int
				//7=automatic conversion
				(7<< 5) |			//0->SAMP triggers sampling, 1->int0 transition triggers adc, 2->timer3 period match triggers sampling, 7->internal counter triggers sampling
				(0<< 4) |			//0->normal operation, 1->stop conversions when the first adc interrupt is generated
				//0=manual sampling
				(1<< 2) |			//0->sampling begins when SAMP is set, 1->sampling begins immediately after last conversion (=continuous mode)
				(0<< 1) |			//0->adc sample/hold amplifier is holding, 1->adc sha is sampling. when asam = 0, writing 1 to this bit starts sampling
				(0<< 0) |			//0->adc conversion is not done, 1->adc conversion is done
				0x00;
	AD1CON2 = 	(0<<13) |			//0->AVDD-AVss, 1->Vref+ - AVss, 2->AVdd - Vref-, 3->Vref+ - Vref-, 4..7->AVdd - AVss
				(0<<12) |			//0->disable offset calibration mode, 1->enable offset calibration mode (VinH and VinL are connected to VR-)
				(0<<10) |			//0->do not scan inputs, 1->scan inputs
				(0<< 7) |			//0->ADC is current filling buffer 0-7, user should access data in 8-15; 1->ADC is currently filling buffer 8-15,  user should access data in 0-7
				(0<< 2) |			//0->interrupt at end of each conversion, 1->interrupt at end of every 2nd conversion, 2->interrupt every 3rd conversion, ...
				(0<< 1) |			//0->buffer configured as one 16-word buffer (ADC1BUF15..0), 1->buffer configured as two 8-word buffer (ADC1BUF7..0, ADC1BUF15..8)
				(0<< 0) |			//0->always use mux a input settings, 1->uses muxA for first sample, then alternate between muxA and muxB
				0x00;
	AD1CON3 = 	(0<<15) |			//0->clock derived from peripheral bus clock, 1->adc internal rc clock
				(1<< 8) |			//0->not allowed, 1->1TAD, 2->2TAD, ..., 31->31Tad
				(2<< 0) |			//0->Tad=2*TPB, 1->Tad=4Tpb, ..., Tad=512*TPB
				0x00;
#else
	//alternative approach -> easier to read but longer code
	AD1CON1bits.ON = 0;				//0->disable adc, 1->enable adc
	AD1CON1bits.FORM = 0;			//0->16 bit integer
	AD1CON1bits.SSRC = 7;			//0..7. 7=auto convert
	AD1CON1bits.ASAM = 1;			//1->continuous mode; 0->adc begins when SAMP is set

	AD1CON2bits.VCFG = 0;			//0..3. adc voltage referernce: 0->VAdd-VAss
	AD1CON2bits.ALTS = 0;			//0->always use mux a. 1->use mux a/b alternately

	AD1CON3bits.ADRC = 0;			//0->use pheripheral clock; 1->use adc rc clock
	AD1CON3bits.SAMC = 1;			//auto sample time bits. 0..31
	AD1CON3bits.ADCS = 2;			//auto conversation clock selection. 0..256
#endif
	//AD1CON3 = 0x0002;
	AD1CSSL = 0;					//0->no scaning
	//use muxA always
	//negative input is VR-
	AD1CHSbits.CH0NA = 0;			//0->ch0 negative is VR-, 1->ch0 negative is AN1

	//turn on the adc
	AD1CON1bits.ON = 1;				//0->adc off, 1->adc on
}

//read the adc
uint16_t analogRead(uint16_t ch) {
	//int i;

	AD1CON1bits.SAMP = 0;			// |= (1<<1);			//1->set SAMP to start sampling, 0->stop sampling and start conversion
	ch = ch & 0x0f;					//0..15 is valid input
	//pin lay-out may change
	//below is for pic32mx1xx/2xx/3xx pdip
	switch (ch) {
	case ADC_AN0:
		ANSELA |= (1<<0);
		break;	//AN0 = RA0
	case ADC_AN1:
		ANSELA |= (1<<1);
		break;	//AN1 = RA1
	case ADC_AN2:
		ANSELB |= (1<<0);
		break;	//AN2 = RB0
	case ADC_AN3:
		ANSELB |= (1<<1);
		break;	//AN3 = RB1
	case ADC_AN4:
		ANSELB |= (1<<2);
		break;	//AN4 = RB2
	case ADC_AN5:
		ANSELB |= (1<<3);
		break;	//AN5 = RB3
#if defined(_PORTC)
	case ADC_AN6:
		ANSELC |= (1<<0);
		break;	//AN6 = RC0
	case ADC_AN7:
		ANSELC |= (1<<1);
		break;	//AN7 = RC1
	case ADC_AN8:
		ANSELC |= (1<<2);
		break;	//AN8 = RC2
#endif
	case ADC_AN9:
		ANSELB |= (1<<15);
		break;	//AN9 = RB15
	case ADC_AN10:
		ANSELB |= (1<<14);
		break;	//AN10= RB14
	case ADC_AN11:
		ANSELB |= (1<<13);
		break;	//AN11= RB13
	case ADC_AN12:
		ANSELB |= (1<<12);
		break;	//AN12= RB12
		//case ADC_AN13:ANSELB |= (1<<0); break;	//AN13= CTMUT
		//case ADC_AN14:ANSELB |= (1<<0); break;	//AN14= Internal Vref
		//case ADC_AN15:ANSELB |= (1<<0); break;	//AN15= Open
	}
	AD1CHSbits.CH0SA = ch;			//set Ch0 positive input
	//start the conversion
	//for (i=0; i<10000; i++);
	AD1CON1bits.SAMP = 1;			// |= (1<<1);			//1->set SAMP to start sampling, 0->stop sampling and start conversion
	//clear the DONE bit -> it is persistent in manual mode
	//AD1CON1bits.DONE = 0;
	//wait for the previous conversion to end
	while (AD1CON1bits.DONE == 0) continue;	//0->conversion on going, 1->conversion done
	return ADC1BUF0;
}
//end ADC

//output compare
//oc1 - 16bit
uint16_t _oc1pr=0xffff;							//oc isr period
void (*_oc1_isrptr)(void)=empty_handler;		//tmr1_ptr pointing to empty_handler by default
//OC ISR
void __ISR(_OUTPUT_COMPARE_1_VECTOR/*, _TxIPL*/) _OC1Interrupt(void) {			//for PIC32
	//clear the flag
	IFS0bits.OC1IF = 0;							//clear the flag
	//OC1R += _oc1pr;	OC1R &= 0xffff;				//update to the next match point
	//only care about the 16 bits
	_oc1_isrptr();								//run user handler
}

void oc1Init(uint16_t pr) {
	_oc1_isrptr=empty_handler;
	_oc1pr = pr;								//reset the pr

	//power up the pwm module
	PMD3bits.OC1MD = 0;							//0->turn on the peripheral, 1->turn off the peripheral

	//assign the output pins
#if defined(PWM12RP)
	PWM12RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC1CON = 0x0000;
	//OC5CON2 = 0x0000;
	OC1CONbits.OC32 = 0;					//0->16bit mode, 1->32-bit mode
	OC1CONbits.OCM = 0x03;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled, 0b011->compare toggles ocx
	OC1CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	//OC1R = OC1RS = TMR2 + _oc1pr;			//reset the duty cycle registers

	IFS0bits.OC1IF = 0;						//0->clear the flag;
	IEC0bits.OC1IE = 0;						//0->disable the interrupt, 1->enable the interrupt
	IPC1bits.OC1IP = OC_IPDEFAULT;			//clear the interrupt priority
	IPC1bits.OC1IS = OC_ISDEFAULT;			//clear the interrupt priority

	OC1CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}

//activate user isr
void oc1AttachISR(void (*isrptr)(void)) {
	_oc1_isrptr=isrptr;						//activate the isr handler
	//OC1R = TMR2 + _oc1pr; OC1R &= 0xffff;	//update to the next match point
	IFS0bits.OC1IF = 0;						//0->clear the flag;
	IEC0bits.OC1IE = 1;						//0->disable the interrupt, 1->enable the interrupt
}

//oc2 - 16bit
uint16_t _oc2pr=0xffff;							//oc isr period
void (*_oc2_isrptr)(void)=empty_handler;		//tmr1_ptr pointing to empty_handler by default
//OC ISR
void __ISR(_OUTPUT_COMPARE_2_VECTOR/*, _TxIPL*/) _OC2Interrupt(void) {			//for PIC32
	//clear the flag
	IFS0bits.OC2IF = 0;							//clear the flag
	OC2R += _oc2pr;
	OC2R &= 0xffff;				//update to the next match point
	//only care about the 16 bits
	_oc2_isrptr();								//run user handler
}

void oc2Init(uint16_t pr) {
	_oc2_isrptr=empty_handler;
	_oc2pr = pr;								//reset the pr

	//power up the pwm module
	PMD3bits.OC2MD = 0;							//0->turn on the peripheral, 1->turn off the peripheral

	//assign the output pins
#if defined(PWM22RP)
	PWM22RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC2CON = 0x0000;
	//OC5CON2 = 0x0000;
	OC2CONbits.OC32 = 0;					//0->16bit mode, 1->32-bit mode
	OC2CONbits.OCM = 0x03;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled, 0b011->compare toggles ocx
	OC2CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	//OC2R = OC2RS = TMR2 + _oc2pr;			//reset the duty cycle registers

	IFS0bits.OC2IF = 0;						//0->clear the flag;
	IEC0bits.OC2IE = 0;						//0->disable the interrupt, 1->enable the interrupt
	IPC2bits.OC2IP = OC_IPDEFAULT;			//clear the interrupt priority
	IPC2bits.OC2IS = OC_ISDEFAULT;			//clear the interrupt priority

	OC2CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}

//activate user isr
void oc2AttachISR(void (*isrptr)(void)) {
	_oc2_isrptr=isrptr;						//activate the isr handler
	OC2R = TMR2 + _oc2pr;
	OC2R &= 0xffff;	//update to the next match point
	IFS0bits.OC2IF = 0;						//0->clear the flag;
	IEC0bits.OC2IE = 1;						//0->disable the interrupt, 1->enable the interrupt
}


//oc3 - 16bit
uint16_t _oc3pr=0xffff;							//oc isr period
void (*_oc3_isrptr)(void)=empty_handler;		//tmr1_ptr pointing to empty_handler by default
//OC ISR
void __ISR(_OUTPUT_COMPARE_3_VECTOR/*, _TxIPL*/) _OC3Interrupt(void) {			//for PIC32
	//clear the flag
	IFS0bits.OC3IF = 0;							//clear the flag
	OC3R += _oc3pr;
	OC3R &= 0xffff;				//update to the next match point
	//only care about the 16 bits
	_oc3_isrptr();								//run user handler
}

void oc3Init(uint16_t pr) {
	_oc3_isrptr=empty_handler;
	_oc3pr = pr;								//reset the pr

	//power up the pwm module
	PMD3bits.OC3MD = 0;							//0->turn on the peripheral, 1->turn off the peripheral

	//assign the output pins
#if defined(PWM32RP)
	PWM32RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC3CON = 0x0000;
	//OC5CON2 = 0x0000;
	OC3CONbits.OC32 = 0;					//0->16bit mode, 1->32-bit mode
	OC3CONbits.OCM = 0x03;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled, 0b011->compare toggles ocx
	OC3CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	//OC3R = OC3RS = TMR2 + _oc3pr;			//reset the duty cycle registers

	IFS0bits.OC3IF = 0;						//0->clear the flag;
	IEC0bits.OC3IE = 0;						//0->disable the interrupt, 1->enable the interrupt
	IPC3bits.OC3IP = OC_IPDEFAULT;			//clear the interrupt priority
	IPC3bits.OC3IS = OC_ISDEFAULT;			//clear the interrupt priority

	OC3CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}

//activate user isr
void oc3AttachISR(void (*isrptr)(void)) {
	_oc3_isrptr=isrptr;						//activate the isr handler
	OC3R = TMR2 + _oc3pr;
	OC3R &= 0xffff;	//update to the next match point
	IFS0bits.OC3IF = 0;						//0->clear the flag;
	IEC0bits.OC3IE = 1;						//0->disable the interrupt, 1->enable the interrupt
}

//oc4 - 16bit
uint16_t _oc4pr=0xffff;							//oc isr period
void (*_oc4_isrptr)(void)=empty_handler;		//tmr1_ptr pointing to empty_handler by default
//OC ISR
void __ISR(_OUTPUT_COMPARE_4_VECTOR/*, _TxIPL*/) _OC4Interrupt(void) {			//for PIC32
	//clear the flag
	IFS0bits.OC4IF = 0;							//clear the flag
	OC4R += _oc4pr;
	OC4R &= 0xffff;				//update to the next match point
	//only care about the 16 bits
	_oc4_isrptr();								//run user handler
}

void oc4Init(uint16_t pr) {
	_oc4_isrptr=empty_handler;
	_oc4pr = pr;								//reset the pr

	//power up the pwm module
	PMD3bits.OC4MD = 0;							//0->turn on the peripheral, 1->turn off the peripheral

	//assign the output pins
#if defined(PWM42RP)
	PWM42RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC4CON = 0x0000;
	//OC5CON2 = 0x0000;
	OC4CONbits.OC32 = 0;					//0->16bit mode, 1->32-bit mode
	OC4CONbits.OCM = 0x03;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled, 0b011->compare toggles ocx
	OC4CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	//OC4R = OC4RS = TMR2 + _oc4pr;			//reset the duty cycle registers

	IFS0bits.OC4IF = 0;						//0->clear the flag;
	IEC0bits.OC4IE = 0;						//0->disable the interrupt, 1->enable the interrupt
	IPC4bits.OC4IP = OC_IPDEFAULT;			//clear the interrupt priority
	IPC4bits.OC4IS = OC_ISDEFAULT;			//clear the interrupt priority

	OC4CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}

//activate user isr
void oc4AttachISR(void (*isrptr)(void)) {
	_oc4_isrptr=isrptr;						//activate the isr handler
	OC4R = TMR2 + _oc4pr;
	OC4R &= 0xffff;	//update to the next match point
	IFS0bits.OC4IF = 0;						//0->clear the flag;
	IEC0bits.OC4IE = 1;						//0->disable the interrupt, 1->enable the interrupt
}

//oc5 - 16bit
uint16_t _oc5pr=0xffff;							//oc isr period
void (*_oc5_isrptr)(void)=empty_handler;		//tmr1_ptr pointing to empty_handler by default
//OC ISR
void __ISR(_OUTPUT_COMPARE_5_VECTOR/*, _TxIPL*/) _OC5Interrupt(void) {			//for PIC32
	//clear the flag
	IFS0bits.OC5IF = 0;							//clear the flag
	OC5R += _oc5pr;
	OC5R &= 0xffff;				//update to the next match point
	//only care about the 16 bits
	_oc5_isrptr();								//run user handler
}

void oc5Init(uint16_t pr) {
	_oc5_isrptr=empty_handler;
	_oc5pr = pr;								//reset the pr

	//power up the pwm module
	PMD3bits.OC5MD = 0;							//0->turn on the peripheral, 1->turn off the peripheral

	//assign the output pins
#if defined(PWM52RP)
	PWM52RP();
#endif

	//tris pin presumed to have been set to output

	//OCxCON1 register settings
	//reset the registers
	OC5CON = 0x0000;
	//OC5CON2 = 0x0000;
	OC5CONbits.OC32 = 0;					//0->16bit mode, 1->32-bit mode
	OC5CONbits.OCM = 0x03;					//0b110 -> pwm on OCx, fault pin disabled, 0b111->pwm on OCx, fault pin enabled, 0b011->compare toggles ocx
	OC5CONbits.OCTSEL = 0;					//0->timebase = timer2, 1->timebase = timer3
	//OC5R = OC5RS = TMR2 + _oc5pr;			//reset the duty cycle registers

	IFS0bits.OC5IF = 0;						//0->clear the flag;
	IEC0bits.OC5IE = 0;						//0->disable the interrupt, 1->enable the interrupt
	IPC5bits.OC5IP = OC_IPDEFAULT;			//clear the interrupt priority
	IPC5bits.OC5IS = OC_ISDEFAULT;			//clear the interrupt priority

	OC5CONbits.ON= 1;						//1->turn on oc, 0->turn off oc
}

//activate user isr
void oc5AttachISR(void (*isrptr)(void)) {
	_oc5_isrptr=isrptr;						//activate the isr handler
	OC5R = TMR2 + _oc5pr;
	OC5R &= 0xffff;	//update to the next match point
	IFS0bits.OC5IF = 0;						//0->clear the flag;
	IEC0bits.OC5IE = 1;						//0->disable the interrupt, 1->enable the interrupt
}

//end output compare

//input capture
static void (*_ic1_isrptr)(void)=empty_handler;				//function pointer pointing to empty_handler by default
//volatile uint16_t IC1DAT=0;				//buffer

//input capture ISR
void __ISR(_INPUT_CAPTURE_1_VECTOR/*, _TxIPL*/) _IC1Interrupt(void) {			//for PIC32
	//clear the flag
	//IC1DAT = IC1BUF;					//read the captured value
	IFS0bits.IC1IF = 0;					//clear the flag after the buffer has been read (the interrupt flag is persistent)
	_ic1_isrptr();						//run user handler
}

//reset input capture 1
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic1Init(void) {
	_ic1_isrptr = empty_handler;		//reset user handler

	IC12RP();							//assign pin to IC
	PMD3bits.IC1MD = 0;					//0->enable power to input capture
	IC1CON = 0;
	IC1CON  = 	(0<<15) |				//1->enable the module, 0->disable the module
				(0<<13) |				//0->operates in idle, 1->don't operate in idle
				(1<<9) |				//1-.capture rising edge first (only used for ICM110)
				(0<<8) |				//1->32-bit mode, 0->16-bit mode
				(1<<7) |				//1->timer2 as timebase, 0->timer3 as timebase
				(0<<5) |				//0->interrupt on every capture event, 1->on every second capture event, 2->on every 3rd event, 3->on every 4th event
				(0<<4) |				//0->ICx no overflow, 1->ICx overflow
				(0<<3) |				//0->buffer is empty, 1->buffer is not empty
				(3<<0) |				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
				0x00;
	IC1CONbits.FEDGE = 1;				//1-.capture rising edge first (only used for ICM110)
	IC1CONbits.ICTMR = 1;				//1->timer2 as timebase, 0->timer3 as timebase
	IC1CONbits.ICM   = 3;				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...

	while (IC1CONbits.ICBNE) IC1BUF;	//read the buffer to clear the flag
	IFS0bits.IC1IF   = 0;				//0->clear the flag
	IEC0bits.IC1IE   = 0;				//1->enable the interrupt, 0->disable the interrupt
	//ICxIP   = 1;						//optional
	//enable the input capture
	IC1CONbits.ON = 1;					//1->enable the module, 0->disable the module
	//input capture running now
}

//activate user ptr
void ic1AttachISR(void (*isrptr)(void)) {
	_ic1_isrptr = isrptr;				//install user ptr
	//IC1BUF;								//read the buffer to clear the flag
	IFS0bits.IC1IF   = 0;				//0->clear the flag
	IEC0bits.IC1IE   = 1;				//1->enable the interrupt, 0->disable the interrupt
	IPC1bits.IC1IP = IC_IPDEFAULT;		//interrupt priority.
	IPC1bits.IC1IS = IC_ISDEFAULT;		//interrupt sur-priority
}

//read buffer value
//uint16_t ic1Get(void) {
//	return IC1DAT;
//}

static void (*_ic2_isrptr)(void)=empty_handler;				//function pointer pointing to empty_handler by default
//volatile uint16_t IC2DAT=0;				//buffer

//input capture ISR
void __ISR(_INPUT_CAPTURE_2_VECTOR/*, _TxIPL*/) _IC2Interrupt(void) {			//for PIC32
	//clear the flag
	//IC2DAT = IC2BUF;					//read the captured value
	IFS0bits.IC2IF = 0;					//clear the flag after the buffer has been read (the interrupt flag is persistent)
	_ic2_isrptr();						//run user handler
}

//reset input capture 1
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic2Init(void) {
	_ic2_isrptr = empty_handler;		//reset user handler

	IC22RP();							//assign pin to IC
	PMD3bits.IC2MD = 0;					//0->enable power to input capture
	IC2CON = 0;
	IC2CON  = 	(0<<15) |				//1->enable the module, 0->disable the module
				(0<<13) |				//0->operates in idle, 1->don't operate in idle
				(1<<9) |				//1-.capture rising edge first (only used for ICM110)
				(0<<8) |				//1->32-bit mode, 0->16-bit mode
				(1<<7) |				//1->timer2 as timebase, 0->timer3 as timebase
				(0<<5) |				//0->interrupt on every capture event, 1->on every second capture event, 2->on every 3rd event, 3->on every 4th event
				(0<<4) |				//0->ICx no overflow, 1->ICx overflow
				(0<<3) |				//0->buffer is empty, 1->buffer is not empty
				(3<<0) |				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
				0x00;
	IC2CONbits.FEDGE = 1;				//1-.capture rising edge first (only used for ICM110)
	IC2CONbits.ICTMR = 1;				//1->timer2 as timebase, 0->timer3 as timebase
	IC2CONbits.ICM   = 3;				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...

	while (IC2CONbits.ICBNE) IC2BUF;	//read the buffer to clear the flag
	IFS0bits.IC2IF   = 0;				//0->clear the flag
	IEC0bits.IC2IE   = 0;				//1->enable the interrupt, 0->disable the interrupt
	//ICxIP   = 1;						//optional
	//enable the input capture
	IC2CONbits.ON = 1;					//1->enable the module, 0->disable the module
	//input capture running now
}

//activate user ptr
void ic2AttachISR(void (*isrptr)(void)) {
	_ic2_isrptr = isrptr;				//install user ptr
	//IC2BUF;								//read the buffer to clear the flag
	IFS0bits.IC2IF   = 0;				//0->clear the flag
	IEC0bits.IC2IE   = 1;				//1->enable the interrupt, 0->disable the interrupt
	IPC2bits.IC2IP = IC_IPDEFAULT;		//interrupt priority.
	IPC2bits.IC2IS = IC_ISDEFAULT;		//interrupt sur-priority
}

//read buffer value
//uint16_t ic2Get(void) {
//	return IC2DAT;
//}

static void (*_ic3_isrptr)(void)=empty_handler;				//function pointer pointing to empty_handler by default
//volatile uint16_t IC3DAT=0;				//buffer

//input capture ISR
void __ISR(_INPUT_CAPTURE_3_VECTOR/*, IPL7*/) _IC3Interrupt(void) {			//for PIC32
	//clear the flag
	//IC3DAT = IC3BUF;					//read the captured value
	IFS0bits.IC3IF = 0;					//clear the flag after the buffer has been read (the interrupt flag is persistent)
	_ic3_isrptr();						//run user handler
}

//reset input capture 1
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic3Init(void) {
	_ic3_isrptr = empty_handler;		//reset user handler

	IC32RP();							//assign pin to IC
	PMD3bits.IC3MD = 0;					//0->enable power to input capture
	IC3CON = 0;							//reset ic3con
	IC3CON  = 	(0<<15) |				//1->enable the module, 0->disable the module
				(0<<13) |				//0->operates in idle, 1->don't operate in idle
				(1<<9) |				//1-.capture rising edge first (only used for ICM110)
				(0<<8) |				//1->32-bit mode, 0->16-bit mode
				(1<<7) |				//1->timer2 as timebase, 0->timer3 as timebase
				(0<<5) |				//0->interrupt on every capture event, 1->on every second capture event, 2->on every 3rd event, 3->on every 4th event
				(0<<4) |				//0->ICx no overflow, 1->ICx overflow
				(0<<3) |				//0->buffer is empty, 1->buffer is not empty
				(3<<0) |				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
				0x00;
	IC3CONbits.FEDGE = 1;				//1-.capture rising edge first (only used for ICM110)
	IC3CONbits.ICTMR = 1;				//1->timer2 as timebase, 0->timer3 as timebase
	IC3CONbits.ICM   = 3;				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
	while (IC3CONbits.ICBNE) IC3BUF;	//read the buffer to clear the flag
	IFS0bits.IC3IF   = 0;				//0->clear the flag
	IEC0bits.IC3IE   = 0;				//1->enable the interrupt, 0->disable the interrupt
	//ICxIP   = 1;						//optional
	//enable the input capture
	IC3CONbits.ON = 1;					//1->enable the module, 0->disable the module
	//input capture running now
}

//activate user ptr
void ic3AttachISR(void (*isrptr)(void)) {
	_ic3_isrptr = isrptr;				//install user ptr
	//IC3BUF;								//read the buffer to clear the flag
	IFS0bits.IC3IF   = 0;				//0->clear the flag
	IEC0bits.IC3IE   = 1;				//1->enable the interrupt, 0->disable the interrupt
	IPC3bits.IC3IP = IC_IPDEFAULT;		//interrupt priority.
	IPC3bits.IC3IS = IC_ISDEFAULT;		//interrupt sur-priority
}

//read buffer value
//uint16_t ic3Get(void) {
//	return IC3DAT;
//}

static void (*_ic4_isrptr)(void)=empty_handler;				//function pointer pointing to empty_handler by default
//volatile uint16_t IC4DAT=0;				//buffer

//input capture ISR
void __ISR(_INPUT_CAPTURE_4_VECTOR/*, _TxIPL*/) _IC4Interrupt(void) {			//for PIC32
	//clear the flag
	//IC4DAT = IC4BUF;					//read the captured value
	IFS0bits.IC4IF = 0;					//clear the flag after the buffer has been read (the interrupt flag is persistent)
	_ic4_isrptr();						//run user handler
}

//reset input capture 1
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic4Init(void) {
	_ic4_isrptr = empty_handler;		//reset user handler

	IC42RP();							//assign pin to IC
	PMD3bits.IC4MD = 0;					//0->enable power to input capture
	IC4CON = 0;							//reset ic4con
	IC4CON  = 	(0<<15) |				//1->enable the module, 0->disable the module
				(0<<13) |				//0->operates in idle, 1->don't operate in idle
				(1<<9) |				//1-.capture rising edge first (only used for ICM110)
				(0<<8) |				//1->32-bit mode, 0->16-bit mode
				(1<<7) |				//1->timer2 as timebase, 0->timer3 as timebase
				(0<<5) |				//0->interrupt on every capture event, 1->on every second capture event, 2->on every 3rd event, 3->on every 4th event
				(0<<4) |				//0->ICx no overflow, 1->ICx overflow
				(0<<3) |				//0->buffer is empty, 1->buffer is not empty
				(3<<0) |				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
				0x00;
	IC4CONbits.FEDGE = 1;				//1-.capture rising edge first (only used for ICM110)
	IC4CONbits.ICTMR = 1;				//1->timer2 as timebase, 0->timer3 as timebase
	IC4CONbits.ICM   = 3;				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
	while (IC4CONbits.ICBNE) IC4BUF;	//read the buffer to clear the flag
	IFS0bits.IC4IF   = 0;				//0->clear the flag
	IEC0bits.IC4IE   = 0;				//1->enable the interrupt, 0->disable the interrupt
	//ICxIP   = 1;						//optional
	//enable the input capture
	IC4CONbits.ON = 1;					//1->enable the module, 0->disable the module
	//input capture running now
}

//activate user ptr
void ic4AttachISR(void (*isrptr)(void)) {
	_ic4_isrptr = isrptr;				//install user ptr
	//IC4BUF;								//read the buffer to clear the flag
	IFS0bits.IC4IF   = 0;				//0->clear the flag
	IEC0bits.IC4IE   = 1;				//1->enable the interrupt, 0->disable the interrupt
	IPC4bits.IC4IP = IC_IPDEFAULT;		//interrupt priority.
	IPC4bits.IC4IS = IC_ISDEFAULT;		//interrupt sur-priority
}

//read buffer value
//uint16_t ic4Get(void) {
//	return IC4DAT;
//}

static void (*_ic5_isrptr)(void)=empty_handler;				//function pointer pointing to empty_handler by default
//volatile uint16_t IC5DAT=0;				//buffer

//input capture ISR
void __ISR(_INPUT_CAPTURE_5_VECTOR/*, _TxIPL*/) _IC5Interrupt(void) {			//for PIC32
	//clear the flag
	//IC5DAT = IC5BUF;					//read the captured value
	IFS0bits.IC5IF = 0;					//clear the flag after the buffer has been read (the interrupt flag is persistent)
	_ic5_isrptr();						//run user handler
}

//reset input capture 1
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic5Init(void) {
	_ic5_isrptr = empty_handler;		//reset user handler

	IC52RP();							//assign pin to IC
	PMD3bits.IC5MD = 0;					//0->enable power to input capture
	IC5CON = 0;
	IC5CON  = 	(0<<15) |				//1->enable the module, 0->disable the module
				(0<<13) |				//0->operates in idle, 1->don't operate in idle
				(1<<9) |				//1-.capture rising edge first (only used for ICM110)
				(0<<8) |				//1->32-bit mode, 0->16-bit mode
				(1<<7) |				//1->timer2 as timebase, 0->timer3 as timebase
				(0<<5) |				//0->interrupt on every capture event, 1->on every second capture event, 2->on every 3rd event, 3->on every 4th event
				(0<<4) |				//0->ICx no overflow, 1->ICx overflow
				(0<<3) |				//0->buffer is empty, 1->buffer is not empty
				(3<<0) |				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
				0x00;
	IC5CONbits.FEDGE = 1;				//1-.capture rising edge first (only used for ICM110)
	IC5CONbits.ICTMR = 1;				//1->timer2 as timebase, 0->timer3 as timebase
	IC5CONbits.ICM   = 3;				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
	while (IC5CONbits.ICBNE) IC5BUF;	//read the buffer to clear the flag
	IFS0bits.IC5IF   = 0;				//0->clear the flag
	IEC0bits.IC5IE   = 0;				//1->enable the interrupt, 0->disable the interrupt
	//ICxIP   = 1;						//optional
	//enable the input capture
	IC5CONbits.ON = 1;					//1->enable the module, 0->disable the module
	//input capture running now
}

//activate user ptr
void ic5AttachISR(void (*isrptr)(void)) {
	_ic5_isrptr = isrptr;				//install user ptr
	//IC5BUF;								//read the buffer to clear the flag
	IFS0bits.IC5IF   = 0;				//0->clear the flag
	IEC0bits.IC5IE   = 1;				//1->enable the interrupt, 0->disable the interrupt
	IPC5bits.IC5IP = IC_IPDEFAULT;		//interrupt priority.
	IPC5bits.IC5IS = IC_ISDEFAULT;		//interrupt sur-priority
}

//read buffer value
//uint16_t ic5Get(void) {
//	return IC5DAT;
//}
//end input capture

//extint
//extint0
void (* _int0_isrptr) (void)=empty_handler;

void __ISR(_EXTERNAL_0_VECTOR) _INT0Interrupt(void) {
	IFS0bits.INT0IF = 0;				//clera the flag
	_int0_isrptr();						//run the isr
}

void int0Init(void) {
	//INT02RP();						//map int0_pin - int0 cannot be remapped
	_int0_isrptr = empty_handler;		//initialize int isr ptr
	IFS0bits.INT0IF = 0;				//clear int0 flag
	IEC0bits.INT0IE = 0;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC0bits.INT0IP = 0;				//interrupt priority.
	IPC0bits.INT0IS = 0;				//interrupt sur-priority
	INTCONbits.INT0EP = 0;				//1=triggered on the falling edge. 0 = rising edge
}

void int0AttachISR(void (*isrptr) (void)) {
	_int0_isrptr = isrptr;
	IFS0bits.INT0IF = 0;				//clear int0 flag
	IEC0bits.INT0IE = 1;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC0bits.INT0IP = INT_IPDEFAULT;	//interrupt priority.
	IPC0bits.INT0IS = INT_ISDEFAULT;	//interrupt sur-priority
}

//extint1
void (* _int1_isrptr) (void)=empty_handler;

void __ISR(_EXTERNAL_1_VECTOR) _INT1Interrupt(void) {
	IFS0bits.INT1IF = 0;				//clera the flag
	_int1_isrptr();						//run the isr
}

void int1Init(void) {
	INT12RP();							//map int1_pin
	_int1_isrptr = empty_handler;		//initialize int isr ptr
	IFS0bits.INT1IF = 0;				//clear int0 flag
	IEC0bits.INT1IE = 0;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC1bits.INT1IP = 0;				//interrupt priority.
	IPC1bits.INT1IS = 0;				//interrupt sur-priority
	INTCONbits.INT1EP = 0;				//1=triggered on the falling edge. 0 = rising edge
}

void int1AttachISR(void (*isrptr) (void)) {
	_int1_isrptr = isrptr;
	IFS0bits.INT1IF = 0;				//clear int0 flag
	IEC0bits.INT1IE = 1;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC1bits.INT1IP = INT_IPDEFAULT;	//interrupt priority.
	IPC1bits.INT1IS = INT_ISDEFAULT;	//interrupt sur-priority
}

//extint2
void (* _int2_isrptr) (void)=empty_handler;

void __ISR(_EXTERNAL_2_VECTOR) _INT2Interrupt(void) {
	IFS0bits.INT2IF = 0;				//clera the flag
	_int2_isrptr();						//run the isr
}

void int2Init(void) {
	INT22RP();							//map int1_pin
	_int2_isrptr = empty_handler;		//initialize int isr ptr
	IFS0bits.INT2IF = 0;				//clear int0 flag
	IEC0bits.INT2IE = 0;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC2bits.INT2IP = 0;				//interrupt priority.
	IPC2bits.INT2IS = 0;				//interrupt sur-priority
	INTCONbits.INT2EP = 0;				//1=triggered on the falling edge. 0 = rising edge
}

void int2AttachISR(void (*isrptr) (void)) {
	_int2_isrptr = isrptr;
	IFS0bits.INT2IF = 0;				//clear int0 flag
	IEC0bits.INT2IE = 1;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC2bits.INT2IP = INT_IPDEFAULT;	//interrupt priority.
	IPC2bits.INT2IS = INT_ISDEFAULT;	//interrupt sur-priority
}

//extint3
void (* _int3_isrptr) (void)=empty_handler;

void __ISR(_EXTERNAL_3_VECTOR) _INT3Interrupt(void) {
	IFS0bits.INT3IF = 0;				//clera the flag
	_int3_isrptr();						//run the isr
}

void int3Init(void) {
	INT32RP();							//map int1_pin
	_int3_isrptr = empty_handler;		//initialize int isr ptr
	IFS0bits.INT3IF = 0;				//clear int0 flag
	IEC0bits.INT3IE = 0;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC3bits.INT3IP = 0;				//interrupt priority.
	IPC3bits.INT3IS = 0;				//interrupt sur-priority
	INTCONbits.INT3EP = 0;				//1=triggered on the falling edge. 0 = rising edge
}

void int3AttachISR(void (*isrptr) (void)) {
	_int3_isrptr = isrptr;
	IFS0bits.INT3IF = 0;				//clear int0 flag
	IEC0bits.INT3IE = 1;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC3bits.INT3IP = INT_IPDEFAULT;	//interrupt priority.
	IPC3bits.INT3IS = INT_ISDEFAULT;	//interrupt sur-priority
}

//extint4
void (* _int4_isrptr) (void)=empty_handler;

void __ISR(_EXTERNAL_4_VECTOR) _INT4Interrupt(void) {
	IFS0bits.INT4IF = 0;				//clera the flag
	_int4_isrptr();						//run the isr
}

void int4Init(void) {
	INT42RP();							//map int1_pin
	_int4_isrptr = empty_handler;		//initialize int isr ptr
	IFS0bits.INT4IF = 0;				//clear int0 flag
	IEC0bits.INT4IE = 0;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC4bits.INT4IP = 0;				//interrupt priority.
	IPC4bits.INT4IS = 0;				//interrupt sur-priority
	INTCONbits.INT4EP = 0;				//1=triggered on the falling edge. 0 = rising edge
}

void int4AttachISR(void (*isrptr) (void)) {
	_int4_isrptr = isrptr;
	IFS0bits.INT4IF = 0;				//clear int0 flag
	IEC0bits.INT4IE = 1;				//1->enable int0 interrupt, 0->disable the interrupt
	IPC4bits.INT4IP = INT_IPDEFAULT;	//interrupt priority.
	IPC4bits.INT4IS = INT_ISDEFAULT;	//interrupt sur-priority
}
//end extint

//spi
//rest spi1
#define F_SPI1			100000ul		//spi speed
void spi1Init(uint32_t br) {
	PMD5bits.SPI1MD = 0;				//0->enable the module

	//map the pins
	//map the pins
#if defined(SCK1RP)
	SCK1RP();
#endif
#if defined(SDO1RP)
	SDO1RP();
#endif
#if defined(SDI1RP)
	SDI1RP();
#endif


	//initialize the spi module
	//master mode, PBCLK as clock, 8-bit data, enhanced buffer mode
	SPI1CON = 0; 						//reset the spi module
	SPI1CONbits.MSTEN = 1;				//1->master mode, 0->slave mode
	SPI1CONbits.ENHBUF= 1;				//1->enable enhanced buffer mode, 0->disable enhanced buffer mode
	SPI1BRG = F_PHB / 2 / br;			//set the baudrate generator
	SPI1BUF;							//read the buffer to reset the flag
	IFS1bits.SPI1TXIF = 0;				//0->reset the flag
	IFS1bits.SPI1RXIF = 0;				//0->reset the flag
	IFS1bits.SPI1EIF  = 0;				//0->reset the flag
	IEC1bits.SPI1TXIE = 0;				//0->disable the interrupt, 1->enable the interrupt
	IEC1bits.SPI1RXIE = 0;				//0->disable the interrupt, 1->enable the interrupt
	IEC1bits.SPI1EIE = 0;				//0->disable the interrupt, 1->enable the interrupt
	SPI1CONbits.ON = 1;					//1->enable the module, 0->disable the module
}

//send data via spi
//void spi1Write(uint8_t dat) {
//	while (spi1Busy()) continue;		//tx buffer is full
//	SPI1BUF = dat;						//load the data
//}

//rest spi2
#define F_SPI2			1000000ul		//baud rate
void spi2Init(uint32_t br) {
	PMD5bits.SPI2MD = 0;				//0->enable the module

	//map the pins
#if defined(SCK2RP)
	SCK2RP();
#endif
#if defined(SDO2RP)
	SDO2RP();
#endif
#if defined(SDI2RP)
	SDI2RP();
#endif

	//initialize the spi module
	//master mode, PBCLK as clock, 8-bit data, enhanced buffer mode
	SPI2CON = 0; 						//reset the spi module
	SPI2CONbits.MSTEN = 1;				//1->master mode, 0->slave mode
	SPI2CONbits.ENHBUF= 1;				//1->enable enhanced buffer mode, 0->disable enhanced buffer mode
	SPI2BRG = F_PHB / 2 / br;			//set the baudrate generator
	SPI2BUF;							//read the buffer to reset the flag
	IFS1bits.SPI2TXIF = 0;				//0->reset the flag
	IFS1bits.SPI2RXIF = 0;				//0->reset the flag
	IFS1bits.SPI2EIF  = 0;				//0->reset the flag
	IEC1bits.SPI2TXIE = 0;				//0->disable the interrupt, 1->enable the interrupt
	IEC1bits.SPI2RXIE = 0;				//0->disable the interrupt, 1->enable the interrupt
	IEC1bits.SPI2EIE = 0;				//0->disable the interrupt, 1->enable the interrupt
	SPI2CONbits.ON = 1;					//1->enable the module, 0->disable the module
}

//send data via spi
//void spi2Write(uint8_t dat) {
//	while (spi2Busy()) continue;		//tx buffer is full
//	SPI2BUF = dat;						//load the data
//}
//end spi

//i2c1
//wait for i2c
#define i2c1Wait()		do {while (I2C1CON & 0x1f); while (I2C1STATbits.TRSTAT);} while (0)		//wait for i2c1

//#define F_I2C1			100000ul		//I2C frequency
//initialize the i2c
void i2c1Init(uint32_t bps) {
	PMD5bits.I2C1MD = 0;				//0->enable the module, 1->disable the module
	I2C1CON = 0;						//reset i2c
	I2C1BRG = F_PHB / 2 / bps - 1 - (F_PHB / 2 / 10000000ul);	//TPGOB = 130ns, minimum of 4
	if (I2C1BRG < 0x04) I2C1BRG = 0x04;	//values 0..3 prohibited
	I2C1CONbits.ON = 1;					//1->turn on the i2c, 0->turn off the i2c
}

//send a start condition
void i2c1Start(void) {
	i2c1Wait();
	I2C1CONbits.SEN = 1;
	while (I2C1CONbits.SEN == 1) continue;
}

//send a stop condition
void i2c1Stop(void) {
	i2c1Wait();
	I2C1CONbits.PEN = 1;
	while (I2C1CONbits.PEN == 1) continue;
}

//send a restart condition
void i2c1Restart(void) {
	i2c1Wait();
	I2C1CONbits.RSEN = 1;
	while (I2C1CONbits.RSEN == 1) continue;
}

//send i2c
unsigned char i2c1Write(unsigned char dat) {
	I2C1TRN = dat; 		             			// Send slave address with Read/Write bit cleared
	//while (I2C1STATbits.TRSTAT == 1) continue;	// Wait until transmit buffer is empty
	while (I2C1STATbits.TBF == 1) continue;		// Wait until transmit buffer is empty
	//i2c1Wait();								//wait for i2c bus to idle
	while (I2C1STATbits.ACKSTAT == 1) continue;	//wait for the ack signal
	return I2C1STATbits.ACKSTAT; 				// Wait until ACK is received
}

//read i2c
unsigned char i2c1Read(unsigned char ack) {
	I2C1CONbits.RCEN = 1;               // Receive enable
	while (I2C1CONbits.RCEN == 1) continue;           // Wait until RCEN is cleared (automatic)
	I2C1STATbits.I2COV = 0;				//clear the flag
	I2C1CONbits.ACKDT = ack;			//send ack bits
	I2C1CONbits.ACKEN = 1;
	while (I2C1CONbits.ACKEN == 1) continue;
	return I2C1RCV;						// Retrieve value from I2C1RCV
}

//i2c2
//wait for i2c
#define i2c2Wait()		do {while (I2C2CON & 0x1f); while (I2C2STATbits.TRSTAT);} while (0)		//wait for i2c2

//#define F_I2C2			100000ul		//I2C frequency
//initialize the i2c
void i2c2Init(uint32_t bps) {
	PMD5bits.I2C2MD = 0;				//0->enable the module, 1->disable the module
	I2C2CON = 0;						//reset i2c
	I2C2BRG = F_PHB / 2 / bps - 1 - (F_PHB / 2 / 10000000ul);	//TPGOB = 130ns
	if (I2C2BRG < 0x04) I2C2BRG = 0x04;	//values 0x00-0x03 prohibited
	I2C2CONbits.ON = 1;					//1->turn on the i2c, 0->turn off the i2c
}

//send a start condition
void i2c2Start(void) {
	i2c2Wait();
	I2C2CONbits.SEN = 1;
	while (I2C2CONbits.SEN == 1) continue;
}

//send a stop condition
void i2c2Stop(void) {
	i2c2Wait();
	I2C2CONbits.PEN = 1;
	while (I2C2CONbits.PEN == 1) continue;
}

//send a restart condition
void i2c2Restart(void) {
	i2c2Wait();
	I2C2CONbits.RSEN = 1;
	while (I2C2CONbits.RSEN == 1) continue;
}

//send i2c
unsigned char i2c2Write(unsigned char dat) {
	I2C2TRN = dat; 		             			// Send slave address with Read/Write bit cleared
	//while (I2C2STATbits.TRSTAT == 1) continue;	// Wait until transmit buffer is empty
	while (I2C2STATbits.TBF == 1) continue;		// Wait until transmit buffer is empty
	//i2c2Wait();								//wait for i2c bus to idle
	while (I2C2STATbits.ACKSTAT == 1) continue;	//wait for the ack signal
	return I2C2STATbits.ACKSTAT; 				// Wait until ACK is received
}

//read i2c
unsigned char i2c2Read(unsigned char ack) {
	I2C2CONbits.RCEN = 1;               // Receive enable
	while (I2C2CONbits.RCEN == 1) continue;           // Wait until RCEN is cleared (automatic)
	I2C2STATbits.I2COV = 0;				//clear the flag
	I2C2CONbits.ACKDT = ack;			//send ack bits
	I2C2CONbits.ACKEN = 1;
	while (I2C2CONbits.ACKEN == 1) continue;
	return I2C2RCV;						// Retrieve value from I2C1RCV
}

//end i2c

//rtcc
//allows write to rtc registers
#define RTCC_WREN()				do {di(); SYSKEY=0xaa996655ul; SYSKEY=0x556699aaul; RTCCONbits.RTCWREN = 1; ei();} while (RTCCONbits.RTCWREN == 0)
//do not allow any write to rtc registers - assumes the nvmkey sequence has been sent
#define RTCC_WRDIS()			do {RTCCONbits.RTCWREN = 0;} while (RTCCONbits.RTCWREN == 1)

//bcd to dec conversion
#define BCD2DEC(bcd)			((((bcd) & 0xf0)>>4)*10+((bcd) & 0x0f))	//convert bcd to int
#define DEC2BCD(dec)			((((dec) / 10)<<4) +((dec) % 10))		//convert int to bcd

//global variables
//struct tm _rtcc;								//rtcc time

//initialize the RTCC
//Need to turn on FSOSCEN fuse bit
void RTCCInit(void) {
	PMD6bits.RTCCMD = 0;						//enable power to RTCC
	RTCC_WREN();								//allows write to rtc registers
	//RTCCON |= 1<<15;							//start the RTCC
	RTCCONbits.ON=1;
	RTCC_WRDIS();
}

//set time
uint32_t RTCCSetTime(uint32_t val) {
	RTCC_WREN();								//enable RTCC write
	di();
	while ((RTCCON & (1<<2)) != 0) continue;	//wait for RTCSYNC=0
	RTCTIME = val;
	ei();
	RTCC_WRDIS();								//disable RTCC write
	return val;
}

//set date
uint32_t RTCCSetDate(uint32_t val) {
	RTCC_WREN();								//enable RTCC write
	di();
	while ((RTCCON & (1<<2)) != 0) continue;	//wait for RTCSYNC=0
	RTCDATE = val;
	ei();
	RTCC_WRDIS();								//disable RTCC write
	return val;
}

//write the calibration
//offset: 0x200..0x1ff. -512..511
uint32_t RTCCSetCal(uint32_t offset) {
	RTCC_WREN();								//allows write to rtc registers
	RTCCON &=~0x03ff0000ul;						//clear the cal registers
	//RTCCON |= (offset & 0x3ff) << 16;			//load the offset
	RTCCONbits.CAL=offset;
	RTCC_WRDIS();								//disable any write to rfc
	return offset;
}

//read the calibration
//int32_t RTCCGetCal(void) {
//	signed char tmp;
//	//RTCC_WREN();								//allows write to rtc registers
//	tmp = RTCCON & 0x03ff0000ul;				//clear the cal registers
//	//RTCC_WRDIS();								//disable any write to rfc
//	return tmp >> 16;
//}

//end RTCC

//cnint
void (* _cna_isrptr) (void)=empty_handler;
void (* _cnb_isrptr) (void)=empty_handler;
#if defined(_PORTC)
void (* _cnc_isrptr) (void)=empty_handler;
#endif

void __ISR(_CHANGE_NOTICE_VECTOR) _CNInterrupt(void) {
	if (IFS1bits.CNAIF) {
		PORTA;    //run the isr
		IFS1bits.CNAIF = 0;
		_cna_isrptr();
	}
	if (IFS1bits.CNBIF) {
		PORTB;    //run the isr
		IFS1bits.CNBIF = 0;
		_cnb_isrptr();
	}
#if defined(_PORTC)
	if (IFS1bits.CNCIF) {
		PORTC;    //run the isr
		IFS1bits.CNCIF = 0;
		_cnc_isrptr();
	}
#endif
}

//initialize change notification
void cnaInit(uint16_t pins) {
	//enable power - always enabled
	GPIOA->CNCON &=~(1<<15);					//0->disable cn, 1->enable cn
	GPIOA->CNPUSET = pins;						//1->enable pull-up
	GPIOA->CNPDCLR = pins;						//0->disable pull-down
	IFS1bits.CNAIF= 0;							//0->clear the flag
	IEC1bits.CNAIE= 0;							//0->disable the interrupt
	IPC0bits.INT0IP = 0;						//interrupt priority.
	IPC0bits.INT0IS = 0;						//interrupt sur-priority
	IPC8bits.CNIP = 0;							//interrupt priority.
	IPC8bits.CNIS = 0;							//interrupt sur-priority
	GPIOA->CNENSET = pins;						//1->enable cn, 0->disable cn
	GPIOA->CNCON |= (1<<15);					//0->disable cn, 1->enable cn
}

//attach user isr
void cnaAttachISR(void (*isrptr) (void)) {
	_cna_isrptr = isrptr;						//point the isrptr
	IFS1bits.CNAIF= 0;							//0->clear the flag
	IEC1bits.CNAIE= 1;							//0->disable the interrupt
	IPC8bits.CNIP = CN_IPDEFAULT;				//interrupt priority.
	IPC8bits.CNIS = CN_ISDEFAULT;				//interrupt sur-priority
}

//initialize change notification
void cnbInit(uint16_t pins) {
	//enable power - always enabled
	GPIOB->CNCON &=~(1<<15);					//0->disable cn, 1->enable cn
	GPIOB->CNPUSET = pins;						//1->enable pull-up
	GPIOB->CNPDCLR = pins;						//0->disable pull-down
	IFS1bits.CNBIF= 0;							//0->clear the flag
	IEC1bits.CNBIE= 0;							//0->disable the interrupt
	IPC8bits.CNIP = 0;							//interrupt priority.
	IPC8bits.CNIS = 0;							//interrupt sur-priority
	GPIOB->CNENSET = pins;						//1->enable cn, 0->disable cn
	GPIOB->CNCON |= (1<<15);					//0->disable cn, 1->enable cn
}

//attach user isr
void cnbAttachISR(void (*isrptr) (void)) {
	_cnb_isrptr = isrptr;						//point the isrptr
	IFS1bits.CNBIF= 0;							//0->clear the flag
	IEC1bits.CNBIE= 1;							//0->disable the interrupt
	IPC8bits.CNIP = CN_IPDEFAULT;				//interrupt priority.
	IPC8bits.CNIS = CN_ISDEFAULT;				//interrupt sur-priority
}

#if defined(_PORTC)
//initialize change notification
void cncInit(uint16_t pins) {
	//enable power - always enabled
	GPIOC->CNCON &=~(1<<15);					//0->disable cn, 1->enable cn
	GPIOC->CNPUSET = pins;						//1->enable pull-up
	GPIOC->CNPDCLR = pins;						//0->disable pull-down
	IFS1bits.CNCIF= 0;							//0->clear the flag
	IEC1bits.CNCIE= 0;							//0->disable the interrupt
	IPC8bits.CNIP = 0;							//interrupt priority.
	IPC8bits.CNIS = 0;							//interrupt sur-priority
	GPIOC->CNENSET = pins;						//1->enable cn, 0->disable cn
	GPIOC->CNCON |= (1<<15);					//0->disable cn, 1->enable cn
}

//attach user isr
void cncAttachISR(void (*isrptr) (void)) {
	_cnc_isrptr = isrptr;						//point the isrptr
	IFS1bits.CNCIF= 0;							//0->clear the flag
	IEC1bits.CNCIE= 1;							//0->disable the interrupt
	IPC8bits.CNIP = CN_IPDEFAULT;				//interrupt priority.
	IPC8bits.CNIS = CN_ISDEFAULT;				//interrupt sur-priority
}
#endif 	//_PORTC
//end cnint

//comparator voltage reference
//initialize the comparator
void CVrefInit(void) {
	//enable the module
	PMD1bits.CVRMD = 0;							//0->enable the module

	CVRCON = 0;									//reset the module
	CVRCONbits.CVRR = 0;						//1->0..0.67CVrsrc, in 24 steps; 0->0.25..0.75CVrsrc in 32 steps
	//output disabled
	CVRCONbits.ON = 1;							//1->enable the module
}



//end comparator voltage reference

//comparator
//initialize comparator
void CM1Init(void) {
	PMD2bits.CMP1MD = 0;						//0->enable the module

	CM1CON = 0;									//reset the comparator
	//output disabled
	//non-inverting input on CxINDA
	//    inverting input on CxINDB
	CM1CONbits.ON = 1;							//1->enable the module
}

//comparator
//initialize comparator
void CM2Init(void) {
	PMD2bits.CMP2MD = 0;						//0->enable the module

	CM2CON = 0;									//reset the comparator
	//output disabled
	//non-inverting input on CxINDA
	//    inverting input on CxINDB
	CM2CONbits.ON = 1;							//1->enable the module
}

//comparator
//initialize comparator
void CM3Init(void) {
	PMD2bits.CMP3MD = 0;						//0->enable the module

	CM3CON = 0;									//reset the comparator
	//output disabled
	//non-inverting input on CxINDA
	//    inverting input on CxINDB
	CM3CONbits.ON = 1;							//1->enable the module
}

//end comparator
