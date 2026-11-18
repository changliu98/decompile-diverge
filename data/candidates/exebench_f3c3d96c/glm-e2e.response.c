void nist_increment_block(uint32_t *block) {
    for (int i = 3; i >= 0; i--) {
        uint32_t val = ntohl(block[i]);
        val += 1;
        block[i] = htonl(val);
        
        if (val != 0) {
            break;
        }
    }
}