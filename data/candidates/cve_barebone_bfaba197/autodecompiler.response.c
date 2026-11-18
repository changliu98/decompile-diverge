static pj_status_t pjmedia_rtcp_fb_build_sli(pjmedia_rtcp_session *session,
                             void *buf, pj_size_t *length,
                             unsigned sli_cnt, pjmedia_rtcp_sli *sli)
{
    pjmedia_rtcp_header *header;
    unsigned i;
    pj_uint16_t len;
    pj_uint16_t *word;
    pj_uint8_t *octet;
    pj_status_t status;

    do { if (!(session && buf && length && sli_cnt && sli)) { ___assert_fail("session && buf && length && sli_cnt && sli", "harness.c", 131, "pj_status_t pjmedia_rtcp_fb_build_sli(pjmedia_rtcp_session *, void *, pj_size_t *, unsigned, pjmedia_rtcp_sli *)"); } } while (0);

    status = ((pj_status_t)70000 + 20);
    if (sli_cnt == 0)
        goto on_error;


    len = (pj_uint16_t)(4 + sli_cnt * 6);


    if (len > *length) {
        status = ((pj_status_t)70000 + 35);
        goto on_error;
    }


    header = (pjmedia_rtcp_header*)buf;
    pj_memcpy(header, &session->rtcp_hdr, sizeof(*header));


    header->pt = (pj_uint8_t)((header->pt & 0xFF) | (206 << 8));
    header->flags = (pj_uint8_t)((header->flags & 0xE0) | 2);
    header->pt = (pj_uint8_t)((header->pt & 0xFF) | ((__ZL8foldCaset((pj_uint16_t)(len>>2)-1) & 0xFFFF) << 8));


    word = (pj_uint16_t*)((pj_uint8_t*)header + sizeof(*header));



    for (i=0; i<sli_cnt; ++i) {

        octet = (pj_uint8_t*)word++;
        *octet = (pj_uint8_t)((sli[i].first >> 5) & 0xFF);
        *octet |= (pj_uint8_t)((sli[i].first & 0x1F) << 3);

        octet = (pj_uint8_t*)word++;
        *octet |= (pj_uint8_t)((sli[i].number >> 10) & 0x7);

        octet = (pj_uint8_t*)word++;
        *octet = (pj_uint8_t)((sli[i].number >> 2) & 0xFF);
        *octet |= (pj_uint8_t)((sli[i].number & 0x3) << 6);

        octet = (pj_uint8_t*)word++;
        *octet |= (pj_uint8_t)((sli[i].lost & 0x3F) << 0);
    }

    *length = len;
    return ((pj_status_t)0);

on_error:
    return status;
}