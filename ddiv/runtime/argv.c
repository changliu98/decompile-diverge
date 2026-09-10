/* Used only with --input-mode argv. Both AFL and replay use this identical
 * adapter: stdin is a NUL-separated argv suffix. No shell parsing occurs. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern int __real_main(int argc, char **argv);

int __wrap_main(int argc, char **argv) {
    size_t cap = 4096, n = 0;
    char *data = malloc(cap + 1);
    if (!data) abort();
    int ch;
    while ((ch = getchar()) != EOF) {
        if (n == cap) {
            cap *= 2;
            char *next = realloc(data, cap + 1);
            if (!next) abort();
            data = next;
        }
        data[n++] = (char)ch;
    }
    clearerr(stdin);
    size_t count = n ? 1 : 0;
    /* A final NUL terminates the last argument; it does not add another one. */
    if (n && data[n - 1] == '\0') --n;
    for (size_t i = 0; i < n; ++i) if (!data[i]) ++count;
    data[n] = '\0';
    char **args = calloc((size_t)argc + count + 1, sizeof(char *));
    if (!args) abort();
    memcpy(args, argv, (size_t)argc * sizeof(char *));
    if (count) {
        size_t at = (size_t)argc;
        args[at++] = data;
        for (size_t i = 0; i < n; ++i) if (!data[i]) args[at++] = data + i + 1;
    }
    /* Keep argv alive through user atexit handlers, as normal process argv is. */
    return __real_main(argc + (int)count, args);
}
