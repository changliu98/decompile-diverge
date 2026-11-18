static int pjstun_parse_msg(unsigned char *src, size_t len, struct nlmsg *nlmsg) {
    nlmsg->buf = src;
    unsigned short type = NLMSG_TYPE(nlmsg->buf[0]);
    int pos = type;
    switch (type) {
    case NLMSG_DONE:
    case NLMSG_ERROR:
        return NLMSG_OK;
    }
    while (1) {
        unsigned short nlmsg_len = NLMSG_LEN(nlmsg->buf);
        if (len < nlmsg_len)
            return NLMSG_ERR_MSG_TOO_SHORT;
        if (nlmsg_len < sizeof(struct genlmsghdr))
            return NLMSG_ERR_HDR_TOO_SHORT;
        struct genlmsghdr *genlhdr = (void *)(nlmsg->buf + pos);
        unsigned int cmd = GENL_HDR_FLAG(genlhdr->cmd);
        pos += sizeof(struct genlmsghdr) + cmd;
        if (cmd < sizeof(struct genlmsghdr))
            return NLMSG_ERR_HDR_TOO_SHORT;
        type = NLMSG_TYPE(genlhdr->cmd);
        switch (type) {
        case GENL_ID_GENERIC:
            break;
        case GENL_ID_CLOEXEC:
            return NLMSG_OK;
        default:
            return NLMSG_ERR_UNKNOWN_TYPE;
        }
        nlmsg_len -= sizeof(struct genlmsghdr) + cmd;
        nlmsg->buf += pos;
        nlmsg->pos++;
    }
    return NLMSG_OK;
}