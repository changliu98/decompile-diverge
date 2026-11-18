/* WARNING: Removing unreachable block (ram,0x001014cb) */

GF_Err gf_avc_change_vui(GF_AVCConfig *avcc,GF_VUIInfo *vui_info)

{
  u8 uVar1;
  u32 uVar2;
  GF_BitStream *bs;
  GF_BitStream *mod_00;
  u8 *puVar3;
  u32 emulation_bytes;
  u32 no_emulation_buf_size;
  u8 *no_emulation_buf;
  GF_AVCConfigSlot *slc;
  s32 idx;
  u32 flag;
  u32 bit_offset;
  u32 i;
  AVCState avc;
  GF_BitStream *mod;
  GF_BitStream *orig;
  GF_VUIInfo *vui_info_local;
  GF_AVCConfig *avcc_local;
  
  memset(&avc,0,0x9438);
  avc.sps_active_idx = -1;
  i = 0;
  while( true ) {
    do {
      slc = gf_list_enum(avcc->sequenceParameterSets,&i);
      if (slc == (GF_AVCConfigSlot *)0x0) {
        return GF_OK;
      }
      no_emulation_buf = (u8 *)0x0;
      idx = gf_avc_read_sps(slc->data,(uint)slc->size,&avc,0,&bit_offset);
    } while (idx < 0);
    no_emulation_buf = gf_malloc((long)(int)(slc->size - 1));
    uVar2 = gf_media_nalu_remove_emulation_bytes(slc->data + 1,no_emulation_buf,slc->size - 1);
    bs = gf_bs_new(no_emulation_buf,(ulong)uVar2,0);
    gf_bs_read_data(bs,no_emulation_buf,uVar2);
    gf_bs_seek(bs,0);
    mod_00 = gf_bs_new((u8 *)0x0,0,1);
    if (bit_offset < 8) break;
    for (; bit_offset != 8; bit_offset = bit_offset - 1) {
      flag = gf_bs_read_int(bs,1);
      gf_bs_write_int(mod_00,flag,1);
    }
    avc_hevc_vvc_rewrite_vui(vui_info,bs,mod_00,0x21);
    while (uVar1 = gf_bs_bits_available(bs), uVar1 != '\0') {
      flag = gf_bs_read_int(bs,1);
      gf_bs_write_int(mod_00,flag,1);
    }
    gf_bs_del(bs);
    gf_free(no_emulation_buf);
    gf_bs_get_content(mod_00,&no_emulation_buf,&flag);
    uVar2 = gf_media_nalu_emulation_bytes_add_count(no_emulation_buf,flag);
    if ((uint)slc->size < flag + uVar2 + 1) {
      puVar3 = gf_realloc(slc->data,(ulong)(flag + uVar2 + 1));
      slc->data = puVar3;
    }
    uVar2 = gf_media_nalu_add_emulation_bytes(no_emulation_buf,slc->data + 1,flag);
    slc->size = (short)uVar2 + 1;
    gf_bs_del(mod_00);
    gf_free(no_emulation_buf);
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("bit_offset >= 8","/work/harness.c",0x186,
                "GF_Err gf_avc_change_vui(GF_AVCConfig *, GF_VUIInfo *)");
}