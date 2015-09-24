/**
 * @file    effect_simplecolor.c
 * @brief
 *
 * @addtogroup effects
 * @{
 */

#include "effect_randomcolor.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/


/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief
 *
 */

msg_t EffectRandomUpdate(int16_t x, int16_t y, systime_t time, void* effectcfg, void* effectdata, const struct Color* color, struct effect_t* next)
{
    (void) color;
    struct EffectRandomColorCfg* cfg = (struct EffectRandomColorCfg*) effectcfg;
    struct EffectRandomColorData* data = (struct EffectRandomColorData*) effectdata;

    systime_t diff = time - data->lastupdate;
    if (diff >= cfg->interval)
    {
        data->lastupdate += cfg->interval;
        ColorRandom(&data->color);
    }

    struct Color out;
    ColorCopy(&data->color, &out);

    return EffectUpdate(next, x, y, time, &out);
}

void EffectRandomReset(int16_t x, int16_t y, systime_t time, void* effectcfg, void* effectdata, struct effect_t* next)
{
    (void)effectcfg;
    struct EffectRandomColorData* data = (struct EffectRandomColorData*) effectdata;
    data->lastupdate = time;

    ColorRandom(&data->color);

    EffectReset(next, x, y, time);
}

/** @} */
