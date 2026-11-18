void __cdecl cpuid(int op, int *eax_0, int *ebx_0, int *ecx_0, int *edx_0)
{
    int a, b, c, d;
    __asm {
        mov eax, op
        cpuid
        mov a, eax
        mov b, ebx
        mov c, ecx
        mov d, edx
    }
    *eax_0 = a;
    *ebx_0 = b;
    *ecx_0 = c;
    *edx_0 = d;
}