#include <stdlib.h>
#include "io.h"

io_reader io_new_reader(uint32_t cap) {
	io_reader r = malloc(sizeof(struct io_reader));
	r->buf = malloc(sizeof(char) * cap);
	r->cap = cap;

	return r;
}

bool io_open(io_reader r, string filename) {
	r->src = fopen(filename, "r");
	r->len = 0;
	return r->src != NULL;
}

bool io_close(io_reader r) {
	return !fclose(r->src);
}

bool io_feed(io_reader r) {
	if (!r->len || r->seek >= r->cap) {
		r->len = fread(r->buf, sizeof(char), r->cap, r->src);
		r->seek = 0;
		return r->len != 0;
	} else if (r->seek >= r->len) {
		return false;
	} else {
		r->seek++;
		return true;
	}
}

byte io_read(io_reader r) {
	return r->buf[r->seek];
}

bool io_fcopy(io_reader r, string filename, stream dest) {
	if (!io_open(r, filename))
		return false;
	while (io_feed(r)) {
		fprintf(dest, "%c", io_read(r));
	}
	printf("\n");
	return io_close(r);
}