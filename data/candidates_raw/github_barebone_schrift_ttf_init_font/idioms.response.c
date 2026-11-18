int sft_read_head(struct SFT_Font *font)
{
    struct SFT_Font *f = font;
    unsigned int scalerType;
    unsigned int head;
    unsigned int hhea;
    if (sft_read_table(f, ((void *)0), 12) == ((void *)0))
        return -1;
    scalerType = sft_get_uint32(f, ((void *)0));
    if (scalerType != 0x10000 && scalerType != 0x74727065)
        return -1;
    if (sft_read_table(f, "head", &head) < 0)
        return -1;
    if (sft_read_table(f, head, 54) == ((void *)0))
        return -1;
    f->unitsPerEm = sft_get_uint16(f, head + 18);
    f->locaFormat = sft_get_int16(f, head + 50);
    if (sft_read_table(f, "hhea", &hhea) < 0)
        return -1;
    if (sft_read_table(f, hhea, 36) == ((void *)0))
        return -1;
    f->numLongHmtx = sft_get_uint16(f, hhea + 34);
    return 0;
}