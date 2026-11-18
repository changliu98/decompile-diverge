char *strcpy(char *dest, const char *src)
{
    asm volatile("cld\n\t"
                 "1:\tlodsb\n\t"
                 "stosb\n\t"
                 "testb %%al,%%al\n\t"
                 "jne 1b\n\t"
                 : "=D"(dest), "=S"(src)
                 :
                 : "memory");
    return dest;
}