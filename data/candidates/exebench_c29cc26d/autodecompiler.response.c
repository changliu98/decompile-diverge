char *strcpy_x86_64_fast(char *dest, const char *src)
{
  asm volatile("1:\n\t"
               "lodsb\n\t"
               "stosb\n\t"
               "testb %%al,%%al\n\t"
               "jne 1b\n\t"
               : "=D"(dest), "=S"(src)
               : "0"((long) dest), "1"((long) src)
               : "memory");
  return dest;
}