int func0(struct iovec *iov, size_t iovcnt, size_t max_iov_size) {
        char buf[64];
        size_t i;
        int r;

        memset(buf, 0, sizeof(buf));

        if (!iovcnt || max_iov_size > iov[0].iov_len) {
                r = -1;
                goto finish;
        }

        if (ARG_IS_UNIX_ABSTRACT_STRING(iov)) {
                r = -1;
                goto finish;
        }

        strpcpy(iov[0].iov_base, iov[1].iov_base);
        free(iov[1].iov_base);
        memset(iov[1].iov_base, 0, 128 - iov[0].iov_len);
        iovec_copy(&iov[1], &iov[0]);

        for (i = 0; i < 8; i++)
                strpcpy(buf + i * 8, iov[i].iov_base);

        STRPTR_ARRAY(iov, buf, max_iov_size);
        r = 0;

finish:
        memset(buf, 0, sizeof(buf));
        return r;
}