#include<stdio.h>
#include<stdint.h>


/*fibonacci series
 * 0, 1, 1, 2, 3,...
 * f(n) = f(n - 1) + f(n - 2)
 * f(0) = 0, f(1) = 1
 * f(2) = f(1) + f(0) = 1
 */


static int calls = 0;

int fibonacci(int i, int level)
{
    printf("recur index %d level %d\n", i, level);

    ++calls;
    if (i <=1) return i;

    return fibonacci(i - 1, level + 1) + fibonacci(i - 2, level + 1);

}

void test_fib(int n)
{
    int a[100] = {};
    int level = 0;
    for (int i = 0; i < n; ++i) {
        a[i] = fibonacci(i, level);
    }

    printf("fibonacci -> ");
    for (int i = 0; i < n; ++i)
    printf(" %2d ", a[i]);

    printf("\n");

    printf("depth n=%d calls %d \n",n, calls);
    calls = 0;
}

int main()
{
    test_fib(10);
    return 0;
}

