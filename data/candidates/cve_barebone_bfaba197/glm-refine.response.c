define PJ_EINVAL 70004

pj_status_t __cdecl pjmedia_rtcp_fb_build_sli(
        pjmedia_rtcp_session *session,
        void *buf,
        pj_size_t *length,
        unsigned int sli_cnt,
        const pjmedia_rtcp_fb_sli *sli)
{
    if (!session || !buf || !length || !sli_cnt || !sli) {
        __assert_fail(
            "session && buf && length && sli_cnt && sli",
            "/work/harness.c",
            0x83,
            "pj_status_t pjmedia_rtcp_fb_build_sli(pjmedia_rtcp_session *, void *, pj_size_t *, unsigned int, const pjmedia_rtcp_fb_sli *)");
        return PJ_EINVAL;
    }

    unsigned int len = 4 * (sli_cnt + 3);
    if (len > *length) {
        return PJ_ETOOBIG;
    }

    // Copy the first 8 bytes from the RTCP session (common header + SSRC)
    pj_memcpy(buf, session, 8);

    // Modify the RTCP common header (first 32-bit word)
    pj_uint32_t header = *(pj_uint32_t *)buf;
    
    // Set Packet Type (PT) to 206 (0xCE)
    header = (header & 0xFFFF00FF) | 0xCE00;
    
    // Set Reception Report Count (RC) to 2
    header = (header & 0xFFFFFFE0) | 2;
    
    // Set Length field (16-bit word length minus 1)
    // Note: `foldCase` is an artifact of decompilation and acts as a no-op for unsigned values here
    header = (header & 0x0000FFFF) | (((len >> 2) - 1) << 16);
    
    *(pj_uint32_t *)buf = header;

    // Pointer to the payload section (after the 8-byte common header)
    pj_uint8_t *p = (pj_uint8_t *)buf + 8;

    // Pack SLI (Slice Loss Indication) entries
    for (unsigned int i = 0; i < sli_cnt; ++i) {
        // The SLI feedback control information (FCI) is 4 bytes (32 bits) per entry:
        // 0                   1                   2                   3
        // 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
        //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        //|            First        |        Number        | Picture ID   |
        //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        // Byte 0: First 8 bits of 'first' (bits 24-31 of the 32-bit FCI field)
        p[0] = (pj_uint8_t)(sli[i].first >> 5);

        // Byte 1: Last 3 bits of 'first' shifted to the top, OR'd with the top 3 bits of 'number'
        p[1] = (pj_uint8_t)((sli[i].first & 0x1F) << 3) | 
               (pj_uint8_t)((sli[i].number >> 10) & 0x07);

        // Byte 2: Middle 8 bits of 'number'
        p[2] = (pj_uint8_t)(sli[i].number >> 2);

        // Byte 3: Last 2 bits of 'number' shifted to the top, OR'd with the 6-bit 'pict_id'
        p[3] = (pj_uint8_t)((sli[i].number & 0x03) << 6) | 
               (pj_uint8_t)(sli[i].pict_id & 0x3F);

        p += 4;
    }

    *length = len;
    return PJ_SUCCESS;
}