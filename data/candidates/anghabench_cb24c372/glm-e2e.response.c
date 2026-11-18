int alps_check_valid_firmware_id(unsigned char *id) {
    if (id[0] == 0x73) {
        return 1;
    } else if (id[0] == 0x88) {
        if (id[1] == 0x07 || id[1] == 0x08 || (id[1] & 0xF0) == 0xB0 || (id[1] & 0xF0) == 0xC0) {
            return 1;
        }
    }
    
    return 0;
}