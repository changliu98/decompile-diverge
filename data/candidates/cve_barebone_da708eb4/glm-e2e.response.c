const char* jvp_literal_number_literal(int arg1, int arg2) {
    // 2480: movzbl -0x18(%rbp),%eax
    // 2484: cmp $0x94,%eax
    assert((arg1 & 0xFF) == 0x94);

    void* dec_number = jvp_dec_number_ptr(arg1, arg2);
    void* literal_number = jvp_literal_number_ptr(arg1, arg2);

    char* result;

    // 24d9: movzbl 0x8(%rax),%eax
    // 24dd: and $0x30,%eax
    if ((*(unsigned char*)((char*)dec_number + 8) & 0x30) != 0) {
        // 24e9: lea 0xbfb(%rip),%rax
        result = "NaN";
    } 
    // 24fd: movzbl 0x8(%rax),%eax
    // 2501: and $0x40,%eax
    else if ((*(unsigned char*)((char*)dec_number + 8) & 0x40) != 0) {
        // 250d: movq $0x0,-0x8(%rbp)
        result = NULL;
    } 
    // 251e: cmpq $0x0,0x10(%rax)
    else if (*(char**)((char*)literal_number + 16) != NULL) {
        // 2567: mov 0x10(%rax),%rax
        result = *(char**)((char*)literal_number + 16);
    } 
    else {
        // 2536: mov (%rax),%eax
        // 2538: add $0xe,%eax
        int size = *(int*)dec_number + 14;
        
        // 2542: call 2430 <jv_mem_alloc>
        char* str = (char*)jv_mem_alloc((long)size);
        
        // 254e: mov %rcx,0x10(%rax)
        *(char**)((char*)literal_number + 16) = str;
        
        // 255e: call 11d0 <decNumberToString>
        decNumberToString(dec_number, str);
        
        result = str;
    }

    // 256f: mov -0x8(%rbp),%rax
    return result;
}