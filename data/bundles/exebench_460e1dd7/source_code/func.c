




















void BinaryFiles__swap_bytes32(unsigned int *value) {
    unsigned int result = (((*value & 0xff) << 24) +
                            ((*value & 0xff00) << 8) +
                            ((*value & 0xff0000) >> 8) +
                            ((*value & 0xff000000) >> 24 ) );
    *value = result;
}
