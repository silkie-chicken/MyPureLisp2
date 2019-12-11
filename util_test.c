#include <stdint.h>
#include "util_test.h"

//コンストラクタは自分で書いて
//Array型へMethodを定義したことにする=================
void Array_Swap(void* arr, int a, int b){
	printf("called Swap(%d, %d)\n", a, b);
}

int Array_LeftIsBig(void* arr, int a, int b){
	return 0;
}
//====================================================

//struct Array_methods ArrayMethods;
CLEATE_METHOD_INSTANCE(Array)

//SortAbleIntarface型へSort()を定義
void SortAble_Sort(SortAble* s){
}


int main(void){
	REGIST_METHOD(Array, Swap)
	REGIST_METHOD(Array, LeftIsBig)
	Array a = {&ArrayMethods, {1, 2, 3}, 3};
	METHOD_CALL(a, Swap)(&a, 1, 2);
		//SETF_INTERFACE(Array, s, arr);
	return 0;
}
