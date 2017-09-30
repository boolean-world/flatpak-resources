#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

void print_file_contents(FILE *fp) {
	char c;

	while ((c = fgetc(fp)) != EOF) {
		printf("%c", c);
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		print_file_contents(stdin);
		return 0;
	}

	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		printf(
			"Usage: %s [filename]...\n"
			"Concatenate files to standard output\n",
			argv[0]);
		return 0;
	}

	bool has_error = false;

	for (int i = 1; i < argc; i++) {
		if (strcmp("-", argv[i]) == 0) {
			print_file_contents(stdin);
		}
		else {
			FILE *fp = fopen(argv[i], "r");

			if (fp == NULL) {
				fprintf(stderr, "Failed to open %s: %s\n", argv[i], strerror(errno));
				has_error = true;
			}
			else {
				print_file_contents(fp);
				fclose(fp);
			}
		}
	}

	return (int)has_error;
}
