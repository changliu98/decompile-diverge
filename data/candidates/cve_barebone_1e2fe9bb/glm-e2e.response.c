void beep_print(struct Context *ctx, const char *s, int len) {
    // The structure has a function pointer at offset 0x98 (152 bytes).
    // Based on the calling convention, it takes the context and a format string.
    void (*emit)(struct Context *, const char *, ...) = *(void (**)(struct Context *, const char *, ...))((char *)ctx + 0x98);

    if (l_strnstart("\x1b[1m", 4, s, len)) {
        emit(ctx, "\x1b[1m");
    } else if (l_strnstart("\x1b[4m", 4, s, len)) {
        emit(ctx, "\x1b[4m");
    } else if (l_strnstart("\x1b[5m", 4, s, len)) {
        emit(ctx, "\x1b[5m");
    } else if (l_strnstart("\x1b[7m", 4, s, len)) {
        emit(ctx, "\x1b[7m");
    } else if (l_strnstart("\x1b[0m", 4, s, len)) {
        emit(ctx, "\x1b[0m");
    } else if (l_strnstart("\x1b[8m", 4, s, len)) {
        emit(ctx, "\x1b[8m");
    } else if (l_strnstart("\x07", 4, s, len)) { 
        // Note: The prefix string is "\x07\x00\x00\x00" (length 4), 
        // but effectively checks for the BEL character.
        emit(ctx, "\x07");
    } else {
        emit(ctx, "%s");
    }
}