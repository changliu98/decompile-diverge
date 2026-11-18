uint32_t XXH32_round(uint32_t acc, uint32_t input) {
    acc += input * 0x85EBCA77;
    acc = (acc << 13) | (acc >> 19); // Rotate left by 13
    acc *= 0x9E3779B1;
    return acc;
}