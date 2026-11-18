#include <assert.h>

int foo(int *x)
{
 *x = *x + 3;
 return *x;
}
