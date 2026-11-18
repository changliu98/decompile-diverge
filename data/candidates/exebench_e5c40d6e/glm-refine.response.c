void __cdecl swap(int *a, int *b)
{
    int temp = *a ^ *b;
    *a = temp;
    *b = *b ^ temp;
    *a ^= *b;
}