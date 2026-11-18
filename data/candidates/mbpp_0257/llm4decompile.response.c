void func0(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}