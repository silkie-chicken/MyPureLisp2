#ifndef INCLUDEGUARD_MYPURELISP_UTIL
#define INCLUDEGUARD_MYPURELISP_UTIL

#include <stdio.h>
#include <stdlib.h>

#define if_null_exit(val, ...) \
	if (val == NULL){ \
		perror(__VA_ARGS__); \
		exit(1); \
	}

//use in header file
//操作関数の構造体の実体を宣言
//任意の名前のInterfaceの実体を定義
//TYPEDEF_INTERFACE (新しいインターフェイス型の名前, {関数ポインタ;, 関数ポインタ; ...}) 
#define TYPEDEF_INTERFACE(name, methods_block) \
	typedef struct name##_methods methods_block\
	name##Methods; \
	\
	typedef struct{ \
		struct name ##_methods* methods; \
		void* data; \
	}name;


#define REGIST_METHOD(obj_name, method_name) \
	obj_name##Methods.method_name = obj_name##_##method_name;

#define CLEATE_METHOD_INSTANCE(name) \
	struct name##_methods name##Methods;


#define TYPEDEF_STRUCT_WITH_METHODS(name, members_block, methods_block) \
	struct name##_methods { \
		methods_block \
	}; \
	\
	extern struct name##_methods name##Methods; \
	\
	typedef struct { \
		struct name##_methods* methods; \
		members_block \
	}name;


#define METHOD_CALL(obj, funcname) \
	((obj).methods->funcname)

//#define SETF_INTERFACE(name_of_interface, name_of_variables, name_of_type) \
//	name_of_interface ## _methods_instance.Swap = name_of_type ## _Swap

#endif
