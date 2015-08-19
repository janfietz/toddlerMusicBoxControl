
/**
 * @file    effect_simplecolor.h
 * @brief
 *
 * @addtogroup effects
 * @{
 */

#ifndef _EFFECT_SIMPLECOLOR_H_
#define _EFFECT_SIMPLECOLOR_H_

#include "ch.h"
#include "color.h"
/*===========================================================================*/
/* Effect constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Effect pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/
struct EffectSimpleColorCfg
{
    struct Color color;
};

struct EffectSimpleColorData
{
    bool reset;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
    msg_t EffectSimpleUpdate(uint16_t led, systime_t time, void* effectcfg, void* effectdata, const struct Color* in, struct Color* out);
    void EffectSimpleReset(uint16_t led, systime_t time, void* effectcfg, void* effectdata);
#ifdef __cplusplus
}
#endif

#endif /* _EFFECT_SIMPLECOLOR_H_ */


/** @} */