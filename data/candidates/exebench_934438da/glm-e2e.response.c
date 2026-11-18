void testfunc16(int *arg1, int *arg2, int *arg3, int *arg4, int *arg5) {
    if (*arg1 > 100) {
        // Empty body (compiler optimized out or empty if block)
    }

    if (*arg5 > 100) {
        // Empty body
    }

    arg5 += 1;     // add $0x4, %rax (pointer arithmetic for int*)
    arg5 += 10;    // add $0x28, %rax (0x28 / 4 = 10)
    
    arg2 += 1;     // add $0x4, %rax
    
    *arg2 += 100;  // add $0x64, %ecx and mov %ecx, (%rax)

    if (*arg3 > 1000) {
        // Empty body
    }

    if (*arg4 < 100) {
        // Empty body
    }

    // 1266: add %al, (%rax)
    // This is likely an artifact of disassembly reading past the end of the function 
    // (often a zero byte 0x00 interpreted as `add %al, (%rax)`), or a corrupted instruction.
}