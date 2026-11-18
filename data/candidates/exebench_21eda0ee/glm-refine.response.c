void __cdecl do_cpuid(unsigned int *eax_0, unsigned int *ebx_0, unsigned int *ecx_0, unsigned int *edx_0)
{
    unsigned int a, b, c, d;

    __asm
    {
        mov eax, dword ptr [eax_0]
        mov a, eax
        mov eax, a
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