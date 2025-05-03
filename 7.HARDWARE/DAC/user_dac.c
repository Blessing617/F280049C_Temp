#include "user_dac.h"

void DAC_init(void)
{
    // Set DAC reference voltage.
    DAC_setReferenceVoltage(DACA_BASE, DAC_REF_ADC_VREFHI);
    // Set DAC gain mode.
    DAC_setGainMode(DACA_BASE, DAC_GAIN_TWO);
    // Set DAC load mode.
    DAC_setLoadMode(DACA_BASE, DAC_LOAD_SYSCLK);
    // Enable the DAC output
    DAC_enableOutput(DACA_BASE);
    // Set the DAC shadow output
    DAC_setShadowValue(DACA_BASE, 0U);
    // Delay for buffered DAC to power up.
}

void DAC_Set_Value(float V)
{
    DAC_setShadowValue(DACA_BASE, V/3.3f*4095);
}



