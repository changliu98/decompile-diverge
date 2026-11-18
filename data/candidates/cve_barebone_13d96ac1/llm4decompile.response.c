pj_ssize_t print_media_desc( const pjmedia_sdp_media *m,
                             char *buf, pj_size_t len)
{
    char *p = buf;
    char *end = buf + len;
    unsigned i;
    pj_ssize_t printed;


    if (len < (m->desc.media.slen + m->desc.transport.slen + 36))
        return -1;


    *p++ = 'm';
    *p++ = '=';
    pj_memcpy(p, m->desc.media.ptr, m->desc.media.slen);
    p += m->desc.media.slen;
    *p++ = ' ';
    p += pj_utoa(m->desc.port, p);
    if (m->desc.port_count > 1) {
        *p++ = '/';
        p += pj_utoa(m->desc.port_count, p);
    }
    *p++ = ' ';
    pj_memcpy(p, m->desc.transport.ptr, m->desc.transport.slen);
    p += m->desc.transport.slen;
    for (i=0; i<m->desc.fmt_count; ++i) {
        *p++ = ' ';
        pj_memcpy(p, m->desc.fmt[i].ptr, m->desc.fmt[i].slen);
        p += m->desc.fmt[i].slen;
    }
    *p++ = '\r';
    *p++ = '\n';


    if (m->conn != NULL) {
        printed = print_connection_info(m->conn, p, end-p);
        if (printed < 0)
            return -1;
        p += printed;
    }


    for (i=0; i<m->bandw_count; ++i) {
        printed = print_bandw(m->bandw[i], p, end-p);
        if (printed < 0)
            return -1;
        p += printed;
    }


    for (i=0; i<m->attr_count; ++i) {
        printed = print_attr(m->attr[i], p, end-p);
        if (printed < 0)
            return -1;
        p += printed;
    }

    return p - buf;
}