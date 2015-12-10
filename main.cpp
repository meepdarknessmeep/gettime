#define _CRT_SECURE_NO_WARNINGS
#include "peb.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{

	_IMAGE_DOS_HEADER dos;
	_IMAGE_NT_HEADERS nt;

	while (argc >= 2)
	{

		char timestamp[128] = "Invalid file";

		FILE *f = fopen(argv[--argc], "rb");

		if (!f)
			continue;

		if (fread(&dos, 1, sizeof(dos), f) == sizeof(dos) && dos.e_magic == 'ZM')
		{

			fseek(f, dos.e_lfanew, SEEK_SET);
			if (fread(&nt, 1, sizeof(nt), f) == sizeof(nt))
			{
				
				time_t t = nt.file.TimeDateStamp;

				strftime(timestamp, sizeof(timestamp), "%F %T", localtime(&t));

			}

		}

		fclose(f);

		printf("%s\t%s\n", argv[argc], timestamp);

	}



	return 0;

}