/* Linked as a separate object. The user's main and source bytes stay intact.
 * Only the clean build enables observers: ASan global redzones must never be
 * read by the bulk .data/.bss snapshot. Runtime globals are excluded by the
 * source-object symbol whitelist used by the runner. */
#include "ddiv.h"
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef DDIV_CLEAN
extern unsigned char __data_start[], _edata[], __bss_start[], _end[];

static int ddiv_write_all(int fd, const void *ptr, size_t n) {
    const unsigned char *p = ptr;
    while (n) {
        ssize_t wrote = write(fd, p, n);
        if (wrote < 0 && errno == EINTR) continue;
        if (wrote <= 0) return -1;
        p += wrote;
        n -= (size_t)wrote;
    }
    return 0;
}

static void ddiv_snapshot(void) {
    const char *path = getenv("DDIV_STATE_PATH");
    if (!path) return;
    uint64_t sizes[2] = {(uintptr_t)_edata - (uintptr_t)__data_start,
                         (uintptr_t)_end - (uintptr_t)__bss_start};
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) return;
    if (ddiv_write_all(fd, "DDIV1\0\0\0", 8) == 0 &&
        ddiv_write_all(fd, sizes, sizeof sizes) == 0 &&
        ddiv_write_all(fd, __data_start, sizes[0]) == 0)
        ddiv_write_all(fd, __bss_start, sizes[1]);
    close(fd);
}

/* Registered before ordinary user constructors, hence called after their exit
 * handlers. Abnormal exit and _exit/_Exit do not produce a snapshot. */
__attribute__((constructor(101))) static void ddiv_setup(void) {
    atexit(ddiv_snapshot);
}

void ddiv_observe(const char *name, const void *bytes, size_t size) {
    int saved_errno = errno;
    const char *path = getenv("DDIV_OBSERVATIONS_PATH");
    if (!path) return;
    int fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (fd >= 0) {
        uint64_t lengths[2] = {strlen(name), size};
        if (ddiv_write_all(fd, lengths, sizeof lengths) == 0 &&
            ddiv_write_all(fd, name, lengths[0]) == 0)
            ddiv_write_all(fd, bytes, size);
        close(fd);
    }
    errno = saved_errno;
}
#else
void ddiv_observe(const char *name, const void *bytes, size_t size) {
    (void)name; (void)bytes; (void)size;
}
#endif
