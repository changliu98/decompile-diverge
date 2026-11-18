int pjstun_parse_msg(void *data, unsigned long data_len, struct pjstun_msg *msg)
{
    struct pjstun_msg_hdr *hdr = (pjstun_msg_hdr *)data;
    char *attr_data = (char *)data + sizeof(pjstun_msg_hdr);
    unsigned int msg_len = (data_len - sizeof(pjstun_msg_hdr));
    int type = foldCase(hdr->type);
    int attr_len;
    if (type != 0x0001 &&
        type != 0x0002 &&
        type != 0x0003 &&
        type != 0x0101 &&
        type != 0x0103 &&
        type != 0x0111 &&
        type != 0x0113 &&
        type != 0x0201 &&
        type != 0x0203 &&
        type != 0x0211 &&
        type != 0x0213 &&
        type != 0x0301 &&
        type != 0x0303 &&
        type != 0x0311 &&
        type != 0x0313 )
        return (320002);
    if (msg_len != foldCase(hdr->length))
        return (320003);
    msg->attr_count = 0;
    while (msg_len > 0)
    {
        struct pjstun_attr_hdr **attr = &msg->attr[msg->attr_count];
        *attr = (struct pjstun_attr_hdr *)attr_data;
        attr_len = (foldCase((*attr)->length) + 3) & ~3;
        if (msg_len < attr_len)
            return (320004);
        if (type == 0x0001 ||
            type == 0x0101 ||
            type == 0x0201 ||
            type == 0x0301)
        {
            if (type == 0x0101 ||
                type == 0x0201 ||
                type == 0x0301)
            {
                if (attr_len == sizeof(struct pjstun_attr_hdr))
                {
                    struct pjstun_attr_hdr *attr_hdr = (pjstun_attr_hdr *)attr;
                    if (type == 0x0101)
                    {
                        if (attr_hdr->type == 0x0001 ||
                            attr_hdr->type == 0x0002 ||
                            attr_hdr->type == 0x0003 ||
                            attr_hdr->type == 0x0101 ||
                            attr_hdr->type == 0x0103 ||
                            attr_hdr->type == 0x0111 ||
                            attr_hdr->type == 0x0113 ||
                            attr_hdr->type == 0x0201 ||
                            attr_hdr->type == 0x0203 ||
                            attr_hdr->type == 0x0211 ||
                            attr_hdr->type == 0x0213 ||
                            attr_hdr->type == 0x0301 ||
                            attr_hdr->type == 0x0303 ||
                            attr_hdr->type == 0x0311 ||
                            attr_hdr->type == 0x0313 )
                        {
                            if (attr_len == sizeof(struct pjstun_attr_hdr))
                            {
                                *attr = (struct pjstun_attr_hdr *)attr;
                                if (type == 0x0101)
                                    return (320001);
                            }
                        }
                    }
                }
            }
        }
        if (type == 0x0103 ||
            type == 0x0203 ||
            type == 0x0303)
        {
            if (type == 0x0103 ||
                type == 0x0203 ||
                type == 0x0303)
            {
                if (attr_len == sizeof(struct pjstun_attr_hdr))
                {
                    struct pjstun_attr_hdr *attr_hdr = (pjstun_attr_hdr *)attr;
                    if (type == 0x0103)
                    {
                        if (attr_hdr->type == 0x0001 ||
                            attr_hdr->type == 0x0002 ||
                            attr_hdr->type == 0x0003 ||
                            attr_hdr->type == 0x0101 ||
                            attr_hdr->type == 0x0103 ||
                            attr_hdr->type == 0x0111 ||
                            attr_hdr->type == 0x0113 ||
                            attr_hdr->type == 0x0201 ||
                            attr_hdr->type == 0x0203 ||
                            attr_hdr->type == 0x0211 ||
                            attr_hdr->type == 0x0213 ||
                            attr_hdr->type == 0x0301 ||
                            attr_hdr->type == 0x0303 ||
                            attr_hdr->type == 0x0311 ||
                            attr_hdr->type == 0x0313 )
                        {
                            if (attr_len == sizeof(struct pjstun_attr_hdr))
                            {
                                *attr = (struct pjstun_attr_hdr *)attr;
                                if (type == 0x0103)
                                    return (320001);
                            }
                        }
                    }
                }
            }
        }
        if (type == 0x0111 ||
            type == 0x0211 ||
            type == 0x0311)
        {
            if (type == 0x0111 ||
                type == 0x0211 ||
                type == 0x0311)
            {
                if (attr_len == sizeof(struct pjstun_attr_hdr))
                {
                    struct pjstun_attr_hdr *attr_hdr = (pjstun_attr_hdr *)attr;
                    if (type == 0x0111)
                    {
                        if (attr_hdr->type == 0x0001 ||
                            attr_hdr->type == 0x0002 ||
                            attr_hdr->type == 0x0003 ||
                            attr_hdr->type == 0x0101 ||
                            attr_hdr->type == 0x0103 ||
                            attr_hdr->type == 0x0111 ||
                            attr_hdr->type == 0x0113 ||
                            attr_hdr->type == 0x0201 ||
                            attr_hdr->type == 0x0203 ||
                            attr_hdr->type == 0x0211 ||
                            attr_hdr->type == 0x0213 ||
                            attr_hdr->type == 0x0301 ||
                            attr_hdr->type == 0x0303 ||
                            attr_hdr->type == 0x0311 ||
                            attr_hdr->type == 0x0313 )
                        {
                            if (attr_len == sizeof(struct pjstun_attr_hdr))
                            {
                                *attr = (struct pjstun_attr_hdr *)attr;
                                if (type == 0x0111)
                                    return (320001);
                            }
                        }
                    }
                }
            }
        }
        if (type == 0x0113 ||
            type == 0x0213 ||
            type == 0x0313)
        {
            if (type == 0x0113 ||
                type == 0x0213 ||
                type == 0x0313)
            {
                if (attr_len == sizeof(struct pjstun_attr_hdr))
                {
                    struct pjstun_attr_hdr *attr_hdr = (pjstun_attr_hdr *)attr;
                    if (type == 0x0113)
                    {
                        if (attr_hdr->type == 0x0001 ||
                            attr_hdr->type == 0x0002 ||
                            attr_hdr->type