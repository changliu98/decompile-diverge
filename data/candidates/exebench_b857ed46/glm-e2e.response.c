void convert_human(unsigned long val, unsigned long *out_val, char *out_unit) {
    int i = 0;
    
    // Divide by 1024 until val is <= 1024 (0x400)
    while (val > 0x400) {
        val >>= 10; // Equivalent to val /= 1024
        i++;
    }
    
    // Assign the appropriate unit character based on the number of divisions
    switch (i) {
        case 0:
            *out_unit = ' '; // 0x20
            break;
        case 1:
            *out_unit = 'K'; // 0x4B
            break;
        case 2:
            *out_unit = 'M'; // 0x4D
            break;
        case 3:
            *out_unit = 'G'; // 0x47
            break;
        case 4:
            *out_unit = 'T'; // 0x54
            break;
        case 5:
            *out_unit = 'P'; // 0x50
            break;
        default:
            break;
    }
    
    // Store the scaled value into the output pointer
    *out_val = val;
}