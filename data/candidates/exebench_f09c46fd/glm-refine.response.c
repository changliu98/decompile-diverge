Optimized and annotated for reverse engineering
void __cdecl minmax(int *arr, int size, int *min, int *max)
{
    // 'size' is unused in this function's logic. 
    // It is likely a leftover parameter from a loop that was inlined by the compiler,
    // or it is intended to be used by the caller to iterate over the array.
    (void)size; 

    // Update the minimum value if the current array element is smaller
    if (*arr < *min)
        *min = *arr;

    // Update the maximum value if the current array element is larger
    if (*arr > *max)
        *max = *arr;
}