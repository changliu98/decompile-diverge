/*
 * Direct-call crash harness for CVE-2020-28840 (jhead, process_COM).
 *
 * Upstream bug (jpgfile.c, process_COM): the comment-marker parser walks the
 * COM-segment payload with
 *
 *     for (a=2;a<length;a++){
 *         ch = Data[a];
 *         if (ch == '\r' && Data[a+1] == '\n') continue;   // <-- unchecked a+1
 *         ...
 *     }
 *
 * `Data` is malloc'd by the REAL caller (ReadJpegSections, jpgfile.c) to
 * EXACTLY `itemlen` bytes -- `Data = malloc(itemlen); ... process_COM(Data,
 * itemlen);` -- so the loop's own bound `a < length` is the only thing
 * standing between `Data[a]` and the end of the allocation. On the LAST loop
 * iteration (a == length-1), if that final byte is '\r' the short-circuited
 * `Data[a+1] == '\n'` check reads `Data[length]`, one byte past the
 * malloc(length) allocation -> heap-buffer-overflow READ (CWE-125). This is
 * the exact baseline: dedup_token "process_COM--ReadJpegSections--
 * ReadJpegFile", "AddressSanitizer: heap-buffer-overflow ./jpgfile.c:51:27
 * in process_COM" (line 51 == the `Data[a+1] == '\n'` read), access READ.
 *
 * process_COM() is embedded verbatim below (byte-identical to
 * target/original_function.c). The preceding definitions are a
 * minimal-but-real subset of jhead.h: `uchar` (jhead.h:41), MAX_COMMENT_SIZE
 * (jhead.h:48, 16000), and ImageInfo_t trimmed to the one field process_COM
 * touches (`Comments[MAX_COMMENT_SIZE]`, jhead.h:122) plus the real global
 * storage declaration `ImageInfo_t ImageInfo;` (jpgfile.c:12) and `extern int
 * ShowTags;` (jhead.h:239, defined here mirroring jhead.c's `int ShowTags =
 * FALSE;` default). No callees need stubbing: process_COM's only calls are
 * printf() (guarded by ShowTags==0, so never taken) and strcpy() into
 * ImageInfo.Comments, both real libc.
 *
 * main() reads argv[1] into a HEAP buffer sized to EXACTLY the file length
 * (this is what lets ASAN's redzone catch the a+1 read past it) and calls
 * process_COM(buf, n) -- mirroring the real call site
 * `Data = malloc(itemlen); process_COM(Data, itemlen)` exactly (n IS the
 * allocation size, exactly as itemlen is).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- jhead.h (verbatim subset) ---- */

typedef unsigned char uchar;

#define MAX_COMMENT_SIZE 16000

/* Trimmed to the one field process_COM touches; real name/size (jhead.h:122). */
typedef struct {
    char  Comments[MAX_COMMENT_SIZE];
}ImageInfo_t;

/* Real global storage (jpgfile.c:12). */
ImageInfo_t ImageInfo;

/* Real extern (jhead.h:239), defined here mirroring jhead.c's default (FALSE). */
int ShowTags = 0;

/* ================= target function, embedded VERBATIM (byte-identical to
 * target/original_function.c) ================= */

static void process_COM (const uchar * Data, int length)
{
    int ch;
    char Comment[MAX_COMMENT_SIZE+1];
    int nch;
    int a;

    nch = 0;

    if (length > MAX_COMMENT_SIZE) length = MAX_COMMENT_SIZE; // Truncate if it won't fit in our structure.

    for (a=2;a<length;a++){
        ch = Data[a];

        if (ch == '\r' && Data[a+1] == '\n') continue; // Remove cr followed by lf.

        if (ch >= 32 || ch == '\n' || ch == '\t'){
            Comment[nch++] = (char)ch;
        }else{
            Comment[nch++] = '?';
        }
    }

    Comment[nch] = '\0'; // Null terminate

    if (ShowTags){
        printf("COM marker comment: %s\n",Comment);
    }

    strcpy(ImageInfo.Comments,Comment);
}

/* ============================= harness main ============================= */

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        perror("fseek");
        fclose(fp);
        return 1;
    }
    long len = ftell(fp);
    if (len < 0) {
        perror("ftell");
        fclose(fp);
        return 1;
    }
    rewind(fp);

    /* Heap buffer, sized to EXACTLY the file length (no slack) -- mirrors the
     * real caller's `Data = malloc(itemlen)` exactly, itemlen == length. */
    size_t alloc_len = (size_t)len > 0 ? (size_t)len : 1;
    uchar *data = (uchar *)malloc(alloc_len);
    if (!data) {
        perror("malloc");
        fclose(fp);
        return 1;
    }
    if (len > 0) {
        size_t got = fread(data, 1, (size_t)len, fp);
        fclose(fp);
        if (got != (size_t)len) {
            free(data);
            return 1;
        }
    } else {
        fclose(fp);
    }

    process_COM(data, (int)len);

    free(data);
    return 0;
}
