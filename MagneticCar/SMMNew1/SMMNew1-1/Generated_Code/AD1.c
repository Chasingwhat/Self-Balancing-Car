/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : AD1.c
**     Project     : SMMNew1
**     Processor   : 56F8013VFAE
**     Component   : ADC
**     Version     : Component 01.690, Driver 02.07, CPU db: 2.87.098
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2016-03-02, 22:04, # CodeGen: 0
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : AD1
**          A/D converter                                  : ADC
**          Sharing                                        : Disabled
**          Interrupt service/event                        : Disabled
**          A/D channels                                   : 6
**            Channel0                                     : 
**              A/D channel (pin)                          : ANA0_GPIOC0
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel1                                     : 
**              A/D channel (pin)                          : ANA1_GPIOC1
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel2                                     : 
**              A/D channel (pin)                          : ANA2_VREFH_GPIOC2
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel3                                     : 
**              A/D channel (pin)                          : ANB0_GPIOC4
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel4                                     : 
**              A/D channel (pin)                          : ANB1_GPIOC5
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**            Channel5                                     : 
**              A/D channel (pin)                          : ANB2_VREFL_GPIOC6
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**          Queue                                          : Enabled
**            Mode                                         : Sequential
**            A/D samples                                  : 8
**              Sample0                                    : Enabled
**                Channel                                  : 0
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample1                                    : Enabled
**                Channel                                  : 1
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample2                                    : Enabled
**                Channel                                  : 2
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample3                                    : Enabled
**                Channel                                  : 3
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample4                                    : Enabled
**                Channel                                  : 4
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample5                                    : Enabled
**                Channel                                  : 5
**                High limit                               : 32760
**                Low limit                                : 0
**                Offset                                   : 0
**                Zero crossing                            : Disabled
**              Sample6                                    : Disabled
**              Sample7                                    : Disabled
**          A/D resolution                                 : 12 bits
**          Conversion time                                : 4.781 ?s
**          Trigger configuration wizard                   : Click to run configurator >
**          Internal trigger                               : Disabled
**          Volt. ref. recovery time                       : 100
**          Power up delay                                 : 13
**          Power savings mode                             : Disabled
**          Auto standby                                   : Disabled
**          Volt. ref. source                              : controlled by this component for both converter
**            High volt. ref. source                       : internal
**            Low volt. ref. source                        : internal
**          Number of conversions                          : 1
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          High input limit                               : 1
**          Low input limit                                : 0
**          Get value directly                             : yes
**          Wait for result                                : yes
**     Contents    :
**         Measure    - byte AD1_Measure(bool WaitForResult);
**         GetValue16 - byte AD1_GetValue16(word *Values);
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
** @file AD1.c
** @version 02.07
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup AD1_module AD1 module documentation
**  @{
*/         

/* MODULE AD1. */

#include "AD1.h"

#define IDLE            0U             /* IDLE state           */
#define MEASURE         1U             /* MEASURE state        */
#define CONTINUOUS      2U             /* CONTINUOUS state     */
#define SINGLE          3U             /* SINGLE state         */

static bool OutFlg;                    /* Measurement finish flag */
/*lint -esym(765,AD1_ModeFlg) Disable MISRA rule (8.10) checking for symbols (AD1_ModeFlg). */
volatile byte AD1_ModeFlg;             /* Current state of device */

/*
** ===================================================================
**     Method      :  MainMeasure (component ADC)
**
**     Description :
**         The method performs A/D conversion(s). The method is called 
**         automatically as a part of measure methods or the HWEnDi 
**         method.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void MainMeasure(void)
{
  if (getRegBit(ADC_ADSTAT,EOSI0)) {   /* Is a scan cycle completed? */
    setRegBits(ADC_ADSTAT,2048);       /* Clear EOSI flag */
    OutFlg = TRUE;                     /* Measured values are available */
    AD1_ModeFlg = IDLE;                /* Set the component to the idle mode */
  }
}

/*
** ===================================================================
**     Method      :  HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of 
**         Enable, Disable and Init methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (AD1_ModeFlg) {                   /* Launch measurement? */
    OutFlg = FALSE;                    /* Measured values are available */
    setRegBits(ADC_ADSTAT,2048);       /* Clear flag */
    clrRegBit(ADC_ADCR1,STOP0);        /* Normal operation mode */
    setRegBit(ADC_ADCR1,START0);       /* Launching of conversion */
  }
  else {
    setRegBit(ADC_ADCR1,STOP0);        /* Stop command issued */
  }
}

