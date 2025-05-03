#include "led.h"

void LED_Init(void)
{

    GPIO_setPadConfig(LED1, GPIO_PIN_TYPE_STD);  // Push-pull output or floating input
    GPIO_setDirectionMode(LED1, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(LED2, GPIO_PIN_TYPE_STD);  // Push-pull output or floating input
    GPIO_setDirectionMode(LED2, GPIO_DIR_MODE_OUT);
    //³õÊ¼×´Ì¬À­¸ß
    LED1_ON;
    LED2_ON;
}
