/*
 * Direct-call crash harness for CVE-2022-1907 (libmobi, mobi_search_links_kf7).
 *
 * Reproduces the heap-buffer-overflow READ (CWE-125) at
 *   if (*(data - 1) == '/' && *data == '>')
 * in src/parse_rawml.c: mobi_search_links_kf7() scans a markup buffer forward
 * for a "filepos=" / "recindex=" attribute value with
 *   while (data <= data_end && !isspace(*data) && *data != tag_close && i < MOBI_ATTRVALUE_MAXSIZE)
 *       result->value[i++] = (char) *data++;
 * which correctly stops advancing `data` once it exceeds data_end -- but the
 * very next statement dereferences `*data` UNCONDITIONALLY whenever the last
 * copied byte was '/', with no `data <= data_end` guard. If the attribute
 * value runs all the way to the last byte of the buffer and that last byte
 * is '/', `data` becomes `data_end + 1` (one past the allocation) and the
 * self-closing-tag check reads one byte past the heap buffer.
 *
 * All type/macro definitions below are copied verbatim (field names, types,
 * values) from the real libmobi headers referenced by parse_rawml.c:
 *   - MOBI_RET (error codes)                        <- mobi.h
 *   - MOBIResult, MOBI_ATTRVALUE_MAXSIZE             <- parse_rawml.h
 *   - max(a,b)                                       <- util.h
 *   - debug_print (no-op unless MOBI_DEBUG, which the real build leaves off) <- debug.h
 *
 * main() mimics the real caller mobi_reconstruct_links_kf7() (parse_rawml.c):
 *     result.start = part->data;
 *     const unsigned char *data_end = part->data + part->size - 1;
 *     mobi_search_links_kf7(&result, result.start, data_end);
 * i.e. data_start/data_end bracket the EXACT bounds of a heap allocation
 * (part->data, an exact-size malloc of the rawml text), data_end pointing at
 * the LAST valid byte (inclusive), never past it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/* ---- mobi.h (verbatim subset) ---- */

typedef enum {
    MOBI_SUCCESS = 0, /**< Generic success return value */
    MOBI_ERROR = 1, /**< Generic error return value */
    MOBI_PARAM_ERR = 2, /**< Wrong function parameter */
    MOBI_DATA_CORRUPT = 3, /**< Corrupted data */
    MOBI_FILE_NOT_FOUND = 4, /**< File not found */
    MOBI_FILE_ENCRYPTED = 5, /**< Unsupported encrypted data */
    MOBI_FILE_UNSUPPORTED = 6, /**< Unsupported document type */
    MOBI_MALLOC_FAILED = 7, /**< Memory allocation error */
    MOBI_INIT_FAILED = 8, /**< Initialization error */
    MOBI_BUFFER_END = 9, /**< Out of buffer error */
    MOBI_XML_ERR = 10, /**< XMLwriter error */
    MOBI_DRM_PIDINV = 11,  /**< Invalid DRM PID */
    MOBI_DRM_KEYNOTFOUND = 12,  /**< Key not found */
    MOBI_DRM_UNSUPPORTED = 13, /**< DRM support not included */
    MOBI_WRITE_FAILED = 14, /**< Writing to file failed */
    MOBI_DRM_EXPIRED = 15, /**< DRM expired */
    MOBI_DRM_RANDOM_ERR = 16 /**< DRM random bytes generation failed */
} MOBI_RET;

/* ---- parse_rawml.h (verbatim subset) ---- */

#define MOBI_ATTRVALUE_MAXSIZE 150 /**< Maximum length of tag attribute value */

typedef struct {
    unsigned char *start; /**< Beginning data to be replaced */
    unsigned char *end; /**< End of data to be replaced */
    char value[MOBI_ATTRVALUE_MAXSIZE + 1]; /**< Attribute value */
    bool is_url; /**< True if value is part of css url attribute */
} MOBIResult;

