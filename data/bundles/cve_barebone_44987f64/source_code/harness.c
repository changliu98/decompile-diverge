/* cve_barebone direct-call harness for redis_check_aof_main
 * CVE fix commit 643b5db235cb82508e72f11c7b4bbfc7dc39be56 (redis/redis):
 *   redis_check_aof_main's own body does
 *       char temp_filepath[PATH_MAX + 1];
 *       memcpy(temp_filepath, filepath, strlen(filepath) + 1);
 *   with NO bound check on strlen(filepath) before the fix. filepath is derived
 *   directly from argv[1]/argv[2]/argv[3] (attacker-controlled path/argument).
 *   A filepath longer than PATH_MAX overflows the stack buffer temp_filepath ->
 *   CWE-787 stack-based buffer overflow (WRITE), caught by ASAN. This harness
 *   reproduces the bug by calling redis_check_aof_main directly with a
 *   synthetic argv built from the input file's bytes.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <libgen.h>
#include <time.h>

/* ---- real type defs redis_check_aof_main needs (from src/sds.h, src/redis-check-aof.c) ---- */
typedef char *sds;

typedef enum {
    AOF_RESP,
    AOF_RDB_PREAMBLE,
    AOF_MULTI_PART,
} input_file_type;

/* file-local static, verbatim name from src/redis-check-aof.c:62 */
static time_t to_timestamp = 0;

/* ---- minimal faithful stubs for callees not on the crash path ----
 * The crash (stack buffer overflow in temp_filepath) happens in the memcpy
 * BEFORE any of these are invoked, so they only need to exist for the
 * function to link and to let "safe" inputs run to a clean exit(0). */
static sds getVersion(void) {
    return strdup("0.0.0");
}
static void sdsfree(sds s) {
    free(s);
}
static input_file_type getInputFileType(char *filepath) {
    (void)filepath;
    return AOF_RESP;
}
static void checkMultiPartAof(char *dirpath, char *filepath, int fix) {
    (void)dirpath; (void)filepath; (void)fix;
}
static void checkOldStyleAof(char *filepath, int fix, int preamble) {
    (void)filepath; (void)fix; (void)preamble;
}

/* ==== BEGIN verbatim redis_check_aof_main (data_cve/cve_44987f64/target/original_function.c) ==== */
int redis_check_aof_main(int argc, char **argv) {
    char *filepath;
    char temp_filepath[PATH_MAX + 1];
    char *dirpath;
    int fix = 0;

    if (argc < 2) {
        goto invalid_args;
    } else if (argc == 2) {
        if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
            sds version = getVersion();
            printf("redis-check-aof %s\n", version);
            sdsfree(version);
            exit(0);
        }

        filepath = argv[1];
    } else if (argc == 3) {
        if (!strcmp(argv[1], "--fix")) {
            filepath = argv[2];
            fix = 1;
        } else {
            goto invalid_args;
        }
    } else if (argc == 4) {
        if (!strcmp(argv[1], "--truncate-to-timestamp")) {
            char *endptr;
            errno = 0;
            to_timestamp = strtol(argv[2], &endptr, 10);
            if (errno != 0 || *endptr != '\0') {
                printf("Invalid timestamp, aborting...\n");
                exit(1);
            }
            filepath = argv[3];
        } else {
            goto invalid_args;
        }
    } else {
        goto invalid_args;
    }

    /* In the glibc implementation dirname may modify their argument. */
    memcpy(temp_filepath, filepath, strlen(filepath) + 1);
    dirpath = dirname(temp_filepath);

    /* Select the corresponding verification method according to the input file type. */
    input_file_type type = getInputFileType(filepath);
    switch (type) {
    case AOF_MULTI_PART:
        checkMultiPartAof(dirpath, filepath, fix);
        break;
    case AOF_RESP:
        checkOldStyleAof(filepath, fix, 0);
        break;
    case AOF_RDB_PREAMBLE:
        checkOldStyleAof(filepath, fix, 1);
        break;
    }

    exit(0);

invalid_args:
    printf("Usage: %s [--fix|--truncate-to-timestamp $timestamp] <file.manifest|file.aof>\n",
        argv[0]);
    exit(1);
}
/* ==== END verbatim redis_check_aof_main ==== */

/* ---- driver: read the corpus input file, build filepath from its bytes,
 * call redis_check_aof_main directly (argc=2, argv[1]=filepath) ---- */
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <inputfile>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    fseek(f, 0, SEEK_SET);

    /* heap-allocate the buffer that becomes filepath (ASAN-guarded) */
    char *buf = malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return 1; }
    size_t rd = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[rd] = '\0';

    char *fake_argv[2];
    fake_argv[0] = "redis-check-aof";
    fake_argv[1] = buf;

    redis_check_aof_main(2, fake_argv);
    /* unreachable: redis_check_aof_main always exit()s */
    return 0;
}
