static void do_cpuid(unsigned int *eax, unsigned int *ebx,
				unsigned int *ecx, unsigned int *edx)
{
	__cpuid(eax, *ecx, *edx);
	*edx = ebx[0];
	*ecx = ebx[1];
}