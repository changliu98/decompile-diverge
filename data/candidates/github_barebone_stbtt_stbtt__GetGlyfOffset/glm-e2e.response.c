int stbtt__GetGlyfOffset(const void *info, int glyph_index) {
    const struct stbtt_fontinfo *font = (const struct stbtt_fontinfo *)info;

    if (font->cff == 0) {
        stbtt__assert_("font->cff != 0", "stbtt__GetGlyfOffset", 0x647);
    }

    if (glyph_index >= font->numGlyphs) {
        return -1;
    }

    if (font->indexToLocFormat >= 2) {
        return -1;
    }

    int g1, g2;

    if (font->indexToLocFormat == 0) {
        g1 = font->loca + ttUSHORT(font->data + font->loca + glyph_index * 2) * 2;
        g2 = font->loca + ttUSHORT(font->data + font->loca + glyph_index * 2 + 2) * 2;
    } else {
        g1 = font->loca + ttLONG(font->data + font->loca + glyph_index * 4);
        g2 = font->loca + ttLONG(font->data + font->loca + glyph_index * 4 + 4);
    }

    if (g1 == g2) {
        return -1;
    }

    return g1;
}