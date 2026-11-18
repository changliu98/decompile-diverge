GF_Err __cdecl gf_avc_change_vui(GF_AVCConfig *avcc, GF_VUIInfo *vui_info)
{
  u8 *no_emulation_buf;
  u32 no_emulation_buf_size;
  u32 emulation_bytes;
  u32 bit_offset;
  u32 flag;
  u32 i;
  s32 idx;
  GF_AVCConfigSlot *slc;
  AVCState avc;
  GF_BitStream *mod = NULL;
  GF_BitStream *orig = NULL;

  memset(&avc, 0, sizeof(avc));
  avc.sps_active_idx = -1;
  
  for (i = 0; ; i++)
  {
    slc = (GF_AVCConfigSlot *)gf_list_enum(avcc->sequenceParameterSets, &i);
    if (!slc)
      break;

    no_emulation_buf = NULL;
    idx = gf_avc_read_sps(slc->data, slc->size, &avc, 0, &bit_offset);
    
    if (idx >= 0)
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
      
      // Original code asserts that bit_offset >= 8
      assert(bit_offset >= 8);
      
      // Copy bits up to the VUI section
      while (bit_offset != 8)
      {
        flag = gf_bs_read_int(orig, 1u);
        gf_bs_write_int(mod, flag, 1);
        --bit_offset;
      }
      
      // Rewrite VUI parameters
      avc_hevc_vvc_rewrite_vui(vui_info, orig, mod, 0x21u);
      
      // Copy remaining bits
      while (gf_bs_bits_available(orig))
      {
        flag = gf_bs_read_int(orig, 1u);
        gf_bs_write_int(mod, flag, 1);
      }
      
      gf_bs_del(orig);
      orig = NULL;
      gf_free(no_emulation_buf);
      
      // Retrieve modified bitstream
      gf_bs_get_content(mod, &no_emulation_buf, &flag);
      
      // Calculate required size with emulation prevention bytes
      emulation_bytes = gf_media_nalu_emulation_bytes_add_count(no_emulation_buf, flag);
      if (emulation_bytes + flag + 1 > slc->size)
      {
        // Reallocate the NAL unit buffer if the new size is larger
        slc->data = (u8 *)gf_realloc(slc->data, emulation_bytes + flag + 1);
      }
      
      // Write back the data with emulation bytes
      u16 v3 = gf_media_nalu_add_emulation_bytes(no_emulation_buf, slc->data + 1, flag);
      slc->size = v3 + 1;
      
      gf_bs_del(mod);
      gf_free(no_emulation_buf);
    }
    else if (orig)
    {
      gf_bs_del(orig);
      orig = NULL;
    }
  }
  
  return 0;
}