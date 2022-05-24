#include <stdio.h>
#include "io/io.h"

int main() {
	io_reader r = io_new_reader(512);
	if (!io_fcopy(r, "./src/main.c", stdout)) {
		perror("Could not copy file ./main.c");
	}

	return 0;
}
