pj_status_t pjmedia_rtcp_fb_build_sli(pjmedia_rtcp_session *session,
                                      void *buf, pj_size_t *length,
                                      unsigned int sli_cnt,
                                      const pjmedia_rtcp_fb_sli *sli)
{
    pjmedia_rtcp_common *hdr;
    pj_uint8_t *p;
    unsigned int i;
    unsigned int len;

    do { if (!(session && buf && length && sli_cnt && sli)) { __assert_fail("session && buf && length && sli_cnt && sli", "/work/harness.c", 131, "pj_status_t pjmedia_rtcp_fb_build_sli(pjmedia_rtcp_session *, void *, pj_size_t *, unsigned int, const pjmedia_rtcp_fb_sli *)"); return 70004; } } while (0);


    len = 8 + 4 * (sli_cnt + 3);
    if (*length < len)
        return 70051;


    pj_memcpy(buf, &session->pkt, sizeof(session->pkt));
    hdr = (pjmedia_rtcp_common*) buf;
    hdr->pt = 206;
    hdr->cc = 2;
    hdr->rc = 0;
    hdr->len = pj_htons((pj_uint16_t) ((len / 4) - 1));


    p = (pj_uint8_t*) ((pj_uint8_t*)buf + 8);
    for (i = 0; i < sli_cnt; i++) {
        *p++ = (sli[i].first & 0xFF) >> 5;
        *p = (sli[i].first & 0x1F) << 3;
        *p++ |= (sli[i].number & 0x70000) >> 17;
        *p++ = (sli[i].number & 0xFF00) >> 8;
        *p = (sli[i].number & 0x03) << 6;
        *p++ |= (sli[i].pict_id & 0x3F);
    }

    *length = len;

    return 0;
}