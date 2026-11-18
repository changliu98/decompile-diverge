int pjmedia_sdp_media_tostr(struct pjmedia_sdp_media *m, char *buf, unsigned long len)
{
    char *p = buf;
    char *end = buf + len;
    int i; int printed;
    if (len < 36 + m->desc.media.slen + m->desc.transport.slen)
        return -1;
    *p++ = 'm';
    *p++ = '=';
    strlcpy(p, m->desc.media.ptr, m->desc.media.slen);
    p += m->desc.media.slen;
    *p++ = ' ';
    p += sdp_int(m->desc.port, p);
    *p++ = ' ';
    strlcpy(p, m->desc.transport.ptr, m->desc.transport.slen);
    p += m->desc.transport.slen;
    for (i = 0; i < m->desc.fmt_count; i++) {
        *p++ = ' ';
        strlcpy(p, m->desc.fmt[i].ptr, m->desc.fmt[i].slen);
        p += m->desc.fmt[i].slen;
    }
    *p++ = '\r';
    *p++ = '\n';
    if (m->conn != ((void *)0)) {
        printed = sdp_connection(m->conn, p, end - p);
        if (printed < 0)
            return -1;
        p += printed;
    }
    for (i = 0; i < m->bandw_count; i++) {
        printed = sdp_bandwidth(m->bandw[i], p, end - p);
        if (printed < 0)
            return -1;
        p += printed;
    }
    for (i = 0; i < m->attr_count; i++) {
        printed = sdp_attr(m->attr[i], p, end - p);
        if (printed < 0)
            return -1;
        p += printed;
    }
    return p - buf;
}