// local variable allocation has failed, the output may be wrong!
void __cdecl id3dmx_flush(
        GF_Filter *filter,
        u8 *id3_buf,
        u32 id3_buf_size,
        GF_FilterPid *audio_pid,
        GF_FilterPid **video_pid_p)
{
  GF_FilterPid *v5; // rdi
  const char *v6; // rax
  bool v7; // [rsp+2Fh] [rbp-4E1h]
  GF_PropertyValue v8; // [rsp+30h] [rbp-4E0h] BYREF
  const char *tag_name; // [rsp+48h] [rbp-4C8h]
  GF_PropertyValue v10; // [rsp+50h] [rbp-4C0h] BYREF
  GF_PropertyValue value; // [rsp+68h] [rbp-4A8h] BYREF
  GF_FilterPacket *dst_pck; // [rsp+80h] [rbp-490h]
  u8 *out_buffer; // [rsp+88h] [rbp-488h] BYREF
  GF_Err e; // [rsp+94h] [rbp-47Ch]
  u32 fsize; // [rsp+98h] [rbp-478h]
  u32 ftag; // [rsp+9Ch] [rbp-474h]
  u32 pic_size; // [rsp+A0h] [rbp-470h]
  s32 tag_idx; // [rsp+A4h] [rbp-46Ch]
  char *sep; // [rsp+A8h] [rbp-468h]
  char szTag[1024]; // [rsp+B0h] [rbp-460h] BYREF
  char *buf; // [rsp+4B8h] [rbp-58h]
  u32 size; // [rsp+4C4h] [rbp-4Ch]
  _BYTE ext_hdr[5]; // [rsp+4CBh] [rbp-45h] OVERLAPPED
  char *_buf; // [rsp+4D0h] [rbp-40h]
  char *sep_desc; // [rsp+4D8h] [rbp-38h]
  GF_BitStream *bs; // [rsp+4E0h] [rbp-30h]
  GF_FilterPid **video_pid_pa; // [rsp+4E8h] [rbp-28h]
  GF_FilterPid *audio_pida; // [rsp+4F0h] [rbp-20h]
  u32 id3_buf_sizea; // [rsp+4FCh] [rbp-14h]
  u8 *id3_bufa; // [rsp+500h] [rbp-10h]
  GF_Filter *filtera; // [rsp+508h] [rbp-8h]

  filtera = filter;
  id3_bufa = id3_buf;
  id3_buf_sizea = id3_buf_size;
  audio_pida = audio_pid;
  video_pid_pa = video_pid_p;
  bs = gf_bs_new(id3_buf, id3_buf_size, 0);
  _buf = 0LL;
  ext_hdr[4] = 0;
  gf_bs_skip_bytes(bs, 3uLL);
  gf_bs_read_u8(bs);
  gf_bs_read_u8(bs);
  gf_bs_read_int(bs, 1u);
  *(_DWORD *)ext_hdr = (unsigned __int8)gf_bs_read_int(bs, 1u);
  gf_bs_read_int(bs, 6u);
  for ( size = gf_id3_read_size(bs); ; size -= fsize )
  {
    v7 = 0;
    if ( size )
      v7 = gf_bs_available(bs) >= 0xA;
    if ( !v7 )
      break;
    ftag = gf_bs_read_u32(bs);
    fsize = gf_id3_read_size(bs);
    gf_bs_read_u16(bs);
    size -= 10;
    if ( !fsize || size < fsize )
      break;
    if ( *(_DWORD *)&ext_hdr[1] <= fsize )
    {
      _buf = (char *)chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(_buf, fsize + 3);
      *(_DWORD *)&ext_hdr[1] = fsize + 3;
    }
    gf_bs_read_data(bs, (u8 *)_buf + 1, fsize);
    _buf[fsize + 1] = 0;
    _buf[fsize + 2] = 0;
    buf = _buf + 1;
    tag_idx = gf_itags_find_by_id3tag(ftag);
    if ( ftag == 1415075928 )
    {
      sep = (char *)memchr(buf, 0, fsize);
      if ( sep )
      {
        if ( !strcasecmp(buf + 1, "comment") )
        {
          id3dmx_set_string(audio_pida, "comment", (u8 *)sep + 1, GF_FALSE);
        }
        else
        {
          strcpy(szTag, "tag_");
          strncat(szTag, buf + 1, 0x3FBuLL);
          id3dmx_set_string(audio_pida, szTag, (u8 *)sep + 1, GF_TRUE);
        }
      }
    }
    else if ( ftag == 1095780675 )
    {
      sep = (char *)memchr(buf + 1, 0, fsize - 1);
      sep_desc = (char *)memchr(sep + 2, 0, fsize - 1);
      if ( sep_desc )
      {
        pic_size = (_DWORD)sep_desc + 1 - (_DWORD)buf;
        pic_size = fsize - pic_size;
        if ( video_pid_pa )
        {
          e = gf_filter_pid_raw_new(
                filtera,
                0LL,
                0LL,
                buf + 1,
                0LL,
                (const u8 *)sep_desc + 1,
                pic_size,
                GF_FALSE,
                video_pid_pa);
          if ( *video_pid_pa )
          {
            gf_filter_pid_set_name(*video_pid_pa, "CoverArt");
            v5 = *video_pid_pa;
            value.type = GF_PROP_BOOL;
            value.value.boolean = GF_TRUE;
            gf_filter_pid_set_property(v5, 0x50434F56u, &value);
            dst_pck = gf_filter_pck_new_alloc(*video_pid_pa, pic_size, &out_buffer);
            if ( dst_pck )
            {
              gf_filter_pck_set_framing(dst_pck, GF_TRUE, GF_TRUE);
              memcpy(out_buffer, sep_desc + 1, pic_size);
              gf_filter_pck_send(dst_pck);
            }
            gf_filter_pid_set_eos(*video_pid_pa);
          }
        }
        else
        {
          v10.type = GF_PROP_DATA;
          v10.value.data.ptr = (u8 *)(sep_desc + 1);
          v10.value.data.size = pic_size;
          gf_filter_pid_set_property(audio_pida, 0x50434F56u, &v10);
        }
      }
    }
    else if ( tag_idx < 0 )
    {
      v6 = gf_4cc_to_str(ftag);
      sprintf(szTag, "tag_%s", v6);
      if ( HIBYTE(ftag) == 84 )
      {
        id3dmx_set_string(audio_pida, szTag, (u8 *)buf + 1, GF_TRUE);
      }
      else
      {
        v8.type = GF_PROP_DATA;
        v8.value.data.ptr = (u8 *)buf;
        v8.value.data.size = fsize;
        gf_filter_pid_set_property_dyn(audio_pida, szTag, &v8);
      }
    }
    else
    {
      tag_name = gf_itags_get_name(tag_idx);
      id3dmx_set_string(audio_pida, (char *)tag_name, (u8 *)buf + 1, GF_FALSE);
    }
  }
  QScopedPointerPodDeleter::cleanup(bs);
  if ( _buf )
    gf_free(_buf);
}