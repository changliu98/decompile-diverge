int obdRevConvert_21(uint32_t raw, uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d)
{
    *a = (uint8_t)(raw / 256);
    *b = (uint8_t)(raw % 256);
    return 2;
}