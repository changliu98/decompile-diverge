int print_media_desc( pjsip_msg *msg, char *buf, size_t size )
{
    char *p = buf;
    char *end = buf + size;
    int i, printed;
    int status;

    if (p + msg->v1.res_line.sz + msg->v1.reason.psz + 12 + 24 >= end) {
        status = -1;
        goto error;
    }


    *p++ = 'm';
    *p++ = '=';
    pj_memcpy(p, msg->v1.msg_name.psz, msg->v1.msg_name.sz);
    p += msg->v1.msg_name.sz;
    *p++ = ' ';
    printed = pj_utoa(msg->v1.status_code, p);
    p += printed;
    if (msg->v1.status_code_text.sz > 1) {
        *p++ = '/';
        printed = pj_utoa(msg->v1.status_code_text.sz, p);
        p += printed;
    }
    *p++ = ' ';
    pj_memcpy(p, msg->v1.reason.psz, msg->v1.reason.sz);
    p += msg->v1.reason.sz;


    for (i=0; i<msg->v1.hdr_count; ++i) {
        *p++ = ' ';
        pj_memcpy(p, msg->v1.hdrs[i].name.psz, msg->v1.hdrs[i].name.sz);
        p += msg->v1.hdrs[i].name.sz;
    }

    *p++ = '\r';
    *p++ = '\n';


    if (msg->v1.contact.ptr) {
        printed = print_connection_info(msg->v1.contact.ptr, p,
                                         (unsigned)(end-p));
        if (printed < 0) {
            status = -1;
            goto error;
        }
        p += printed;
    }


    for (i=0; i<msg->v1.cnt_bandw; ++i) {
        printed = print_bandw(msg->v1.bandw[i], p, (unsigned)(end-p));
        if (printed < 0) {
            status = -1;
            goto error;
        }
        p += printed;
    }


    for (i=0; i<msg->v1.cnt_attr; ++i) {
        printed = print_attr(msg->v1.attr[i], p, (unsigned)(end-p));
        if (printed < 0) {
            status = -1;
            goto error;
        }
        p += printed;
    }

    status = p-buf;

error:
    return status;
}