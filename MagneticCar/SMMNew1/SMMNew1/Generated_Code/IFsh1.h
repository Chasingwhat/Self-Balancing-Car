/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : IFsh1.h
**     Project     : SMMNew1-1
**     Processor   : 56F8013VFAE
**     Component   : IntFLASH
**     Version     : Component 02.409, Driver 02.09, CPU db: 2.87.098
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2016-03-01, 17:44, # CodeGen: 0
**     Abstract    :
**         This component "IntFLASH" implements an access to internal FLASH.
**         The component support reading/writing data into FLASH, erasing of
**         selected sector.
**         The component supports events if the write interrupt is supported.
**         The component supports following modes of write operations:
**           - Write - writing without any test.
**           - Destructive write - sector is erased if necessary.
**           - Safe write - user event is invoked to save and resore data
**                          from the current sector.
**         The component requires on-chip FLASH memory (not used/allocated by
**         other components).
**     Settings    :
**         FLASH memory type                 : Program FLASH
**         Memory size                       : 8192 words
**         Sector size                       : 256 words
**         Interrupt service                 : Disabled
**         Write method                      : Safe write (with save & erase)
**         Buffer Type                       : Implemented by the component
**         Wait in RAM                       : yes
**     Contents    :
**         Busy         - bool IFsh1_Busy(byte Block);
**         SetByteFlash - byte IFsh1_SetByteFlash(IFsh1_TAddress Addr, byte Data);
**         SetWordFlash - byte IFsh1_SetWordFlash(IFsh1_TAddress Addr, word Data);
**         DataPtr2Addr - IFsh1_TAddress IFsh1_DataPtr2Addr(void* Addr);
**         FuncPtr2Addr - IFsh1_TAddress IFsh1_FuncPtr2Addr(void(*Addr)());
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
** @file IFsh1.h
** @version 02.09
** @brief
**         This component "IntFLASH" implements an access to internal FLASH.
**         The component support reading/writing data into FLASH, erasing of
**         selected sector.
**         The component supports events if the write interrupt is supported.
**         The component supports following modes of write operations:
**           - Write - writing without any test.
**           - Destructive write - sector is erased if necessary.
**           - Safe write - user event is invoked to save and resore data
**                          from the current sector.
**         The component requires on-chip FLASH memory (not used/allocated by
**         other components).
*/         
/*!
**  @addtogroup IFsh1_module IFsh1 module documentation
**  @{
*/         

#ifndef __IFsh1
#define __IFsh1

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* Include inherited beans */
#include "Cpu.h"

/* MODULE IFsh1. */

/* FLASH memory size and location in 16-bit words */
#define PROG_FLASH_START 0
#define PROG_FLASH_END   8191
#define PROG_FLASH_SECTOR_SIZE 256u

/* Common data fields for all IntFLASH bean's modules */
#ifndef CommonFlashData
#define CommonFlashData

/* Flash user mode commands */
#define ERASE_VERIFY 0x05
#define PROGRAM      0x20
#define PAGE_ERASE   0x40
#define MASS_ERASE   0x41

#endif /* Common data fields for all IntFLASH bean's modules */

#ifndef __BWUserType_IFsh1_TAddress
#define __BWUserType_IFsh1_TAddress
   typedef dword IFsh1_TAddress;       /* Bean type for address to the FLASH.*/
#endif
#ifndef __BWUserType_IFsh1_TDataAddress
#define __BWUserType_IFsh1_TDataAddress
  typedef dword IFsh1_TDataAddress;    /* Bean type for data address. */
#endif


/* Adressess for wait in RAM routine copy */
extern _LWIR_ROM_addr_low;
extern _LWIR_ROM_addr_high;
extern _LWIR_RAM_addr_low;
extern _LWIR_RAM_addr_high;
extern _LWIR_size;

/*
Test the Command complete flag.
*/
#define IFsh1_Busy(Block) ((bool)( \
  (getRegBit(FMUSTAT,CCIF)) ? \
    (FALSE) : \
    (TRUE)))
/*
** ===================================================================
**     Method      :  IFsh1_Busy (component IntFLASH)
*/
/*!
**     @brief
**         This method returns the status of the FLASH device. The
**         method may be required and called from another component
**         methods - in this case it cannot be disabled.
**     @param
**         Block           - Number of Flash block. Not used for
**                           Freescale 56800, HCS08, HCS12X and
**                           ColdFireV1 derivates - any value may be
**                           passed.
**     @return
**                         - [true]/[false] - FLASH is busy/ready
*/
/* ===================================================================*/

