pj_status_t get_name_len( int rec_counter,
                                 pj_uint8_t *pkt,
                                 pj_uint8_t *start,
                                 pj_uint8_t *max,
                                 int *parsed_len,
                                 int *name_len )
{
    pj_uint8_t *p;
    pj_uint16_t offset;
    int label_len;
    int ptr_len;
    pj_status_t status;


    if( rec_counter > 10 )
        return 313355;


    if( start >= max )
        return 313355;

    *parsed_len = 0;
    *name_len = 0;

    p = start;
    while( *p != '\0' )
    {
        if( (*p & 0xC0) == 0xC0 )
        {
            ptr_len = 0;
            pj_memcpy(&offset, p, 2);
            offset = pj_ntohs(offset ^ pj_htons(0xC000));

            if( offset >= (max - pkt) )
                return 313355;

            status = get_name_len( ++rec_counter,
                                   pkt,
                                   pkt + offset,
                                   max,
                                   &label_len,
                                   &ptr_len );
            if( status != 0 )
                return status;

            *parsed_len += 2;
            *name_len += ptr_len;
            break;
        }
        else
        {
            label_len = *p;

            if( p + label_len + 2 > max )
                return 313355;

            p += label_len + 1;
            *parsed_len += label_len + 1;

            if( *p != '\0' )
                label_len++;

            *name_len += label_len;
        }
    }

    if( *p == '\0' )
        *parsed_len += 1;

    return 0;
}