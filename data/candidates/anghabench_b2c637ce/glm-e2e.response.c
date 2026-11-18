int dac_lsb_4020_reg(int value) {
    return ((value & 1) << 2) + 0x70;
}