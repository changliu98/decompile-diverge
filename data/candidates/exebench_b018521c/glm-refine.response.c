void __cdecl cpuid(unsigned int op, unsigned int *eax_0, unsigned int *ebx_0, unsigned int *ecx_0, unsigned int *edx_0)
{
    int regs[4];

    __asm
    {
        mov eax, op
        cpuid
        mov regs[0], eax
        mov regs[1], ebx
        mov regs[2], ecx
        mov regs[3], edx
    }

    *eax_0 = (unsigned int)regs[0];
    *ebx_0 = (unsigned int)regs[1];
    *ecx_0 = (unsigned int)regs[2];
    *edx_0 = (unsigned int)regs[3];
}