/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : COUNTER1.h
**     Project     : SMMNew1
**     Processor   : 56F8013VFAE
**     Component   : EventCntr16
**     Version     : Component 02.141, Driver 02.07, CPU db: 2.87.098
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2016-03-02, 22:04, # CodeGen: 0
**     Abstract    :
**         This component "EventCntr16" implements an 16-bit event counter.
**         It counts the external events (specified edges of the external
**         signal). It uses a hardware timer counter.
**         The counter width is extended or taperred to 16 bits.
**     Settings    :
**         Timer name                  : TMR0 [16-bit]
**
**         Counting mode               : Simple counter
**
**         Used input pin              : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       19            |  GPIOB4_T0_CLKO
**             ----------------------------------------------------
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**         Counter register            : TMR0_CNTR [61445]
**         Mode register               : TMR0_CTRL [61446]
**         Run register                : TMR0_CTRL [61446]
**     Contents    :
**         Reset        - byte COUNTER1_Reset(void);
**         GetNumEvents - byte COUNTER1_GetNumEvents(word *Value);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file COUNTER1.h
** @version 02.07
** @brief
**         This component "EventCntr16" implements an 16-bit event counter.
**         It counts the external events (specified edges of the external
**         signal). It uses a hardware timer counter.
**         The counter width is extended or taperred to 16 bits.
*/         
/*!
**  @addtogroup COUNTER1_module COUNTER1 module documentation
**  @{
*/         

#ifndef __COUNTER1
#define __COUNTER1

/* MODULE COUNTER1. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "Cpu.h"


byte COUNTER1_Reset(void);
/*
** ===================================================================
**     Method      :  COUNTER1_Reset (component EventCntr16)
**     Description :
**         This method resets the external event counter (sets it to
**         zero).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
** ===================================================================
*/

byte COUNTER1_GetNumEvents(word *Value);
/*
** ===================================================================
**     Method      :  COUNTER1_GetNumEvents (component EventCntr16)
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

void COUNTER1_Interrupt(void);
/*
** ===================================================================
**     Method      :  COUNTER1_Interrupt (component EventCntr16)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void COUNTER1_Init(void);
/*
** ===================================================================
**     Method      :  COUNTER1_Init (component EventCntr16)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END COUNTER1. */

#endif /* ifndef __COUNTER1 */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/