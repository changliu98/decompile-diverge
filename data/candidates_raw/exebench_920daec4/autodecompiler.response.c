void encode_symbol(unsigned int symbol1, unsigned int symbol2,
                   int order, struct SYMBOL *sym)
{
    int state = 0;
    int i = 0;
    int index;

    for (i = order - 1; i >= 0; i--) {
        index = (state << 2) | (((symbol1 >> i) & 1) << 1) | ((symbol2 >> i) & 1);
        sym->index = (sym->index << 2) | ((0x361e9cb4 >> (index << 1)) & 3);
        state = (0x8fe65831 >> (index << 1)) & 3;
    }
}