static void cpuinfo(int func, int *ax, int *bx, int *cx, int *dx)
{
	asm volatile("cpuinfo"
		     : "=a" (*ax),
		       "=b" (*bx),
		       "=c" (*cx),
		       "=d" (*dx)
		     : "a" (*ax), "c" (*cx), "b" (*bx), "d" (*dx), "0" (func));
}