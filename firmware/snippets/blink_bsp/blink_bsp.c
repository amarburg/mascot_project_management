//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  On the TX1 Companion board, LEDs are on P2.4 and P2.5
//  J. Stevenson
//  Texas Instruments, Inc
//  July 2013
//  Built with Code Composer Studio v5
//***************************************************************************************

#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    P2DIR |= (BIT4 | BIT5);                   // Set P1.0 to output direction
		P2OUT |= BIT4;

    for(;;) {
        volatile unsigned int i;            // volatile to prevent optimization

        P2OUT ^= (BIT4 | BIT5);                      // Toggle P1.0 using exclusive-OR

        i = 50000;                          // SW Delay
        do i--;
        while(i != 0);
    }

    return 0;
}
