static enum _pj_status_t parseName(int rec_counter, unsigned char *pkt, unsigned char *start, unsigned char *end, int *parsed_len, int *name_len)
{
    int label_len;
    int ptr_len;
    int offset;
    int dummy;
    unsigned char *p;
    enum _pj_status_t status;
    if (rec_counter > 10)
    {
        return (PJ_ST_NET_DNS_RECURSION_LIMIT);
    }
    *parsed_len = 0;
    *name_len = 0;
    for (p = start; *p != 0; )
    {
        if ((unsigned char)(*p & 0xc0) == 0xc0)
        {
            ptr_len = 0;
            get_unaligned_16((unsigned char *)&offset, p, sizeof(offset));
            offset ^= 0xc000;
            offset = foldCase(offset);
            if (offset + (int)pkt > (int)end)
            {
                return (PJ_ST_NET_DNS_RECURSION_LIMIT);
            }
            status = parseName(rec_counter + 1, pkt, pkt + offset, end, &dummy, &ptr_len);
            if (status != PJ_SUCCESS)
            {
                return (status);
            }
            *parsed_len += sizeof(offset);
            *name_len += ptr_len;
            return (PJ_SUCCESS);
        }
        label_len = *p;
        if (label_len + (int)p > (int)end)
        {
            return (PJ_ST_NET_DNS_RECURSION_LIMIT);
        }
        p += (label_len + 1);
        *parsed_len += (label_len + 1);
        if (*p != 0)
        {
            label_len++;
        }
        *name_len += label_len;
        if (p >= end)
        {
            return (PJ_ST_NET_DNS_INCONSISTENT);
        }
    }
    p++;
    (*parsed_len)++;
    return (PJ_SUCCESS);
}