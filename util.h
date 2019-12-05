#ifndef INCLUDEGUARD_MYPURELISP_UTIL
#define INCLUDEGUARD_MYPURELISP_UTIL

#include <stdio.h>
#include <stdlib.h>

#define if_null_exit(val, ...) \
	if (val == NULL){ \
		perror(__VA_ARGS__); \
		exit(1); \
	}

/*
typedef struct ops{
	int (*hoge)(int, int);
	int (*wiwe)(char*);
}

typedef struct interface{
	struct ops;
	void*  priv;
}hogehoge Interface;

//新しいインターフェイス型の名前　関数群 int hoge(int,int)
#define TYPEDEF_INTERFACE(name, ...) \
	typedef struct{ \
	\
	}ops; \
	\
	typedef struct{ \

	}name;


//
//typedef struct hoge{
//	int oseijf; 
//	int osie;
//	struct hoge_ops*;
//}
//
//typedef struct interface{
//	struct ops;
//	struct vals* vals;
//}Interface;
//
//#define Method()

//#define TYPEDEF_Interface(name,, ...)

*/
#endif
