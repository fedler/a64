#ifndef A64IO_H
#define A64IO_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef char byte;
typedef FILE * stream;

// Efficiently transfers chunks of memory.
typedef byte *buffer;

// Immutable, null terminated, sequence of ascii characters.
typedef char const * const string;

// Buffered reader for an byte stream
typedef struct io_reader * io_reader;

// Buffered reader for an byte stream
struct io_reader {
	buffer    buf;   // A chunk of memory to read bytes into
	uint32_t  cap;   // Number of bytes the buffer can hold.
	uint32_t  len;   // Number of bytes the buffer holds.
	uint32_t  seek;  // Index of the next character to be read.
	stream    src;   // The source being read from
};

// Creates an io_reader with a specified buffer capacity
io_reader io_new_reader(uint32_t cap);

// Tells a reader to open a file by name.
//    returns if the file was successfully opened. When false, check perror
//    for the failure code and message.
bool io_open(io_reader r, string filename);

// Tells a reader to close the open file.
//    returns if the file was successfully closed. When false, check perror for
//    the failure code and message.
bool io_close(io_reader r);

// Returns the next byte in the stream.
byte io_read(io_reader r);

// Feed moves past the current byte and returns if there exists more bytes in
// the stream to read.
bool io_feed(io_reader r);

bool io_fcopy(io_reader r, string filename, stream dest);
#endif
