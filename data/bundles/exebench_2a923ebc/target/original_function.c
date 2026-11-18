void swap(int * const p1, int * const p2)
{
 int tmp = *p1;
 *p1 = *p2;
 *p2 = tmp;
}