/* ---- util.h (verbatim) ---- */

#define max(a, b) ((a) > (b) ? (a) : (b))

/* ---- debug.h (verbatim: MOBI_DEBUG is off in the real build, so this is a no-op) ---- */

#define debug_print(fmt, ...)

/* ================= target function, embedded verbatim ================= */

MOBI_RET mobi_search_links_kf7(MOBIResult *result, const unsigned char *data_start, const unsigned char *data_end) {
    if (!result) {
        debug_print("Result structure is null%s", "\n");
        return MOBI_PARAM_ERR;
    }
    result->start = result->end = NULL;
    *(result->value) = '\0';
    if (!data_start || !data_end) {
        debug_print("Data is null%s", "\n");
        return MOBI_PARAM_ERR;
    }
    const char *needle1 = "filepos=";
    const char *needle2 = "recindex=";
    const size_t needle1_length = strlen(needle1);
    const size_t needle2_length = strlen(needle2);
    const size_t needle_length = max(needle1_length,needle2_length);
    if (data_start + needle_length > data_end) {
        return MOBI_SUCCESS;
    }
    unsigned char *data = (unsigned char *) data_start;
    const unsigned char tag_open = '<';
    const unsigned char tag_close = '>';
    unsigned char last_border = tag_open;
    while (data <= data_end) {
        if (*data == tag_open || *data == tag_close) {
            last_border = *data;
        }
        if (data + needle_length <= data_end &&
            (memcmp(data, needle1, needle1_length) == 0 ||
             memcmp(data, needle2, needle2_length) == 0)) {
                /* found match */
                if (last_border != tag_open) {
                    /* opening char not found, not an attribute */
                    data += needle_length;
                    continue;
                }
                /* go to attribute  beginning */
                while (data >= data_start && !isspace(*data) && *data != tag_open) {
                    data--;
                }
                result->start = ++data;
                /* now go forward */
                int i = 0;
                while (data <= data_end && !isspace(*data) && *data != tag_close && i < MOBI_ATTRVALUE_MAXSIZE) {
                    result->value[i++] = (char) *data++;
                }
                /* self closing tag '/>' */
                if (*(data - 1) == '/' && *data == '>') {
                    --data; --i;
                }
                result->end = data;
                result->value[i] = '\0';
                return MOBI_SUCCESS;
            }
        data++;
    }
    return MOBI_SUCCESS;
}

/* ============================= harness main ============================= */

int
main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    long n = ftell(f);
    if (n < 0) { fclose(f); return 1; }
    rewind(f);

    if (n == 0) {
        /* nothing to parse -- mirrors the real caller, which never hands
         * mobi_search_links_kf7() a zero-size part->data allocation. */
        fclose(f);
        return 0;
    }

    /* HEAP buffer for the attacker-controlled markup text, sized EXACTLY to
     * the input file length -- exactly like the real caller's part->data,
     * an exact-size malloc'd rawml text buffer. This is what lets the
     * trailing '/' self-closing-tag check run one byte off the end of the
     * allocation when the attribute value runs all the way to the last
     * byte of the buffer. */
    unsigned char *buf = (unsigned char *)malloc((size_t)n);
    if (!buf) { fclose(f); return 1; }

    size_t got = fread(buf, 1, (size_t)n, f);
    fclose(f);
    if (got != (size_t)n) { free(buf); return 1; }

    MOBIResult result;
    memset(&result, 0, sizeof(result));

    /* Real caller (mobi_reconstruct_links_kf7):
     *   result.start = part->data;
     *   const unsigned char *data_end = part->data + part->size - 1;
     *   mobi_search_links_kf7(&result, result.start, data_end); */
    const unsigned char *data_start = buf;
    const unsigned char *data_end = buf + (size_t)n - 1;

    MOBI_RET rc = mobi_search_links_kf7(&result, data_start, data_end);
    (void)rc;

    free(buf);
    return 0;
}
