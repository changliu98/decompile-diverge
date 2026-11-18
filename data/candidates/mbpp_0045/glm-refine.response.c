// Computes the Greatest Common Divisor (GCD) of an array of integers.
// Note: This function assumes 'size' is at least 2, otherwise an out-of-bounds read will occur.
int __cdecl gcd_of_array(int *arr, int size)
{
    int gcd = find_gcd(arr[0], arr[1]);

    for (int i = 2; i < size; ++i)
    {
        gcd = find_gcd(gcd, arr[i]);
    }

    return gcd;
}