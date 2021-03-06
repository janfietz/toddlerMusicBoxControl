/**
 * @file    board_drivers.c
 * @brief
 *
 * @{
 */

#include "board_drivers.h"
#include "ledconf.h"

#include "ch.h"
#include "hal.h"

#include "ws281x.h"
#include "usbcfg.h"
#include "mfrc522.h"

extern ws2811Driver ws2811;
extern SerialUSBDriver SDU1;
extern MFRC522Driver RFID1;

static ws2811Config ws2811_cfg =
{
    LEDCOUNT,
    LED1,
    0b00000010,
    (uint32_t)(&(GPIOA->BSRR.H.set)),
    (uint32_t)(&(GPIOA->BSRR.H.clear)),
    WS2812_BIT_PWM_WIDTH,
    WS2812_ZERO_PWM_WIDTH,
    WS2812_ONE_PWM_WIDTH,
    {
        168000000 / 2 / WS2812_BIT_PWM_WIDTH,
        (LEDCOUNT * 24) + 20,
        NULL,
        {
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_DISABLED, NULL },
            { PWM_OUTPUT_DISABLED, NULL },
            { PWM_OUTPUT_DISABLED, NULL }
        },
        TIM_CR2_MMS_2, /* master mode selection */
        0,
    },
    &PWMD2,
    {
        168000000 / 2,
        WS2812_BIT_PWM_WIDTH,
        NULL,
        {
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL }
        },
        0,
        TIM_DIER_UDE | TIM_DIER_CC3DE | TIM_DIER_CC1DE,
    },
    &PWMD1,
    STM32_DMA2_STREAM5,
    STM32_DMA2_STREAM1,
    STM32_DMA2_STREAM6,
};

static MFRC522Config RFID1_cfg =
{

};

/*
 * SPI1 configuration structure.
 * Speed 5.25MHz, CPHA=1, CPOL=1, 8bits frames, MSb transmitted first.
 * The slave select line is the pin GPIOA_LRCK on the port GPIOA.
 */
static const SPIConfig SPI1cfg = {
  NULL,
  /* HW dependent part.*/
  GPIOC,
  GPIOC_PIN5,
  SPI_CR1_BR_0 | SPI_CR1_BR_1
};

void BoardDriverInit(void)
{
    sduObjectInit(&SDU1);
    ws2811ObjectInit(&ws2811);
    MFRC522ObjectInit(&RFID1);
}

void BoardDriverStart(void)
{
    spiStart(&SPID1, &SPI1cfg);
    MFRC522Start(&RFID1, &RFID1_cfg);

    ws2811Start(&ws2811, &ws2811_cfg);
    palSetGroupMode(GPIOA, 0b00000010, 0, PAL_MODE_OUTPUT_PUSHPULL|PAL_STM32_OSPEED_HIGHEST|PAL_STM32_PUDR_FLOATING);

    /*
     * Initializes a serial-over-USB CDC driver.
     */
    sduStart(&SDU1, &serusbcfg);

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);
}

void BoardDriverShutdown(void)
{
    sduStop(&SDU1);
    ws2811Stop(&ws2811);

    MFRC522Stop(&RFID1);
    spiStop(&SPID1);
}

/** @} */
