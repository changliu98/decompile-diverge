void __cdecl SWAP(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}