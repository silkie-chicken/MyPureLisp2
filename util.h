#ifndef INCLUDEGUARD_MYPURELISP_UTIL
#define INCLUDEGUARD_MYPURELISP_UTIL

#include <stdio.h>

#define if_null_exit(val, ...) \
	if (val == NULL){ \
		perror(__VA_ARGS__); \
		exit(1); \
	}

#endif
