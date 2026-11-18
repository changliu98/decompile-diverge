void __attribute__ ((noinline))
test_cpuid (unsigned int *a, unsigned int *b, unsigned int *c, unsigned int *d)
{
  asm ("pushq %%rax\n\t"
       "movl (%0), %%eax\n\t"
       "pushq %%rbx\n\t"
       "movl (%1), %%ebx\n\t"
       "pushq %%rcx\n\t"
       "movl (%2), %%rcx\n\t"
       "pushq %%rdx\n\t"
       "movl (%3), %%rdx\n\t"
       "cpuid\n\t"
       "popq %%rdx\n\t"
       "movl %%eax, (%0)\n\t"
       "movl %%ebx, (%1)\n\t"
       "movl %%ecx, (%2)\n\t"
       "movl %%edx, (%3)\n\t"
       "popq %%rcx\n\t"
       "popq %%rbx\n\t"
       "popq %%rax\n\t"
       :
       : "r" (a), "r" (b), "r" (c), "r" (d));
}