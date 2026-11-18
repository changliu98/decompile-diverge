void __cdecl initialize_temp(unsigned int *src, unsigned int *temp)
{
    int j = 14;
    
    // Copy the 10 elements from src to temp[14..5]
    for (int i = 9; i >= 0; --i)
        temp[j--] = src[i];

    // Zero out the remaining elements in temp[4..0]
    while (j >= 0)
        temp[j--] = 0;
}