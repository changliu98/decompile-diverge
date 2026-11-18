void read_quant_matrix_ext(struct MpegEncContext *s, struct GetBitContext *gb)
{
    int i; int j;
    unsigned short val;
    if (ff_get_block_type(gb))
    {
        for (i = 0; i < 64; i++)
        {
            val = ff_get_uexp(gb, 8);
            j = s->idsp.idct_permutation[ff_zigzag_direct[i]];
            s->intra_matrix[s->idsp.idct_permutation[ff_zigzag_direct[i]]] = val;
            s->chroma_intra_matrix[j] = val;
        }
    }
    if (ff_get_block_type(gb))
    {
        for (i = 0; i < 64; i++)
            ff_get_uexp(gb, 8);
    }
    if (ff_get_block_type(gb))
    {
        for (i = 0; i < 64; i++)
        {
            val = ff_get_uexp(gb, 8);
            j = s->idsp.idct_permutation[ff_zigzag_direct[i]];
            s->chroma_intra_matrix[s->idsp.idct_permutation[ff_zigzag_direct[i]]] = val;
        }
    }
    if (ff_get_block_type(gb))
    {
        for (i = 0; i < 64; i++)
            ff_get_uexp(gb, 8);
    }
    ff_get_block_type(gb);
}