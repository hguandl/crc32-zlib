#include <stdio.h>
#include <string.h>
#include <zlib.h>

#define BUF_SIZE (4*1024*1024)

unsigned char buf[BUF_SIZE];

int main(int argc, char const *argv[])
{
	FILE *file;

	for (int t = 1; t < argc; ++ t) {
		file = fopen(argv[t], "r");

		if (file == NULL) {
			continue;
		}

		int len;
		unsigned long crc = crc32(0L, Z_NULL, 0);
		while ((len = fread(buf, sizeof(unsigned char), BUF_SIZE, file)) != 0) {
			crc = crc32(crc, buf, len);
		}
		
		if (crc == 0) {
			fprintf(stderr, "%s: Is a blank file or directory\n", argv[t]);
		} else {
			printf("%08lx\t%s\n", crc, argv[t]);
		}
	}
	
	return 0;
}
