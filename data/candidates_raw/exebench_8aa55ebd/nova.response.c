static void func0(int subfunc, int feature, int *eax, int *ebx,
			   int *ecx, int *edx)
{
	int orig_eax = *eax;
	int orig_ebx = *ebx;
	int orig_ecx = *ecx;
	int orig_edx = *edx;

	asm volatile(
		"cpuid;"
		: "=a" (*eax),
		  "=b" (*ebx),
		  "=c" (*ecx),
		  "=d" (*edx)
		: "0" (subfunc),
		  "2" (feature)
	);

	*eax -= orig_eax;
	*ebx -= orig_ebx;
	*ecx -= orig_ecx;
	*edx -= orig_edx;
}