void __cdecl print_udta(GF_ISOFile *file, u32 track_number, Bool has_itags)
{
    u32 udta_size;
    u8 *udta;
    bin128 uuid;
    bin128 uuid_0;
    u32 type;
    u32 type_0;
    u32 first;
    u32 nb_items;
    u32 j;
    u32 count;
    u32 i;

    count = gf_isom_get_udta_count(file, track_number);
    if (!count)
        return;

    if (has_itags != GF_FALSE)
    {
        for (i = 0; i < count; ++i)
        {
            gf_isom_get_udta_type(file, track_number, i + 1, &type, (bin128 *)uuid);
            if (type == 1835365473) // 'itags' in little-endian (0x6D646574)
            {
                --count;
                break;
            }
        }
        if (!count)
            return;
    }

    fprintf(stderr, "%d UDTA types: ", count);
    for (i = 0; i < count; ++i)
    {
        first = 1;
        gf_isom_get_udta_type(file, track_number, i + 1, &type_0, (bin128 *)uuid_0);
        nb_items = gf_isom_get_user_data_count(file, track_number, type_0, uuid_0);
        
        fprintf(stderr, "%s (%d) ", gf_4cc_to_str(type_0), nb_items);
        
        for (j = 0; j < nb_items; ++j)
        {
            udta = NULL;
            gf_isom_get_user_data(file, track_number, type_0, uuid_0, j + 1, &udta, &udta_size);
            if (udta)
            {
                if (gf_utf8_is_legal(udta, udta_size))
                {
                    if (first)
                    {
                        fprintf(stderr, "\n");
                        first = 0;
                    }
                    fprintf(stderr, "\t%s\n", (const char *)udta);
                }
                gf_free(udta);
            }
        }
    }
    fprintf(stderr, "\n");
}