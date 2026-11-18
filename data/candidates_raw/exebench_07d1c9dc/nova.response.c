static void func0(unsigned int op, unsigned int op1, unsigned int op2,
		     unsigned int *eax, unsigned int *ebx, unsigned int *ecx,
		     unsigned int *edx)
{
	__asm__ __volatile__ (".byte 0x0f,0x11,0x80"
			      : "=a" (*eax),
				"=b" (*ebx),
				"=c" (*ecx),
				"=d" (*edx)
			      : "a" (op), "b" (op1), "c" (op2));
}