#ifndef _KEY_H_
#define _KEY_H_

#include "sys.h"

#define key_up     PIin(11)
#define key_down   PEin(5)
#define key_left   PEin(3)
#define key_right  PIin(7)

void key_init(void);

#endif

