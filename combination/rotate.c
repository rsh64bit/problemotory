/*rotate*/
/*basic recursion*/

#include<stdio.h>
static void rotate(int *a, int n, int k)
{
	int i = n - 1, s = a[n - 1];

	printf(" enter %s ptr %4p %4p\n", __func__, a, &a);
	if (k == 0) {
		printf("  k == 0 return %s\n", __func__);
		return;
	}

	for(; i > 0; --i ) {
		a[i] = a[i - 1];
	}
	a[0] = s;

	rotate(a, n, k - 1);

	printf("exit %s\n", __func__);
}

#define print_array(arr) for (int l = 0; l < sizeof(arr)/sizeof(arr[0]); ++l) { \
	printf("%d", sizeof(arr)/sizeof(arr[0]));\
	printf("%d", arr[l]);\
	}
int main()
{

	int a[] = {1, 2, 3, 4};
	//printf(" enter %s ptr %4p %4p\n", __func__, a, &a);

	//rotate(a, 4, 2);
#if 0
	printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);
	for (int l = 0; l < sizeof(a)/sizeof(a[0]); ++l) { 
	printf("  %d %d \n", l, a[l]);
	}
#endif
	printf("done\n");
	//print_array(a);

}
