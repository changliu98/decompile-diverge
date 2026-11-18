bool clip_img(int x, int y, int w, int h, int *x_ptr, int *y_ptr, 
              int *w_ptr, int *h_ptr, int stride_x, int stride_y) {
    // x is in -0x4(%rbp) (edi)
    // y is in -0x8(%rbp) (esi)
    // w is in -0xc(%rbp) (edx)
    // h is in -0x10(%rbp) (ecx)
    // x_ptr is in -0x18(%rbp) (r8)
    // y_ptr is in -0x20(%rbp) (r9)
    // w_ptr is at 0x10(%rbp)
    // h_ptr is at 0x18(%rbp)
    // stride_x is at 0x20(%rbp)
    // stride_y is at 0x28(%rbp)
    // offset_x is at 0x30(%rbp)
    // offset_y is at 0x38(%rbp)

    if (*x_ptr < x) {
        *w_ptr -= x - *x_ptr;
        *stride_x += (x - *x_ptr) * offset_x;
        *x_ptr = x;
    }

    if (*w_ptr > w - *x_ptr + 1) {
        *w_ptr = w - *x_ptr + 1;
    }

    if (*y_ptr < y) {
        *h_ptr -= y - *y_ptr;
        *stride_y += (y - *y_ptr) * offset_y;
        *y_ptr = y;
    }

    if (*h_ptr > h - *y_ptr + 1) {
        *h_ptr = h - *y_ptr + 1;
    }

    return (*w_ptr >= 0) && (*h_ptr >= 0);
}