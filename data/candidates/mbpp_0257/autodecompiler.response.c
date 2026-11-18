void func0(int *pa, int *pb)
{
 int temp = *pa;
 *pa = *pb;
 *pb = temp;
}