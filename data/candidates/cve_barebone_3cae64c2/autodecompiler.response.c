static void id3dmx_flush(GF_Filter *from, char *id3_buf, u32 id3_buf_size, GF_Pid *pid, GF_Pid **cover_pid)
{
 GF_BitStream *bs = gf_bs_new(id3_buf, id3_buf_size, NULL);
 char *buffer=NULL;
 unsigned int buffer_alloc=0;

 gf_bs_skip_bytes(bs, 3);
 gf_bs_read_u8(bs);
 gf_bs_read_u8(bs);

 char ext_hdr = gf_bs_read_int(bs, 1);
 gf_bs_read_int(bs, 1);
 gf_bs_read_int(bs, 6);

 unsigned int size = gf_id3_read_size(bs);


 if (ext_hdr) {

 }

 while(1) {
  char ok = 1;
  if (!size || gf_bs_available(bs)<11) ok = 0;
  if (!ok) break;

  unsigned int tag = gf_bs_read_u32(bs);
  unsigned int fsize = gf_id3_read_size(bs);
  gf_bs_read_u16(bs);
  size -= 10;

  if (!fsize) break;
  if (size<fsize) break;

  if (buffer_alloc<=fsize) {
   buffer = _ZN4chip14BindingManager40RegisterBoundDeviceContextReleaseHandlerEPFvPvE(buffer, sizeof(char)*(fsize+3));
   buffer_alloc = fsize+3;
  }
  gf_bs_read_data(bs, buffer+1, fsize);
  buffer[1+fsize] = 0;
  buffer[1+fsize+1] = 0;

  char *data = &buffer[1];
  int tag_idx = gf_itags_find_by_id3tag(tag);

  if (tag==0x54585858) {
   char *sep = strchr(data, '\0');
   if (sep) {
    if (!strcasecmp(&data[1], "comment")) {
     id3dmx_set_string(pid, "comment", sep+1, 0);
    } else {
     char szTag[1024];
     strcpy(szTag, "tag_");
     strncat(szTag, &data[1], 1024 - 1 - 5);
     id3dmx_set_string(pid, szTag, sep+1, 1);
    }
   }
  } else if (tag==0x41504943) {
   char *sep = strchr(data, '\0');
   char *sep_desc = strchr(sep+2, '\0');
   if (sep_desc) {
    unsigned int pic_size = sep_desc+1 - data;
    pic_size = fsize - pic_size;

    if (cover_pid) {
     GF_Pid *cpid = gf_filter_pid_raw_new(from, NULL, NULL, data+1, NULL, pic_size, cover_pid);
     if (cpid) continue;
     if (*cover_pid) {
      gf_filter_pid_set_name(*cover_pid, "CoverArt");

      GF_PropertyValue pval;
      pval.type = 5;
      pval.value._int = 1;
      gf_filter_pid_set_property(*cover_pid, 0x50434F56, &pval);

      char *pck_data;
      GF_FilterPacket *pck = gf_filter_pck_new_alloc(*cover_pid, pic_size, &pck_data);
      if (pck) {
       gf_filter_pck_set_framing(pck, 1, 1);
       memcpy(pck_data, sep_desc+1, pic_size);
       gf_filter_pck_send(pck);
      }
      gf_filter_pid_set_eos(*cover_pid);
     }
    } else {
     GF_PropertyValue pval;
     pval.type = 16;
     pval.value.string = sep_desc+1;
     pval.value.string_length = pic_size;
     gf_filter_pid_set_property(pid, 0x50434F56, &pval);
    }
   }
  } else if (tag_idx>=0) {
   char *tag_name = gf_itags_get_name(tag_idx);
   id3dmx_set_string(pid, tag_name, data, 0);
  } else {
   char szTag[1024];
   char *tag_name = szTag;
   sprintf(tag_name, "tag_%s", gf_4cc_to_str(tag));

   if ((tag>>24)=='T') {
    id3dmx_set_string(pid, szTag, data, 1);
   } else {
    GF_PropertyValue pval;
    pval.type = 16;
    pval.value.string = data;
    pval.value.string_length = fsize;
    gf_filter_pid_set_property_dyn(pid, szTag, &pval);
   }
  }
  size -= fsize;
 }
 __ZN24QScopedPointerPodDeleter7cleanupEPv(bs);
 if (buffer) gf_free(buffer);
}