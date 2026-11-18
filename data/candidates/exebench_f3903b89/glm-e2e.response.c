void get_payload_info(struct payload *p, uint32_t *size, uint32_t *count) {
    uint8_t val = (uint8_t)(p->offset_1f1 + 1);
    uint32_t shifted = (uint32_t)val << 9;
    
    *size = p->offset_248 + shifted;
    *count = p->offset_24c;
}