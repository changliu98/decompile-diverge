void __cdecl run_cpuid(int eax_0, int ecx_0, int *abcd)
{
    int a, b, c, d;

    __asm__ __volatile__(
        "cpuid"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d) // Output operands
        : "a" (eax_0), "c" (ecx_0)               // Input operands
    );

    abcd[0] = a;
    abcd[1] = b;
    abcd[2] = c;
    abcd[3] = d;
}