byte IFsh1_SetByteFlash(IFsh1_TAddress Addr,byte Data);
/*
** ===================================================================
**     Method      :  IFsh1_SetByteFlash (component IntFLASH)
*/
/*!
**     @brief
**         Writes a byte to an address in FLASH. The operation of this
**         method depends on the "Write method" property and state of
**         the flash. Please see more details on general info page of
**         the help.
**     @param
**         Addr            - Address to FLASH.
**                           [ Version specific information for 56800
**                           derivatives ] 
**                           The value of this parameter is address of a
**                           byte location in the selected memory space
**                           (address of a 16 bit word location
**                           multiplied by 2 and the least significant
**                           bit determines even or odd byte). The
**                           memory space depends on the selected flash
**                           memory device.
**     @param
**         Data            - Data to write.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_NOTAVAIL - Desired program/erase
**                           operation is not available 
**                           - ERR_RANGE - Address is out of range 
**                           - ERR_VALUE - Read value is not equal to
**                           written value 
**                           - ERR_SPEED - This device does not work in
**                           the active speed mode 
**                           - ERR_BUSY - Device is busy 
**                           - ERR_PROTECT - Flash is write protect
*/
/* ===================================================================*/

byte IFsh1_SetWordFlash(IFsh1_TAddress Addr,word Data);
/*
** ===================================================================
**     Method      :  IFsh1_SetWordFlash (component IntFLASH)
*/
/*!
**     @brief
**         Writes a word to an address in FLASH. The operation of this
**         method depends on the "Write method" property and state of
**         the flash. Please see more details on general info page of
**         the help.
**     @param
**         Addr            - Address to FLASH.
**                           [ Version specific information for 56800
**                           derivatives ] 
**                           The value of this parameter is address of a
**                           16 bit word location in the selected memory
**                           space. The memory space depends on the
**                           selected flash memory device.
**     @param
**         Data            - Data to write.
**     @return
**                         - Error code, possible codes: 
**                           - ERR_OK - OK 
**                           - ERR_NOTAVAIL - Desired program/erase
**                           operation is not available 
**                           - ERR_RANGE - Address is out of range 
**                           - ERR_VALUE - Read value is not equal to
**                           written value 
**                           - ERR_SPEED - This device does not work in
**                           the active speed mode 
**                           - ERR_BUSY - Device is busy 
**                           - ERR_PROTECT - Flash is write protect
*/
/* ===================================================================*/

void IFsh1_Init(void);
/*
** ===================================================================
**     Method      :  IFsh1_Init (component IntFLASH)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#define IFsh1_DataPtr2Addr(DataPtr) ((IFsh1_TAddress)(DataPtr))
/*
** ===================================================================
**     Method      :  IFsh1_DataPtr2Addr (component IntFLASH)
*/
/*!
**     @brief
**         This method converts data pointer to format of a component's
**         method address parameter. Generally a data pointer format is
**         different from format of a method Addr parameter.
**     @param
**         Addr            - Data pointer.
**     @return
**                         - Address in the format used in the component
**                           methods.
**                           [ Version specific information for 56800
**                           derivatives ] 
**                           The return value is address of a byte
**                           location of the object the input parameter
**                           - pointer pointing at (address of a 16 bit
**                           word location multiplied by 2 and the least
**                           significant bit determines even or odd byte).
*/
/* ===================================================================*/

#define IFsh1_FuncPtr2Addr(FuncPtr) ((IFsh1_TAddress)(FuncPtr))
/*
** ===================================================================
**     Method      :  IFsh1_FuncPtr2Addr (component IntFLASH)
*/
/*!
**     @brief
**         This method converts function pointer to format of a
**         component's method address parameter. Generally a function
**         pointer format is different from format of a method Addr
**         parameter.
**     @param
**         Addr            - Function pointer.
**     @return
**                         - Address in the format used in the component
**                           methods.
**                           [ Version specific information for 56800
**                           derivatives ] 
**                           The return value is address of a byte
**                           location of the object the input parameter
**                           - pointer pointing at (address of a 16 bit
**                           word location multiplied by 2 and the least
**                           significant bit determines even or odd byte).
*/
/* ===================================================================*/

/* END IFsh1. */

#endif /* ifndef __IFsh1 */
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