#ifndef _LETGINE_H
#define _LETGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LGBUFSIZ        8192
#define LGLINEBUFSIZ    128

char* letgine(size_t size, int fd);

#endif /* !_LETGINE_H */
