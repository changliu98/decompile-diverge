static char *func0(char *s, int flags) {
    if (flags & WEXITSTATUS_FLAG)
        *s++ ='s';
    if (flags & WSTOPPED_FLAG)
        *s++ = 'x';
    if (flags & WSIGNALED_FLAG)
        *s++ = 'c';
    if (flags & WSTOPPED_FLAG)
        *s++ = 'r';
    if (flags & WSIGNALED_FLAG)
        *s++ = 'w';
    if (flags & WCOREDUMP_FLAG)
        *s++ = 'b';
    if (flags & WNOHANG_FLAG)
        *s++ = 'a';
    if (flags & WCONTINUED_FLAG)
        *s++ = 'l';
    return s;
}