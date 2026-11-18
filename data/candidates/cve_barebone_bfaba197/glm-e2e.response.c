int pjmedia_rtcp_fb_build_sli(struct pjmedia_rtcp_session *sess, void *buf, size_t *len, unsigned count, struct pjmedia_rtcp_fb_sli_entry *sli)
{
    uint32_t *pkt;
    uint8_t *p;
    unsigned i;
    size_t pkt_len;

    if (!sess || !buf || !len || !count || !sli) {
        if (!sess || !buf || !len || !count || !sli) {
            __assert_fail("sess && buf && len && count && sli", "rtcp_fb.c", 0x83, "pjmedia_rtcp_fb_build_sli");
        }
        return 0x11174; // -40012
    }

    pkt_len = (count + 3) * 4;
    if (pkt_len > *len) {
        return 0x11183; // -40001
    }

    pkt = (uint32_t *)buf;
    pj_memcpy(pkt, sess, 8);

    pkt[0] = (pkt[0] & 0xFFFF00FF) | 0xCE00;
    pkt[0] = (pkt[0] & 0xFFFFFFE0) | 0x2;
    pkt[0] = (pkt[0] & 0xFFFF) | ((uint32_t)pj_htons((uint16_t)((pkt_len / 4) - 1)) << 16);

    p = (uint8_t *)&pkt[2];
    for (i = 0; i < count; i++) {
        p[0] = (uint8_t)(sli[i].first >> 5);
        p[1] = (uint8_t)((sli[i].first & 0x1F) << 3);
        p[1] |= (uint8_t)((sli[i].number >> 10) & 0x7);
        p[2] = (uint8_t)((sli[i].number >> 2) & 0xFF);
        p[3] = (uint8_t)((sli[i].number & 0x3) << 6);
        p[3] |= (uint8_t)(sli[i].picture_id & 0x3F);
        p += 6;
    }

    *len = pkt_len;
    return 0;
}