int print_media_desc(struct pjmedia_sdp_media *md, char *buf, int len) {
    char *p = buf;
    char *end = buf + len;
    int printed;

    if (len < md->field_8 + md->field_20 + 0x24) {
        return -1;
    }

    *p++ = 'm';
    *p++ = '=';
    pj_memcpy(p, md->field_0, md->field_8);
    p += md->field_8;
    *p++ = ' ';
    printed = pj_utoa(md->field_10, p);
    p += printed;
    if (md->field_14 > 1) {
        *p++ = '/';
        printed = pj_utoa(md->field_14, p);
        p += printed;
    }
    *p++ = ' ';
    pj_memcpy(p, md->field_18, md->field_20);
    p += md->field_20;

    for (unsigned int i = 0; i < md->field_28; i++) {
        *p++ = ' ';
        pj_memcpy(p, md->attr_arr[i].ptr, md->attr_arr[i].len);
        p += md->attr_arr[i].len;
    }

    *p++ = '\r';
    *p++ = '\n';

    if (md->field_230 != NULL) {
        printed = print_connection_info(md->field_230, p, end - p);
        if (printed < 0) {
            return -1;
        }
        p += printed;
    }

    for (unsigned int i = 0; i < md->field_238; i++) {
        printed = print_bandw(md->field_240[i], p, end - p);
        if (printed < 0) {
            return -1;
        }
        p += printed;
    }

    for (unsigned int i = 0; i < md->field_260; i++) {
        printed = print_attr(md->field_268[i], p, end - p);
        if (printed < 0) {
            return -1;
        }
        p += printed;
    }

    return p - buf;
}