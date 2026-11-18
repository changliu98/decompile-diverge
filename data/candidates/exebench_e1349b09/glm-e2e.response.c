char* strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    char c;

    // The cld instruction clears the direction flag, 
    // ensuring rsi and rdi increment after lods and stos.
    do {
        // lods %ds:(%rsi),%al
        c = *src++;
        
        // stos %al,%es:(%rdi)
        *dest++ = c;
        
    // test %al,%al ; jne 11e5
    } while (c != '\0');

    // The instructions at 11ef-11f9 appear to be unoptimized compiler artifacts 
    // (storing internal registers into unused stack space), but the final 
    // step before returning is moving the original destination pointer into rax.
    
    // mov -0x8(%rbp),%rax
    return original_dest;
}