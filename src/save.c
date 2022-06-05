#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <byteswap.h>
#include "save.h"

SAVE_TYPE id_save(char *filename)
{
	FILE *fp = fopen(filename, "rb");
	if(!fp) return EBADF;

	fseek(fp, 0 , SEEK_END);
	size_t size = ftell(fp);

	fclose(fp);

	switch(size)
	{
		case NMR_SAVE_SIZE:
			return NMR;
			break;
		case NMM_SAVE_SIZE:
			return NMM;
			break;
		default:
			return ERR;
	}
}

nmm_save_t *update_save(nmm_save_t *save)
{
	nmm_save_t *save_tmp = malloc(sizeof(nmm_save_t)-4);

	memcpy(save_tmp, (u8*)save+4, sizeof(nmm_save_t)-4);

	u32 crc = crc32(0L, Z_NULL, 0);

	for(int i = 0; i < sizeof(nmm_save_t)-4; i++)
	{
		// printf("%c", *(u8*)save_tmp+i);
		crc = crc32(crc, (u8*)save_tmp+i, 1);
	}
	
	save->nmr_save.crc = crc;

	return save;
}

nmm_save_t *swap_save(nmm_save_t *save)
{
	save->nmr_save.crc = __bswap_32(save->nmr_save.crc);

	for(int i = 0; i < 11; i++)
	{
		save->nmr_save.galagar_saves[i].shot = __bswap_32(save->nmr_save.galagar_saves[i].shot);
		save->nmr_save.galagar_saves[i].zero1 = __bswap_32(save->nmr_save.galagar_saves[i].zero1);
		save->nmr_save.galagar_saves[i].percent = __bswap_32(save->nmr_save.galagar_saves[i].percent);
		save->nmr_save.galagar_saves[i].hp = __bswap_32(save->nmr_save.galagar_saves[i].hp);
		save->nmr_save.galagar_saves[i].score = __bswap_32(save->nmr_save.galagar_saves[i].score);
		save->nmr_save.galagar_saves[i].zero2 = __bswap_32(save->nmr_save.galagar_saves[i].zero2);
		save->nmr_save.galagar_saves[i].zero3 = __bswap_32(save->nmr_save.galagar_saves[i].zero3);
		save->nmr_save.galagar_saves[i].score_trophy = __bswap_32(save->nmr_save.galagar_saves[i].score_trophy);
		save->nmr_save.galagar_saves[i].zero4 = __bswap_32(save->nmr_save.galagar_saves[i].zero4);
		save->nmr_save.galagar_saves[i].beat = __bswap_32(save->nmr_save.galagar_saves[i].beat);

		save->nmr_save.galagar_saves[i].zero5 = __bswap_32(save->nmr_save.galagar_saves[i].zero5);
	}

	return save;
}

int write_save(nmm_save_t *save)
{
	FILE *fp = fopen("museum.bin", "ab");
	if(!fp) return EBADF;

	nmm_save_t *save_tmp = swap_save(save);

	fwrite(save_tmp, 1, sizeof(nmm_save_t), fp);

	fclose(fp);

	return 0;
}

