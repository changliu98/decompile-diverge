u8 __cdecl BS_ReadByte(GF_BitStream *bs)
{
    u8 next;
    Bool loc_eos;
    u8 res;
    
    // Memory-backed stream mode
    if ( !bs->bsmode )
    {
        if ( bs->position < bs->size )
        {
            res = bs->original[bs->position++];
            
            if ( bs->remove_emul_prevention_byte )
            {
                if ( bs->nb_zeros == 2 && res == 3 && bs->position < bs->size && bs->original[bs->position] < 4 )
                {
                    bs->nb_zeros = 0;
                    res = bs->original[bs->position++];
                }
                if ( res )
                    bs->nb_zeros = 0;
                else
                    ++bs->nb_zeros;
            }
            return res;
        }
        else
        {
            if ( bs->EndOfStream )
                bs->EndOfStream(bs->par);
            if ( !bs->overflow_state )
                bs->overflow_state = 1;
            return 0;
        }
    }

    // File-backed stream mode
    if ( bs->cache_write )
        bs_flush_write_cache(bs);

    if ( gf_feof(bs->stream) && !bs->cache_read )
        goto end_of_stream;

    loc_eos = GF_FALSE;
    if ( bs->position > bs->size )
        __assert_fail("bs->position<=bs->size", "/work/harness.c", 0xB6u, "u8 BS_ReadByte(GF_BitStream *)");

    ++bs->position;
    res = gf_bs_load_byte(bs, &loc_eos);

    if ( loc_eos )
    {
end_of_stream:
        if ( bs->EndOfStream )
        {
            bs->EndOfStream(bs->par);
            if ( !bs->overflow_state )
                bs->overflow_state = 1;
        }
        if ( bs->position > bs->size + 1 )
            __assert_fail("bs->position <= 1+bs->size", "/work/harness.c", 0xD4u, "u8 BS_ReadByte(GF_BitStream *)");
        return 0;
    }

    if ( bs->remove_emul_prevention_byte )
    {
        if ( bs->nb_zeros == 2 && res == 3 && bs->position < bs->size )
        {
            next = gf_bs_load_byte(bs, &loc_eos);
            if ( next >= 4 )
            {
                gf_bs_seek(bs, bs->position);
            }
            else
            {
                bs->nb_zeros = 0;
                res = next;
                ++bs->position;
            }
        }
        if ( res )
            bs->nb_zeros = 0;
        else
            ++bs->nb_zeros;
    }

    return res;
}