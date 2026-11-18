pj_status_t __cdecl pjmedia_rtcp_fb_build_sli(
        pjmedia_rtcp_session *session,
        void *buf,
        pj_size_t *length,
        unsigned int sli_cnt,
        const pjmedia_rtcp_fb_sli *sli)
{
  pj_uint8_t *v5; // rax
  _BYTE *v6; // rax
  pj_uint8_t *v7; // rax
  unsigned int i; // [rsp+8h] [rbp-48h]
  unsigned int len; // [rsp+Ch] [rbp-44h]
  pj_uint8_t *p; // [rsp+10h] [rbp-40h]
  pj_uint8_t *pa; // [rsp+10h] [rbp-40h]

  if ( session && buf && length && sli_cnt && sli )
  {
    len = 4 * (sli_cnt + 3);
    if ( len <= *length )
    {
      pj_memcpy(buf, session, 8uLL);
      *(_DWORD *)buf = *(_DWORD *)buf & 0xFFFF00FF | 0xCE00;
      *(_DWORD *)buf = *(_DWORD *)buf & 0xFFFFFFE0 | 2;
      *(_DWORD *)buf = (foldCase((len >> 2) - 1) << 16) | (unsigned __int16)*(_DWORD *)buf;
      p = (pj_uint8_t *)buf + 8;
      for ( i = 0; i < sli_cnt; ++i )
      {
        v5 = p;
        pa = p + 1;
        *v5 = (int)sli[i].first >> 5;
        *pa = 8 * (sli[i].first & 0x1F);
        *pa |= ((int)sli[i].number >> 10) & 7;
        v6 = pa + 1;
        pa += 2;
        *v6 = (int)sli[i].number >> 2;
        *pa = (sli[i].number & 3) << 6;
        v7 = pa;
        p = pa + 1;
        *v7 |= sli[i].pict_id & 0x3F;
      }
      *length = len;
      return 0;
    }
    else
    {
      return 70019;
    }
  }
  else
  {
    if ( !session || !buf || !length || !sli_cnt || !sli )
      __assert_fail(
        "session && buf && length && sli_cnt && sli",
        "/work/harness.c",
        0x83u,
        "pj_status_t pjmedia_rtcp_fb_build_sli(pjmedia_rtcp_session *, void *, pj_size_t *, unsigned int, const pjmedia_rtcp_fb_sli *)");
    return 70004;
  }
}