/*
** ===================================================================
**     Method      :  AD1_Measure (component ADC)
*/
/*!
**     @brief
**         This method performs one measurement on all channels that
**         are set in the component inspector. (Note: If the [number of
**         conversions] is more than one the conversion of A/D channels
**         is performed specified number of times.)
**     @param
**         WaitForResult   - Wait for a result of a
**                           conversion. If [interrupt service] is
**                           disabled, A/D peripheral doesn't support
**                           measuring all channels at once or Autoscan
**                           mode property isn't enabled and at the same
**                           time the [number of channels] is greater
**                           than 1, then the WaitForResult parameter is
**                           ignored and the method waits for each
**                           result every time. If the [interrupt
**                           service] is disabled and a [number of
**                           conversions] is greater than 1, the
**                           parameter is ignored and the method also
**                           waits for each result every time.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
*/
/* ===================================================================*/
byte AD1_Measure(bool WaitForResult)
{
  if (AD1_ModeFlg != IDLE) {           /* Is the device in running mode? */
    return ERR_BUSY;                   /* If yes then error */
  }
  AD1_ModeFlg = MEASURE;               /* Set state of device to the measure mode */
  HWEnDi();                            /* Enable the device */
  if (WaitForResult) {                 /* Is WaitForResult TRUE? */
    while (AD1_ModeFlg == MEASURE) {   /* Calling MainMeasure while IDLE state occured */
      MainMeasure();                   /* A/D converter handler */
    }
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_GetValue16 (component ADC)
*/
/*!
**     @brief
**         This method returns the last measured values of all channels.
**         Compared with [GetValue] method this method returns more
**         accurate result if the [number of conversions] is greater
**         than 1 and [AD resolution] is less than 16 bits. In addition,
**         the user code dependency on [AD resolution] is eliminated.
**     @param
**         Values          - Pointer to the array that contains
**                           the measured data.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
*/
/* ===================================================================*/
byte AD1_GetValue16(word *Values)
{
  if (AD1_ModeFlg != IDLE) {           /* Is the device in any measure mode? */
    MainMeasure();                     /* Call A/D converter handler */
  }
  if (!OutFlg) {                       /* Is measured value(s) available? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  *Values++ = (getReg(ADC_ADRSLT0) + 0U) << 1U; /* Store value from result register of device to user buffer */
  *Values++ = (getReg(ADC_ADRSLT1) + 0U) << 1U; /* Store value from result register of device to user buffer */
  *Values++ = (getReg(ADC_ADRSLT2) + 0U) << 1U; /* Store value from result register of device to user buffer */
  *Values++ = (getReg(ADC_ADRSLT3) + 0U) << 1U; /* Store value from result register of device to user buffer */
  *Values++ = (getReg(ADC_ADRSLT4) + 0U) << 1U; /* Store value from result register of device to user buffer */
  *Values = (getReg(ADC_ADRSLT5) + 0U) << 1U; /* Store value from result register of device to user buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AD1_Init(void)
{
  volatile word i;

  OutFlg = FALSE;                      /* No measured value */
  AD1_ModeFlg = IDLE;                  /* Device isn't running */
  /* ADC_ADCR1: ??=0,STOP0=1,START0=0,SYNC0=0,EOSIE0=0,ZCIE=0,LLMTIE=0,HLMTIE=0,CHNCFG=0,??=0,SMODE=0 */
  setReg(ADC_ADCR1,16384U);            /* Set control register 1 */
  /* ADC_CAL: SEL_VREFH=0,SEL_VREFLO=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  setReg(ADC_CAL,0U);                  /* Set calibration register */
  /* ADC_ADPOWER: ASB=0,??=0,??=0,PSTS2=0,PSTS1=0,PSTS0=0,PUDELAY=13,APD=0,PD2=0,PD1=0,PD0=0 */
  setReg(ADC_ADPOWER,208U);            /* Enable device */
  /* ADC_ADOFS0: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg(ADC_ADOFS0,0U);               /* Set offset reg. 0 */
  /* ADC_ADOFS1: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg(ADC_ADOFS1,0U);               /* Set offset reg. 1 */
  /* ADC_ADOFS2: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg(ADC_ADOFS2,0U);               /* Set offset reg. 2 */
  /* ADC_ADOFS3: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg(ADC_ADOFS3,0U);               /* Set offset reg. 3 */
  /* ADC_ADOFS4: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg(ADC_ADOFS4,0U);               /* Set offset reg. 4 */
  /* ADC_ADOFS5: ??=0,OFFSET=0,??=0,??=0,??=0 */
  setReg(ADC_ADOFS5,0U);               /* Set offset reg. 5 */
  /* ADC_ADHLMT0: ??=0,HLMT=4095,??=0,??=0,??=0 */
  setReg(ADC_ADHLMT0,32760U);          /* Set high limit reg. 0 */
  /* ADC_ADHLMT1: ??=0,HLMT=4095,??=0,??=0,??=0 */
  setReg(ADC_ADHLMT1,32760U);          /* Set high limit reg. 1 */
  /* ADC_ADHLMT2: ??=0,HLMT=4095,??=0,??=0,??=0 */
  setReg(ADC_ADHLMT2,32760U);          /* Set high limit reg. 2 */
  /* ADC_ADHLMT3: ??=0,HLMT=4095,??=0,??=0,??=0 */
  setReg(ADC_ADHLMT3,32760U);          /* Set high limit reg. 3 */
  /* ADC_ADHLMT4: ??=0,HLMT=4095,??=0,??=0,??=0 */
  setReg(ADC_ADHLMT4,32760U);          /* Set high limit reg. 4 */
  /* ADC_ADHLMT5: ??=0,HLMT=4095,??=0,??=0,??=0 */
  setReg(ADC_ADHLMT5,32760U);          /* Set high limit reg. 5 */
  /* ADC_ADLLMT0: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg(ADC_ADLLMT0,0U);              /* Set low limit reg. 0 */
  /* ADC_ADLLMT1: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg(ADC_ADLLMT1,0U);              /* Set low limit reg. 1 */
  /* ADC_ADLLMT2: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg(ADC_ADLLMT2,0U);              /* Set low limit reg. 2 */
  /* ADC_ADLLMT3: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg(ADC_ADLLMT3,0U);              /* Set low limit reg. 3 */
  /* ADC_ADLLMT4: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg(ADC_ADLLMT4,0U);              /* Set low limit reg. 4 */
  /* ADC_ADLLMT5: ??=0,LLMT=0,??=0,??=0,??=0 */
  setReg(ADC_ADLLMT5,0U);              /* Set low limit reg. 5 */
  /* ADC_ADZCSTAT: ??=1,??=1,??=1,??=1,??=1,??=1,??=1,??=1,ZCS7=1,ZCS6=1,ZCS5=1,ZCS4=1,ZCS3=1,ZCS2=1,ZCS1=1,ZCS0=1 */
  setReg(ADC_ADZCSTAT,65535);          /* Clear zero crossing status flags */
  /* ADC_ADLSTAT: HLS7=1,HLS6=1,HLS5=1,HLS4=1,HLS3=1,HLS2=1,HLS1=1,HLS0=1,LLS7=1,LLS6=1,LLS5=1,LLS4=1,LLS3=1,LLS2=1,LLS1=1,LLS0=1 */
  setReg(ADC_ADLSTAT,65535);           /* Clear high and low limit status */
  /* ADC_ADSTAT: CIP0=0,CIP1=0,??=0,EOSI1=0,EOSI0=1,ZCI=0,LLMTI=0,HLMTI=0,RDY7=0,RDY6=0,RDY5=0,RDY4=0,RDY3=0,RDY2=0,RDY1=0,RDY0=0 */
  setReg(ADC_ADSTAT,2048);             /* Clear EOSI flag */
  /* ADC_ADSDIS: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DS7=1,DS6=1,DS5=0,DS4=0,DS3=0,DS2=0,DS1=0,DS0=0 */
  setReg(ADC_ADSDIS,192U);             /* Enable/disable of samples */
  /* ADC_ADLST1: ??=0,SAMPLE3=4,??=0,SAMPLE2=2,??=0,SAMPLE1=1,??=0,SAMPLE0=0 */
  setReg(ADC_ADLST1,16912U);           /* Set ADC channel list reg. */
  /* ADC_ADLST2: ??=0,SAMPLE7=0,??=0,SAMPLE6=0,??=0,SAMPLE5=6,??=0,SAMPLE4=5 */
  setReg(ADC_ADLST2,101U);             /* Set ADC channel list reg. */
  /* ADC_ADZCC: ZCE7=0,ZCE6=0,ZCE5=0,ZCE4=0,ZCE3=0,ZCE2=0,ZCE1=0,ZCE0=0 */
  setReg(ADC_ADZCC,0U);                /* Set zero crossing control reg. */
  /* ADC_ADCR2: ??=0,STOP1=0,START1=0,SYNC1=0,EOSIE1=0,??=0,??=0,??=0,??=0,??=0,SIMULT=1,DIV=8 */
  setReg(ADC_ADCR2,40U);               /* Set prescaler */
  for (i=0U;i<100U;i++) {}             /* Recovery time of voltage reference */
  while (ADC_ADPOWER&(ADC_ADPOWER_PSTS_MASK)) {} /* Wait for device powered up */
}

/* END AD1. */

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
