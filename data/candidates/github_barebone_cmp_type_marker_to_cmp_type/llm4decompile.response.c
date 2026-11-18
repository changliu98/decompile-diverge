bool type_marker_to_cmp_type(uint8_t type_marker, uint8_t *cmp_type)
{
    if (type_marker < 0x80) {
        *cmp_type = 0;
        return true;
    } else if (type_marker < 0x90) {
        *cmp_type = 1;
        return true;
    } else if (type_marker < 0xa0) {
        *cmp_type = 2;
        return true;
    } else if (type_marker < 0xc0) {
        *cmp_type = 3;
        return true;
    } else if (type_marker < 0xe0) {
        switch (type_marker) {
        case 0xc0:
            *cmp_type = 4;
            return true;
        case 0xc1:
            return false;
        case 0xc2:
            *cmp_type = 5;
            return true;
        case 0xc3:
            *cmp_type = 5;
            return true;
        case 0xc4:
            *cmp_type = 6;
            return true;
        case 0xc5:
            *cmp_type = 7;
            return true;
        case 0xc6:
            *cmp_type = 8;
            return true;
        case 0xc7:
            return false;
        case 0xc8:
            return false;
        case 0xc9:
            *cmp_type = 9;
            return true;
        case 0xca:
            *cmp_type = 10;
            return true;
        case 0xcb:
            *cmp_type = 11;
            return true;
        case 0xcc:
            *cmp_type = 12;
            return true;
        case 0xcd:
            *cmp_type = 13;
            return true;
        case 0xce:
            *cmp_type = 14;
            return true;
        case 0xcf:
            *cmp_type = 15;
            return true;
        case 0xd0:
            *cmp_type = 16;
            return true;
        case 0xd1:
            *cmp_type = 17;
            return true;
        case 0xd2:
            *cmp_type = 18;
            return true;
        case 0xd3:
            *cmp_type = 19;
            return true;
        case 0xd4:
            *cmp_type = 20;
            return true;
        case 0xd5:
            *cmp_type = 21;
            return true;
        case 0xd6:
            *cmp_type = 22;
            return true;
        case 0xd7:
            *cmp_type = 23;
            return true;
        case 0xd8:
            *cmp_type = 24;
            return true;
        case 0xd9:
            *cmp_type = 25;
            return true;
        case 0xda:
            *cmp_type = 26;
            return true;
        case 0xdb:
            *cmp_type = 27;
            return true;
        case 0xdc:
            *cmp_type = 28;
            return true;
        case 0xdd:
            *cmp_type = 29;
            return true;
        case 0xde:
            *cmp_type = 30;
            return true;
        case 0xdf:
            *cmp_type = 31;
            return true;
        }
    } else {
        *cmp_type = 32;
        return true;
    }
    return false;
}