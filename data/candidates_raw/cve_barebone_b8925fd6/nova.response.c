static int func0(struct nlmsg *nlmsg, struct iovec *io,
                         size_t size) {
    if (io + 2 > &io[size])
        return _ENOMEM;
    if (nlmsg->pos > nlmsg->buf + sizeof(nlmsg->buf) - 2)
        return _ENOMEM;
    if (nlmsg->nused > nlmsg->pos - 2)
        return _ENOMEM;

    struct sockaddr_nl addr = {
       .nl_family = AF_NETLINK,
       .nl_pad = 0,
       .nl_pid = nlmsg->seq,
       .nl_groups = nlmsg_mask(nlmsg),
    };
    struct msghdr msg = {
       .msg_name = &addr,
       .msg_namelen = sizeof(addr),
    };
    int err;
    for (io = io + 1;; io++) {
        io->iov_base = nlmsg_next(nlmsg, io->iov_len);
        io->iov_len = _MIN(io->iov_len, nlmsg->nused);
        if (io->iov_len == 0)
            break;
        err = 1;
    }
    return err;
}