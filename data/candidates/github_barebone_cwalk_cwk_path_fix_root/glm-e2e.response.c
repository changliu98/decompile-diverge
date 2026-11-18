void cwk_path_fix_root(char *path, size_t *length, size_t *absolute_length) {
    // 14: cmpl $0x0,0x0(%rip)
    // 1b: je 26
    if (separator[0] == '\0') {
        return;
    }

    // 26: mov -0x18(%rbp),%rax
    // 2a: cmp -0x10(%rbp),%rax
    // 2e: jbe 3c
    // 34: mov -0x10(%rbp),%rax
    // 38: mov %rax,-0x18(%rbp)
    if (*absolute_length > *length) {
        *absolute_length = *length;
    }

    // 3c: movq $0x0,-0x20(%rbp)
    for (size_t i = 0; i < *absolute_length; i++) {
        // 52: mov -0x8(%rbp),%rdi
        // 56: add -0x20(%rbp),%rdi
        // 5a: call 5f
        // 5f: test $0x1,%al
        // 61: jne 6c
        if (is_separator(&path[i])) {
            // 6c: mov 0x0(%rip),%rax
            // 73: mov (%rax),%dl
            // 75: mov -0x8(%rbp),%rax
            // 79: mov -0x20(%rbp),%rcx
            // 7d: mov %dl,(%rax,%rcx,1)
            path[i] = *separator;
        }
    }
}