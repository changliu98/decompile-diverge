/* Direct-call crash harness for pdfgen jpeg_size (CVE-2018-11363, CWE-125).
 *
 * jpeg_size() is a self-contained function: unsigned char* buffer + unsigned
 * int length in, two int* out-params. No struct/typedef dependencies beyond
 * plain C types, so it is embedded verbatim with no supporting definitions.
 *
 * main() mimics the real caller (pdf_add_raw_jpeg() in pdfgen.c): it reads
 * the whole input file into a malloc'd heap buffer sized EXACTLY to the file
 * length (no over-allocation slack) and calls jpeg_size(data, len, &w, &h)
 * once, directly. Any out-of-bounds byte access inside jpeg_size's JPEG
 * marker walk then reads past the end of the heap allocation and ASAN
 * reports a heap-buffer-overflow READ, matching CWE-125.
 */
#include <stdio.h>
#include <stdlib.h>

/* ---- verbatim target function (target/original_function.c) ---- */
static int jpeg_size(unsigned char* data, unsigned int data_size,
                     int *width, int *height)
{
    int i = 0;
    if (i + 3 < data_size && data[i] == 0xFF && data[i+1] == 0xD8 &&
            data[i+2] == 0xFF && data[i+3] == 0xE0) {
        i += 4;
        if(i + 6 < data_size &&
                data[i+2] == 'J' && data[i+3] == 'F' && data[i+4] == 'I' &&
                data[i+5] == 'F' && data[i+6] == 0x00) {
            unsigned short block_length = data[i] * 256 + data[i+1];
            while(i<data_size) {
                i+=block_length;
                if((i + 1) >= data_size)
                    return -1;
                if(data[i] != 0xFF)
                    return -1;
                if(data[i+1] == 0xC0) {
                    *height = data[i+5]*256 + data[i+6];
                    *width = data[i+7]*256 + data[i+8];
                    return 0;
                }
                i+=2;
                block_length = data[i] * 256 + data[i+1];
            }
        }
    }

    return -1;
}
/* ---- end verbatim target function ---- */

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

    /* Heap buffer, sized to EXACTLY the file length (no slack) so ASAN's
     * redzone sits immediately after the real data, mirroring pdfgen's
     * jpeg_data = malloc(len) in pdf_add_raw_jpeg(). */
    unsigned char *data = malloc((size_t)len > 0 ? (size_t)len : 1);
    if (!data) {
        perror("malloc");
        fclose(fp);
        return 1;
    }
    if (len > 0 && fread(data, (size_t)len, 1, fp) != 1) {
        fprintf(stderr, "short read\n");
        fclose(fp);
        free(data);
        return 1;
    }
    fclose(fp);

    int width = 0, height = 0;
    int rc = jpeg_size(data, (unsigned int)len, &width, &height);

    printf("jpeg_size rc=%d width=%d height=%d\n", rc, width, height);

    free(data);
    return 0;
}
