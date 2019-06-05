#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned int counter; /*Variable contadorea */

void interrupt VectorNumber_Vrti rti_isr (void){
	SRTISC_RTIACK = 1;
	
	if(counter == 10){
		counter = 0;
	}
	
	PTBD = counter;
	counter++;
}


void main(void) {
	/*Configuración incial*/
  SOPT1 = 0x53; /*Desactivamos el watchdog */                                       
  	  
  SOPT2 = 0x00; /* SOPT2:
    	+	COPCLKS= 0
    	+	IICPS  = 0
    	+ 	ACIC   = 0
   */
  
  	/*Configuración del Puerto B*/
	PTBD = 0; /*Inicializamos el puerto B*/
	
	PTBDD_PTBDD0 = 1;		/* Configuración de los puertos B0-B3 Como salidas*/
	PTBDD_PTBDD1 = 1;
	PTBDD_PTBDD2 = 1;
	PTBDD_PTBDD3 = 1;
	
	PTBPE_PTBPE0 = 1;		/* Configuración de los puertos B0-B3 con pull-up activado*/ 
	PTBPE_PTBPE1 = 1;
	PTBPE_PTBPE2 = 1;
	PTBPE_PTBPE3 = 1;
	
	SRTISC = 0x57; /* Configuración de System RTI Status n Control
		+.
		+	RTIACK = 1 
		+	RTICLKS= 0
		+	RTIE   = 1
		+	RTIS   = 111
	*/
		
	EnableInterrupts;

  for(;;) {
    __RESET_WATCHDOG();	
  } /* loop forever */
  
}
