void jpc_qmfb_split_colgrp(void *a, int start, int height, int stride) {
    int buf_max_size = (start + 2 - 1) >> 1;
    long long buf[0x1000]; // Stack allocated buffer
    long long *bufptr = buf;

    // Allocate dynamically if the required buffer size exceeds the stack limit
    if (buf_max_size > 0x1000) {
        bufptr = jas_alloc2(buf_max_size, 8);
        if (!bufptr) {
            abort();
        }
    }

    if (start >= 2) {
        int h0 = (start + 1 - height) >> 1;
        int h1 = start - h0;
        int i = h1;
        long long *src = (long long *)((char *)a + (1 - height) * stride * 8);
        
        // First loop: Copy elements to the buffer
        while (i > 0) {
            long long *p1 = bufptr;
            long long *p2 = src;
            int j = 0;
            while (j < 16) {
                *p1 = *p2;
                p1++;
                p2++;
                j++;
            }
            bufptr += 16;
            src = (long long *)((char *)src + (stride * 2 * 8));
            i--;
        }

        long long *p1 = (long long *)((char *)a + (1 - height) * stride * 8);
        long long *p2 = (long long *)((char *)a + (2 - height) * stride * 8);
        i = start - h1 - (height != 0 ? 0 : 1);
        
        // Second loop: Interleave elements within the array
        while (i > 0) {
            long long *p3 = p1;
            long long *p4 = p2;
            int j = 0;
            while (j < 16) {
                *p3 = *p4;
                p3++;
                p4++;
                j++;
            }
            p1 = (long long *)((char *)p1 + stride * 8);
            p2 = (long long *)((char *)p2 + stride * 2 * 8);
            i--;
        }

        long long *p3 = (long long *)((char *)a + h0 * stride * 8);
        long long *p4 = buf;
        i = h1;
        
        // Third loop: Copy elements back from the buffer
        while (i > 0) {
            long long *p5 = p3;
            long long *p6 = p4;
            int j = 0;
            while (j < 16) {
                *p5 = *p6;
                p5++;
                p6++;
                j++;
            }
            p3 = (long long *)((char *)p3 + stride * 8);
            p4 += 16;
            i--;
        }
    }

    // Free dynamically allocated memory if it was used
    if (bufptr != buf) {
        jas_free(bufptr);
    }
}