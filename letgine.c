#include "letgine.h"

static char     _LGBUF[LGBUFSIZ];
static char*    _BUFSEEK    = NULL;

static char*    _LGLINEBUF  = NULL;
static char*    _LINESEEK   = NULL;

#define _readbuffer(fd) do {            \
		read(fd, _LGBUF, LGBUFSIZ - 1); \
		_LGBUF[LGBUFSIZ-1] = EOF;       \
		_BUFSEEK = _LGBUF;              \
	} while (0)

static char*
_init()
{
	_LGLINEBUF  = (char*)malloc(LGLINEBUFSIZ);
	_LINESEEK   = _LGLINEBUF;
	return _LGLINEBUF;
}

static void
_grow()
{
}

static void
_shrink()
{
}

char*
letgine(size_t size, int fd)
{
	size_t nread = 0;

	if (!_LGLINEBUF && !_init()) {
		return NULL;
	}

	if (!_BUFSEEK || *_BUFSEEK == EOF) {
		_LINESEEK = _LGLINEBUF;
		_readbuffer(fd);
	}

	while (*_BUFSEEK != '\0' || *_BUFSEEK != EOF) {
		if (nread == size) {
			break;
		}

		*_LINESEEK = *_BUFSEEK++;
		if (*_LINESEEK == '\n') {
			*++_LINESEEK = '\0';
			break;
		} else {
			++_LINESEEK;
		}

		++nread;
	}

	return _LGLINEBUF;
}
