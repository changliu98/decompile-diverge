bool nsgif__deinterlace(uint32_t height, uint32_t *row, uint8_t *pass) {
    *row += *pass & 0xf;

    if (*row >= height) {
        return true;
    }

    switch (*pass) {
        case 0x4:
            *row = 1;
            *pass = 2;
            break;
        case 0x8:
            *row = 2;
            *pass = 4;
            break;
        case 0x18:
            *row = 4;
            *pass = 8;
            break;
        default:
            return false;
    }

    if (*row >= height) {
        return true;
    }

    return false;
}