#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <byteswap.h>
#include <errno.h>
#include "save.h"

int main(int argc, char **argv)
{
	/*
	SAVE_TYPE id = id_save(argv[1]);

	switch(id)
	{
		case NMR:
			printf("nmr save\n");
			break;
		case NMM:
			printf("nmm save\n");
			break;
		case ERR:
			printf("not a save\n");
			break;
	}

	if(errno) perror("test");
	*/

	// printf("%d\n", sizeof(galagar_save_t));

	nmm_save_t *save = malloc(sizeof(nmm_save_t));
	memset(save, 0, sizeof(nmm_save_t));

	save->nmr_save.galagar_saves[1].score = 65535;
	save->nmr_save.galagar_saves[1].beat = 1;

	save = update_save(save);

	printf("%x\n", save->nmr_save.crc);

	//save = swap_save(save);

	write_save(save);

	return 0;
}

