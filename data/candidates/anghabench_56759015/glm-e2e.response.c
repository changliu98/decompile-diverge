int dac_convert_reg(int arg) {
    return ((arg & 1) << 1) + 0x70;
}