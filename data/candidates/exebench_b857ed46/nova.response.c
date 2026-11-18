static void convert_human(size_t size, unsigned *out_e, char *out_unit) {
    unsigned e = 0;
    for (; size > 1024; size = (size + 512) / 1024) {
        e++;
    }
    unsigned i;
    for (i = e; i >= 5; i--) {
        size /= 1024;
    }
    switch (i) {
    case 4:
        *out_unit = 'G';
        break;
    case 3:
        *out_unit = 'M';
        break;
    case 2:
        *out_unit = 'K';
        break;
    case 1:
        *out_unit ='';
        break;
    case 0:
        *out_unit = 'B';
        break;
    default:
        *out_unit = 'T';
        break;
    }
    *out_e = e;
}