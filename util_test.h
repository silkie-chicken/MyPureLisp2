#include "util.h"

TYPEDEF_INTERFACE(SortAble, {
		void (*Swap)     (int, int);
		int  (*LeftIsBig)(int, int);
	})

TYPEDEF_WITH_METHODS(Array, {
		int array[];
		int num;
	},{
		void (*Swap)     (int, int);
		int  (*LeftIsBig)(int, int);
	})



