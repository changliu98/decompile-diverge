bool type_marker_to_cmp_type(uint8_t type_marker, uint8_t *cmp_type) {
    if (type_marker <= 0x7f) {
        *cmp_type = 0x0;
        return true;
    } else if (type_marker <= 0x8f) {
        *cmp_type = 0x1;
        return true;
    } else if (type_marker <= 0x9f) {
        *cmp_type = 0x2;
        return true;
    } else if (type_marker <= 0xbf) {
        *cmp_type = 0x3;
        return true;
    } else if (type_marker >= 0xe0) {
        *cmp_type = 0x22;
        return true;
    } else {
        // Covers the range 0xC0 to 0xDF
        switch (type_marker - 0xa0) {
            case 0x20: *cmp_type = 0x4;  return true;
            case 0x21: *cmp_type = 0x5;  return true;
            case 0x22: *cmp_type = 0x5;  return true;
            case 0x23: *cmp_type = 0x6;  return true;
            case 0x24: *cmp_type = 0x7;  return true;
            case 0x25: *cmp_type = 0x8;  return true;
            case 0x26: *cmp_type = 0x9;  return true;
            case 0x27: *cmp_type = 0xa;  return true;
            case 0x28: *cmp_type = 0xb;  return true;
            case 0x29: *cmp_type = 0xc;  return true;
            case 0x2a: *cmp_type = 0xd;  return true;
            case 0x2b: *cmp_type = 0xe;  return true;
            case 0x2c: *cmp_type = 0xf;  return true;
            case 0x2d: *cmp_type = 0x10; return true;
            case 0x2e: *cmp_type = 0x11; return true;
            case 0x2f: *cmp_type = 0x12; return true;
            case 0x30: *cmp_type = 0x13; return true;
            case 0x31: *cmp_type = 0x14; return true;
            case 0x32: *cmp_type = 0x15; return true;
            case 0x33: *cmp_type = 0x16; return true;
            case 0x34: *cmp_type = 0x17; return true;
            case 0x35: *cmp_type = 0x18; return true;
            case 0x36: *cmp_type = 0x19; return true;
            case 0x37: *cmp_type = 0x1a; return true;
            case 0x38: *cmp_type = 0x1b; return true;
            case 0x39: *cmp_type = 0x1c; return true;
            case 0x3a: *cmp_type = 0x1d; return true;
            case 0x3b: *cmp_type = 0x1e; return true;
            case 0x3c: *cmp_type = 0x1f; return true;
            case 0x3d: *cmp_type = 0x20; return true;
            case 0x3e: *cmp_type = 0x21; return true;
            // No default case is needed because the bounds check 
            // (type_marker <= 0xbf and type_marker >= 0xe0) guarantees 
            // the switch variable is between 0x20 and 0x3f.
        }
    }
    
    return false;
}