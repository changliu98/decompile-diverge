int __cdecl divide(int a, int b, int *remainder)
{
    // Note: If b == 0, this will trigger a hardware divide-by-zero exception (#DE).
    // Note: If a == INT_MIN and b == -1, this triggers an overflow exception (#DE).
    
    *remainder = a % b;
    return a / b;
}