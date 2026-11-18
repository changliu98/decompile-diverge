pj_status_t get_name_len( int rec_counter,
                                 pj_uint8_t *pkt,
                                 pj_uint8_t *start,
                                 pj_uint8_t *max,
                                 int *parsed_len,
                                 int *name_len)
{
    pj_uint8_t *p;
    pj_uint16_t offset;
    int label_len;
    int ptr_len;
    int dummy;
    pj_status_t status;


    if (rec_counter > 10)
        return 313387;

    *parsed_len = 0;
    *name_len = 0;


    for (p = start; *p != '\0';) {

        if ((*p & 0xc0) == 0xc0) {
            ptr_len = 0;
            pj_memcpy(&offset, p, 2);
            offset = pj_ntohs(offset ^ pj_htons(0xc000));
            if (pkt + offset >= max)
                return 313387;

            status = get_name_len(++rec_counter, pkt, pkt + offset,
                                  max, &dummy, &ptr_len);
            if (status != 0)
                return status;

            *parsed_len += 2;
            *name_len += ptr_len;
            break;
        }


        label_len = *p;
        if (pkt + label_len > max)
            return 313387;

        p += label_len + 1;
        *parsed_len += label_len + 1;
        if (*p != '\0')
            label_len++;
        *name_len += label_len;

        if (p >= max)
            return 313385;
    }

    if (*p == '\0')
        *parsed_len += 1;

    return 0;
}