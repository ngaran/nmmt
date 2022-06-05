#ifndef _SAVE_H
#define _SAVE_H

#include "type.h"

#define NMR_SAVE_SIZE 49156
#define NMM_SAVE_SIZE 57348

typedef struct
{
	u32  shot,
	     zero1,
	     percent,
	     hp,
	     score;
	u32  zero2,
	     zero3;
	u32  score_trophy;
	u32  zero4;
	u32  beat;
	u32  zero5;
}
galagar_save_t;

typedef struct
{
	u32 crc;
	galagar_save_t galagar_saves[11];
	u8  junk2[48668];
}
nmr_save_t;

typedef struct
{
	nmr_save_t nmr_save;
	u8         junk2[8192];
}
nmm_save_t;

typedef enum
{
	ERR = 0,
	NMR = 1,
	NMM = 2
}
SAVE_TYPE;

SAVE_TYPE id_save(char *filename);
nmm_save_t *update_save(nmm_save_t *save);
nmm_save_t *swap_save(nmm_save_t *save);
int write_save(nmm_save_t *save);

#endif

