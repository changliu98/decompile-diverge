void __attribute__ ((noinline))
native_cpuid (unsigned int *a, unsigned int *b, unsigned int *c, unsigned int *d)
{
  asm ("pushq %%rax\n\t"
       "movl (%0),%%eax\n\t"
       "movl (%1),%%ecx\n\t"
       "pushq %%rbx\n\t"
       "pushq %%rdx\n\t"
       "pushq %%rcx\n\t"
       "pushq %%rdx\n\t"
       "cpuid\n\t"
       "popq %%rdx\n\t"
       "popq %%rcx\n\t"
       "popq %%rdx\n\t"
       "popq %%rbx\n\t"
       "movl %%eax,(%0)\n\t"
       "movl %%ebx,(%1)\n\t"
       "movl %%ecx,(%2)\n\t"
       "movl %%edx,(%3)\n\t"
       :
       : "r" (a), "r" (b), "r" (c), "r" (d));
}