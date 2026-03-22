#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 *  int (*ptr)[20] -> pointer to the array of 20 elements
 *  int *ptr[20] -> array of 20 pointers to int*/ 

void check_array(int (*ptr)[20])
{
	int *x = (int *)ptr;
	printf("data check %p %d %d\n", ptr, x[0], *ptr[0]);
}

void check_array_of_ptr(int *ptr[20])
{
	check_array((int(*)[20])ptr[0]);
}

int main()
{
	int arr[20] = { 1, 2, 4 };
	int brr[20] = { 4, 5, 6 };

	/*both are same*/
	check_array(&arr);
	check_array(arr);

	int *ptr_array[20] = { arr, brr };

	check_array_of_ptr(ptr_array);

	return 0;
}
