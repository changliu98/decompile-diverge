int ether_hash(const uint8_t *addr) {
    int hash = 0;
    for (int i = 0; i < 6; i++) {
        hash = (hash << 6) + (hash << 10) - hash + addr[i];
    }
    return hash;
}