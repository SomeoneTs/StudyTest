#ifndef _LED_H_
#define _LED_H_

#include "sys.h"

#define LED0 PIout(9)
#define LED1 PIout(10)
#define LED2 PGout(7)
#define LED3 PFout(10)



void led_init(void);
#endif
