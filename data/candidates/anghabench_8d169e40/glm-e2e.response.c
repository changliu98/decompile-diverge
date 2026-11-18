unsigned char fsp_test_invert_cmd(unsigned char cmd) {
    unsigned char inverted_cmd = cmd;
    
    if (cmd == 0xe9 || cmd == 0xee || cmd == 0xf2 || cmd == 0xff) {
        inverted_cmd = ~cmd;
    }
    
    return inverted_cmd;
}