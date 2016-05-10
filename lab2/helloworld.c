#include "xgpio.h"          // Provides access to PB GPIO driver.
#include <stdio.h>          // xil_printf and so forth.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.

// This is invoked in response to a timer interrupt.
// It does 2 things: 1) debounce switches, and 2) advances the time.
int onesec;
int tenms;
int halfsec;
int buttonValid;
int currentButtonState;
int hours;
int mins;
int seconds;
int holding;

void pb_interrupt_handler();


void timer_interrupt_handler() {
	onesec++;
	tenms++;
	halfsec++;
	if(currentButtonState == 0x00) {
		holding = 0;
		if(onesec == 100) {
			onesec = 0;
			seconds++;
			if(seconds == 60) {
				mins++;
				seconds = 0;
			}
			if(mins == 60) {
				hours++;
		 		mins = 0;
			}
			if(hours == 24) {
				hours = 0;
			}
			xil_printf("        \r", hours, mins, seconds);
			xil_printf("%02d:%02d:%02d\r", hours, mins, seconds);
		}
	}
	else {
		if(onesec == 100) {
			onesec = 0;
			holding = 1;
			halfsec = 0;
		}
	}

	if(holding == 1){
		if(halfsec == 50) {
			halfsec = 0;
			pb_interrupt_handler();

		}
	}
	if(tenms == 20) {
		tenms = 0;
		buttonValid = 1;
	}
}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
  // Clear the GPIO interrupt.
  XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now.
  currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
  // You need to do something here.
  if(buttonValid == 1) {
	  //xil_printf("button_interrupt\n\r");
	  //xil_printf("%x\n\r", currentButtonState);
	  onesec = 0;
	  buttonValid = 0;
	  if(currentButtonState == 0x18) {		// hour++
		  //xil_printf("hour++\n\r");
		  if(hours == 23) {
			  hours = 0;
		  }
		  else {
			  hours++;
		  }

	  }
	  if(currentButtonState == 0x0c) {		// hour--
		 // xil_printf("hour--\n\r");
		  if(hours == 0) {
			  hours = 23;
		  }
		  else {
			  hours--;
		  }
	  }
	  if(currentButtonState == 0x11) {		//min++
		  //xil_printf("min++\n\r");
		  if(mins == 59) {
			  mins = 0;
			  hours++;
		  }
		  else {
			  mins++;
		  }
	  }
	  if(currentButtonState == 0x05) {		//min--
		 // xil_printf("min--\n\r");
		  if(mins == 0) {
			  mins = 59;
			  if(hours != 0)
				  hours--;
		  }
		  else {
			  mins--;
		  }
	  }
	  if(currentButtonState == 0x12) {		//sec++
		 // xil_printf("sec++\n\r");
		  if(seconds == 59) {
			  seconds = 0;
			  mins++;
		  }
		  else {
			  seconds++;
		  }
	  }
	  if(currentButtonState == 0x06) {		//sec--
		 // xil_printf("sec--\n\r");
		  if(seconds == 0) {
			  seconds = 59;
			  if(mins != 0)
				  mins--;
		  }
		  else {
			  seconds--;
		  }
	  }
		xil_printf("        \r", hours, mins, seconds);
		xil_printf("%02d:%02d:%02d\r", hours, mins, seconds);
  }
  XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);            // Ack the PB interrupt.
  XGpio_InterruptGlobalEnable(&gpPB);                 // Re-enable PB interrupts.
}

// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
	// Check the FIT interrupt first.
	if (intc_status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
		pb_interrupt_handler();
	}
	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
		timer_interrupt_handler();
	}
	// Check the push buttons.

}

int main (void) {
    init_platform();
    // Initialize the GPIO peripherals.
    int success;
    print("hello world\n\r");
    success = XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
    // Set the push button peripheral to be inputs.
    XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
    // Enable the global GPIO interrupt for push buttons.
    XGpio_InterruptGlobalEnable(&gpPB);
    // Enable all interrupts in the push button peripheral.
    XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

    microblaze_register_handler(interrupt_handler_dispatcher, NULL);
    XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
    		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
    XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
    microblaze_enable_interrupts();

    while(1);  // Program never ends.

    cleanup_platform();

    return 0;
}
