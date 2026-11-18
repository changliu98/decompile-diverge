uint16_t BigUnsignedShort(uint16_t value) {
    uint16_t var = value;
    uint32_t low = var & 0xFF;
    uint32_t high = (var >> 8) & 0xFF;
    
    return (uint16_t)((low << 8) + high);
}