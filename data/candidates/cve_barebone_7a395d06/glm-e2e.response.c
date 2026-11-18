int chdlc_if_print(void *arg1, void *arg2, void *arg3) {
    int var_4;
    int var_24 = *(int *)((char *)arg2 + 0x14);
    int var_28 = *(int *)((char *)arg2 + 0x10);

    if (var_28 < 4) {
        // The function pointer is located at offset 0x10 of arg1
        int (*print_error)(void *, const char *, ...) = *(int (**)(void *, const char *, ...))((char *)arg1 + 0x10);
        var_4 = print_error(arg1, "chdlc_if_print: packet too short");
    } else {
        var_4 = chdlc_print(arg1, arg3, var_24);
    }

    return var_4;
}