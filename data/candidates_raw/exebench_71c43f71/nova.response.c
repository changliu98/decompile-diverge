static void func0(unsigned int *eax, unsigned int *ebx,
			   unsigned int *ecx, unsigned int *edx)
{
	__cpuid(eax, *ecx, *edx);
	*ecx = ecx[0];
	*edx = edx[0];
}