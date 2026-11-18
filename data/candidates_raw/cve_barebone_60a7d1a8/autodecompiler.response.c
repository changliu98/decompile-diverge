int ZBarcode_Buffer(struct zint_symbol *symbol, size_t length, struct zint_buffer *buffer) {
    int error_number;
    unsigned short i;
    unsigned short j;
    unsigned short k;
    unsigned short p;
    unsigned short e;
    unsigned short c;
    unsigned short d;
    unsigned short n;
    unsigned short o;
    unsigned short m;
    unsigned short l;
s100:
    buffer->source = symbol;
    i = __ZL8foldCaset(buffer->source->symbology);
    switch (i) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 32:
            break;
        default:
            goto s101;
    }
    j = __ZL8foldCaset(buffer->source->height);
    if (j != (unsigned short)(length - 20)) {
        goto s101;
    }
    buffer->rows = 0;
    p = 20;
s102:
    if (j > 0) {
        k = (unsigned short)(buffer->rows + 1);
        buffer->row_pointer[k] = &symbol->bitmap_data[p];
        l = __ZL8foldCaset(buffer->row_pointer[k][2]) + 4;
        l = (unsigned short)((l + 3) & ~3);
        if (j < l) {
            goto s103;
        }
        m = __ZL8foldCaset(buffer->row_pointer[k][0]);
        switch (m) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 32:
                break;
            default:
                goto s104;
        }
        j = (unsigned short)(j - l);
        p = (unsigned short)(p + l);
        buffer->rows++;
        goto s102;
    }
    goto s105;
s103:
    error_number = 314;
    goto s106;
s104:
    error_number = 315;
    goto s106;
s105:
    error_number = 0;
s106:
    return error_number;
s101:
    error_number = 313;
    goto s106;
}