void id3dmx_flush(GF_Filter *filter,u8 *id3_buf,u32 id3_buf_size,GF_FilterPid *audio_pid,
                 GF_FilterPid **video_pid_p)

{
  int iVar1;
  GF_BitStream *bs_00;
  u64 uVar2;
  u8 *__s;
  void *pvVar3;
  char *pcVar4;
  bool bVar5;
  GF_PropertyValue local_4e8;
  char *tag_name;
  GF_PropertyValue local_4c8;
  GF_PropertyValue local_4b0;
  GF_FilterPacket *dst_pck;
  u8 *out_buffer;
  GF_Err e;
  u32 fsize;
  u32 ftag;
  u32 pic_size;
  s32 tag_idx;
  char *sep;
  char szTag [1024];
  char *buf;
  u32 size;
  u8 ext_hdr;
  u32 buf_alloc;
  char *_buf;
  char *sep_desc;
  GF_BitStream *bs;
  GF_FilterPid **video_pid_p_local;
  GF_FilterPid *audio_pid_local;
  u32 id3_buf_size_local;
  u8 *id3_buf_local;
  GF_Filter *filter_local;
  
  bs_00 = gf_bs_new(id3_buf,(ulong)id3_buf_size,0);
  _buf = (char *)0x0;
  buf_alloc = 0;
  gf_bs_skip_bytes(bs_00,3);
  gf_bs_read_u8(bs_00);
  gf_bs_read_u8(bs_00);
  gf_bs_read_int(bs_00,1);
  gf_bs_read_int(bs_00,1);
  gf_bs_read_int(bs_00,6);
  size = gf_id3_read_size(bs_00);
  while( true ) {
    bVar5 = false;
    if (size != 0) {
      uVar2 = gf_bs_available(bs_00);
      bVar5 = 9 < uVar2;
    }
    if (!bVar5) break;
    ftag = gf_bs_read_u32(bs_00);
    fsize = gf_id3_read_size(bs_00);
    gf_bs_read_u16(bs_00);
    if ((fsize == 0) || (size - 10 < fsize)) break;
    if (buf_alloc <= fsize) {
      _buf = gf_realloc(_buf,(ulong)(fsize + 3));
      buf_alloc = fsize + 3;
    }
    gf_bs_read_data(bs_00,(u8 *)(_buf + 1),fsize);
    _buf[fsize + 1] = '\0';
    _buf[fsize + 2] = '\0';
    __s = (u8 *)(_buf + 1);
    tag_idx = gf_itags_find_by_id3tag(ftag);
    if (ftag == 0x54585858) {
      sep = memchr(__s,0,(ulong)fsize);
      if (sep != (char *)0x0) {
        iVar1 = strcasecmp(_buf + 2,"comment");
        if (iVar1 == 0) {
          id3dmx_set_string(audio_pid,"comment",(u8 *)(sep + 1),GF_FALSE);
        }
        else {
          strcpy(szTag,"tag_");
          strncat(szTag,_buf + 2,0x3fb);
          id3dmx_set_string(audio_pid,szTag,(u8 *)(sep + 1),GF_TRUE);
        }
      }
    }
    else if (ftag == 0x41504943) {
      sep = memchr(_buf + 2,0,(ulong)(fsize - 1));
      pvVar3 = memchr(sep + 2,0,(ulong)(fsize - 1));
      if (pvVar3 != (void *)0x0) {
        pic_size = fsize - (((int)pvVar3 + 1) - (int)__s);
        if (video_pid_p == (GF_FilterPid **)0x0) {
          local_4c8.type = GF_PROP_DATA;
          local_4c8.value.data.ptr = (u8 *)((long)pvVar3 + 1);
          local_4c8.value.data.size = pic_size;
          gf_filter_pid_set_property(audio_pid,0x50434f56,&local_4c8);
        }
        else {
          e = gf_filter_pid_raw_new
                        (filter,(char *)0x0,(char *)0x0,_buf + 2,(char *)0x0,
                         (u8 *)((long)pvVar3 + 1),pic_size,GF_FALSE,video_pid_p);
          if (*video_pid_p != (GF_FilterPid *)0x0) {
            gf_filter_pid_set_name(*video_pid_p,"CoverArt");
            local_4b0.type = GF_PROP_BOOL;
            local_4b0.value.boolean = GF_TRUE;
            gf_filter_pid_set_property(*video_pid_p,0x50434f56,&local_4b0);
            dst_pck = gf_filter_pck_new_alloc(*video_pid_p,pic_size,&out_buffer);
            if (dst_pck != (GF_FilterPacket *)0x0) {
              gf_filter_pck_set_framing(dst_pck,GF_TRUE,GF_TRUE);
              memcpy(out_buffer,(void *)((long)pvVar3 + 1),(ulong)pic_size);
              gf_filter_pck_send(dst_pck);
            }
            gf_filter_pid_set_eos(*video_pid_p);
          }
        }
      }
    }
    else if (tag_idx < 0) {
      pcVar4 = gf_4cc_to_str(ftag);
      sprintf(szTag,"tag_%s",pcVar4);
      if (ftag >> 0x18 == 0x54) {
        id3dmx_set_string(audio_pid,szTag,(u8 *)(_buf + 2),GF_TRUE);
      }
      else {
        local_4e8.type = GF_PROP_DATA;
        local_4e8.value.data.size = fsize;
        local_4e8.value.data.ptr = __s;
        gf_filter_pid_set_property_dyn(audio_pid,szTag,&local_4e8);
      }
    }
    else {
      tag_name = gf_itags_get_name(tag_idx);
      id3dmx_set_string(audio_pid,tag_name,(u8 *)(_buf + 2),GF_FALSE);
    }
    size = (size - 10) - fsize;
  }
  gf_bs_del(bs_00);
  if (_buf != (char *)0x0) {
    gf_free(_buf);
  }
  return;
}