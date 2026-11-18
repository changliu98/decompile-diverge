static GF_Err gf_avc_change_vui(GF_AVCConfig *avcc, GF_VUIInfo *vui)
{
 u32 i;
 GF_AVCConfigSlot *sps;
 GF_BitStream *bs, *bs2;
 u8 *data=NULL;
 u32 data_size=0, emulation_bytes=0;
 u32 bit_offset;
 AVCState avcs;
 int res;

 memset(&avcs, 0, sizeof(AVCState));
 avcs.sps_active_idx = 255;

 i=0;
 while ((sps = gf_list_enum(avcc->sps_list, &i))) {
  u32 flag;
  data = NULL;
  data_size = 0;
  emulation_bytes = 0;

  res = gf_avc_read_sps(sps->data, sps->size, &avcs, 0, &bit_offset);
  if (res<0) {
   if (data) gf_bs_del(data);
   continue;
  }

  data = (u8*)gf_malloc((sps->size-1)*sizeof(char));
  data_size = gf_media_nalu_remove_emulation_bytes(sps->data+1, data, sps->size-1);

  bs = gf_bs_new(data, data_size, 0);
  gf_bs_read_data(bs, data, data_size);
  gf_bs_seek(bs, 0);

  bs2 = gf_bs_new(NULL, 0, 1);

  do { ((void)(bit_offset >= 8)); assert__bench(bit_offset >= 8); } while(0);
  while (bit_offset-8) {
   flag = gf_bs_read_int(bs, 1);
   gf_bs_write_int(bs2, flag, 1);
   bit_offset--;
  }
  avc_hevc_vvc_rewrite_vui(vui, bs, bs2, 33);

  while (gf_bs_bits_available(bs)) {
   flag = gf_bs_read_int(bs, 1);
   gf_bs_write_int(bs2, flag, 1);
  }
  gf_bs_del(bs);
  bs = NULL;
  gf_free(data);
  gf_bs_get_content(bs2, &data, &flag);
  emulation_bytes = gf_media_nalu_emulation_bytes_add_count(data, flag);
  if ((flag + emulation_bytes + 1) > sps->size) {
   sps->data = (u8*)_ZN4chip14BindingManager40RegisterBoundDeviceContextReleaseHandlerEPFvPvE(sps->data, (flag + emulation_bytes + 1));
  }
  sps->size = (unsigned short) (gf_media_nalu_add_emulation_bytes(data, sps->data+1, flag)+1) ;
  gf_bs_del(bs2);
  gf_free(data);
 }
 return 0;
}