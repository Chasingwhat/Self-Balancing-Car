/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : COUNTER2.H
**     Project   : SMMNew1
**     Processor : 56F8013VFAE
**     Component : EventCntr16
**     Version   : Component 02.135, Driver 02.04, CPU db: 2.87.097
**     Compiler  : Metrowerks DSP C Compiler
**     Date/Time : 2012-2-3, 17:35
**     Abstract  :
**         This bean "EventCntr16" implements an 16-bit event counter.
**         It counts the external events (specified edges of the external
**         signal). It uses a hardware timer counter.
**         The counter width is extended or taperred to 16 bits.
**     Settings  :
**         Timer name                  : TMR1 [16-bit]
**
**         Counting mode               : Simple counter
**
**         Used input pin              : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       22            |  GPIOA4_PWM4_FAULT1_T2
**             ----------------------------------------------------
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**         Counter register            : TMR1_CNTR [61461]
**         Mode register               : TMR1_CTRL [61462]
**         Run register                : TMR1_CTRL [61462]
**     Contents  :
**         Reset        - byte COUNTER2_Reset(void);
**         GetNumEvents - byte COUNTER2_GetNumEvents(word *Value);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __COUNTER2
#define __COUNTER2

/* MODULE COUNTER2. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


byte COUNTER2_Reset(void);
/*
** ===================================================================
**     Method      :  COUNTER2_Reset (component EventCntr16)
**
**     Description :
**         This method resets the external event counter (sets it to
**         zero).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
** ===================================================================
*/

byte COUNTER2_GetNumEvents(word *Value);
/*
** ===================================================================
**     Method      :  COUNTER2_GetNumEvents (component EventCntr16)
**
**     Description :
**         This method returns the number of the external events.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Value           - A pointer to the returned number of
**                           the external events
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_OVERFLOW - Timer overflow
** ===================================================================
*/

void COUNTER2_Interrupt(void);
/*
** ===================================================================
**     Method      :  COUNTER2_Interrupt (component EventCntr16)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void COUNTER2_Init(void);
/*
** ===================================================================
**     Method      :  COUNTER2_Init (component EventCntr16)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END COUNTER2. */

#endif /* ifndef __COUNTER2 */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.00 [04.35]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
