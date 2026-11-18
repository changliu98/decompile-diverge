pj_status_t
pjmedia_rtcp_fb_build_sli
          (pjmedia_rtcp_session *session,void *buf,pj_size_t *length,uint sli_cnt,
          pjmedia_rtcp_fb_sli *sli)

{
  pj_uint16_t pVar1;
  uint uVar2;
  byte *pbVar3;
  uint i;
  uint len;
  pj_uint8_t *p;
  pjmedia_rtcp_common *hdr;
  pjmedia_rtcp_fb_sli *sli_local;
  uint sli_cnt_local;
  pj_size_t *length_local;
  void *buf_local;
  pjmedia_rtcp_session *session_local;
  pj_status_t local_c;
  
  if ((((session == (pjmedia_rtcp_session *)0x0) || (buf == (void *)0x0)) ||
      (length == (pj_size_t *)0x0)) || ((sli_cnt == 0 || (sli == (pjmedia_rtcp_fb_sli *)0x0)))) {
    if (((session == (pjmedia_rtcp_session *)0x0) || (buf == (void *)0x0)) ||
       ((length == (pj_size_t *)0x0 || ((sli_cnt == 0 || (sli == (pjmedia_rtcp_fb_sli *)0x0)))))) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("session && buf && length && sli_cnt && sli","/work/harness.c",0x83,
                    "pj_status_t pjmedia_rtcp_fb_build_sli(pjmedia_rtcp_session *, void *, pj_size_t *, unsigned int, const pjmedia_rtcp_fb_sli *)"
                   );
    }
    local_c = 0x11174;
  }
  else {
    uVar2 = (sli_cnt + 3) * 4;
    if (*length < (ulong)uVar2) {
      local_c = 0x11183;
    }
    else {
      pj_memcpy(buf,session,8);
      *(uint *)buf = *(uint *)buf & 0xffff00ff | 0xce00;
      *(uint *)buf = *(uint *)buf & 0xffffffe0 | 2;
      pVar1 = pj_htons((short)(sli_cnt + 3) - 1);
      *(uint *)buf = *(uint *)buf & 0xffff | (uint)pVar1 << 0x10;
      p = (pj_uint8_t *)((long)buf + 8);
      for (i = 0; i < sli_cnt; i = i + 1) {
        pbVar3 = p + 1;
        *p = (pj_uint8_t)((int)(uint)sli[i].first >> 5);
        *pbVar3 = (byte)((sli[i].first & 0x1f) << 3);
        *pbVar3 = *pbVar3 | (byte)((int)(uint)sli[i].number >> 10) & 7;
        pbVar3 = p + 3;
        p[2] = (pj_uint8_t)((int)(uint)sli[i].number >> 2);
        *pbVar3 = (byte)((sli[i].number & 3) << 6);
        p = p + 4;
        *pbVar3 = *pbVar3 | sli[i].pict_id & 0x3f;
      }
      *length = (ulong)uVar2;
      local_c = 0;
    }
  }
  return local_c;
}