void func0(Bitmap *b, unsigned long value) {
    size_t i;

    if (b->words == 0 || value == 1)
        return;

    if (value == 0) {
        bitmap_zero(b);
        return;
    }

    for (i = b->words; i > 0; i--) {
        if (b->word[i - 1] & ((BITMAP_WORD_TYPE)1 << (i - 1))) {
            b->word[i - 1] &= ~((BITMAP_WORD_TYPE)1 << (i - 1));
            bitmap_set(b, i - 1, value);
        }
    }
}