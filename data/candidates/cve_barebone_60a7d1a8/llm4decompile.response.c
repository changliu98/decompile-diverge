pj_status_t pjstun_parse_msg(const pj_uint8_t *buf, pj_size_t buf_len,
                             pjstun_msg *msg)
{
    pj_uint16_t attr_len;
    pj_uint16_t msg_len;
    pj_uint16_t msg_type;
    const pj_uint8_t *p_attr;

    msg->hdr = (pjstun_msg_hdr*) buf;


    msg_type = pj_ntohs(msg->hdr->type);
    if (msg_type != 0x0001 &&
        msg_type != 0x0002 &&
        msg_type != 0x0101 &&
        msg_type != 0x0102 &&
        msg_type != 0x0111 &&
        msg_type != 0x0112)
    {
        return 303746;
    }


    msg_len = pj_ntohs(msg->hdr->length);
    if (msg_len != (buf_len - sizeof(pjstun_msg_hdr)))
    {
        return 303747;
    }


    msg->attr_count = 0;
    p_attr = buf + sizeof(pjstun_msg_hdr);
    while (msg_len)
    {
        msg->attr[msg->attr_count] = (pjstun_attr_hdr*) p_attr;


        attr_len = pj_ntohs(msg->attr[msg->attr_count]->length);
        attr_len = (attr_len + 3) & (~3);
        if (msg_len < attr_len)
        {
            return 303748;
        }


        switch (pj_ntohs(msg->attr[msg->attr_count]->type))
        {
        case (0x0001):
            break;
        case (0x0002):
            break;
        case (0x0003):
            break;
        case (0x0004):
            break;
        case (0x0005):
            break;
        case (0x0006):
            break;
        case (0x0007):
            break;
        case (0x0008):
            break;
        case (0x0009):
            break;
        case (0x000a):
            break;
        case (0x000b):
            break;
        case (0x000c):
            break;
        case (0x000d):
            break;
        case (0x000e):
            break;
        case (0x000f):
            break;
        case (0x0010):
            break;
        case (0x0012):
            break;
        case (0x0013):
            break;
        case (0x0014):
            break;
        case (0x0015):
            break;
        case (0x0016):
            break;
        case (0x8001):
            break;
        case (0x8002):
            break;
        case (0x8003):
            break;
        case (0x8004):
            break;
        case (0x8005):
            break;
        case (0x8006):
            break;
        case (0x8007):
            break;
        case (0x8008):
            break;
        case (0x8009):
            break;
        case (0x800a):
            break;
        case (0x800b):
            break;
        case (0x800c):
            break;
        case (0x800d):
            break;
        case (0x800e):
            break;
        case (0x800f):
            break;
        case (0x8010):
            break;
        case (0x8012):
            break;
        case (0x8013):
            break;
        case (0x8014):
            break;
        case (0x8015):
            break;
        case (0x8016):
            break;
        case (0x8020):
            break;
        case (0x8021):
            break;
        case (0x8022):
            break;
        case (0x8023):
            break;
        case (0x8024):
            break;
        case (0x8025):
            break;
        case (0x8026):
            break;
        case (0x8027):
            break;
        case (0x8028):
            break;
        default:
            break;
        }

        msg_len -= attr_len;
        p_attr += attr_len;
        msg->attr_count++;
    }

    return 0;
}