GF_Err __cdecl gf_avc_change_vui(GF_AVCConfig *avcc, GF_VUIInfo *vui_info)
{
  u8 *v2; // rax
  __int16 v3; // ax
  u32 emulation_bytes; // [rsp+0h] [rbp-9480h]
  u32 no_emulation_buf_size; // [rsp+4h] [rbp-947Ch]
  u8 *no_emulation_buf; // [rsp+8h] [rbp-9478h] BYREF
  GF_AVCConfigSlot *slc; // [rsp+10h] [rbp-9470h]
  s32 idx; // [rsp+18h] [rbp-9468h]
  u32 flag; // [rsp+1Ch] [rbp-9464h] BYREF
  u32 bit_offset; // [rsp+20h] [rbp-9460h] BYREF
  u32 i; // [rsp+24h] [rbp-945Ch] BYREF
  AVCState avc; // [rsp+28h] [rbp-9458h] BYREF
  GF_BitStream *mod; // [rsp+9460h] [rbp-20h]
  GF_BitStream *orig; // [rsp+9468h] [rbp-18h]
  GF_VUIInfo *vui_infoa; // [rsp+9470h] [rbp-10h]
  GF_AVCConfig *avcca; // [rsp+9478h] [rbp-8h]

  avcca = avcc;
  vui_infoa = vui_info;
  orig = 0LL;
  memset(&avc, 0, sizeof(avc));
  avc.sps_active_idx = -1;
  i = 0;
  while ( 1 )
  {
    slc = (GF_AVCConfigSlot *)gf_list_enum(avcca->sequenceParameterSets, &i);
    if ( !slc )
      break;
    no_emulation_buf = 0LL;
    idx = gf_avc_read_sps(slc->data, slc->size, &avc, 0, &bit_offset);
    if ( idx >= 0 )
    {
      no_emulation_buf = (u8 *)gf_malloc(slc->size - 1);
      no_emulation_buf_size = gf_media_nalu_remove_emulation_bytes(
                                (const u8 *)slc->data + 1,
                                no_emulation_buf,
                                slc->size - 1);
      orig = gf_bs_new(no_emulation_buf, no_emulation_buf_size, 0);
      gf_bs_read_data(orig, no_emulation_buf, no_emulation_buf_size);
      gf_bs_seek(orig, 0LL);
      mod = gf_bs_new(0LL, 0LL, 1u);
      if ( bit_offset < 8 )
        __assert_fail(
          "bit_offset >= 8",
          "/work/harness.c",
          0x186u,
          "GF_Err gf_avc_change_vui(GF_AVCConfig *, GF_VUIInfo *)");
      while ( bit_offset != 8 )
      {
        flag = gf_bs_read_int(orig, 1u);
        gf_bs_write_int(mod, flag, 1);
        --bit_offset;
      }
      avc_hevc_vvc_rewrite_vui(vui_infoa, orig, mod, 0x21u);
      while ( gf_bs_bits_available(orig) )
      {
        flag = gf_bs_read_int(orig, 1u);
        gf_bs_write_int(mod, flag, 1);
      }
      gf_bs_del(orig);
      orig = 0LL;
      gf_free(no_emulation_buf);
      gf_bs_get_content(mod, &no_emulation_buf, &flag);
      emulation_bytes = gf_media_nalu_emulation_bytes_add_count(no_emulation_buf, flag);
      if ( emulation_bytes + flag + 1 > slc->size )
      {
        v2 = (u8 *)chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(slc->data, emulation_bytes + flag + 1);
        slc->data = v2;
      }
      v3 = gf_media_nalu_add_emulation_bytes(no_emulation_buf, slc->data + 1, flag);
      slc->size = v3 + 1;
      gf_bs_del(mod);
      gf_free(no_emulation_buf);
    }
    else if ( orig )
    {
      gf_bs_del(orig);
    }
  }
  return 0;
}