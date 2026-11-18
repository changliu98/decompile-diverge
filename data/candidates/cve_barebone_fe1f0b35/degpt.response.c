u32 GetHintFormat(GF_TrackBox *trak)

{
  GF_Box *pGVar1;
  u32 *puVar2;
  u32 local_2c;
  GF_Box *a;
  GF_HintMediaHeaderBox *hmhd;
  GF_TrackBox *trak_local;
  u32 local_c;
  
  pGVar1 = trak->Media->information->InfoHeader;
  if (pGVar1->type == 0x686d6864) {
    if ((pGVar1 == (GF_Box *)0x0) || (pGVar1[1].type == 0)) {
      puVar2 = gf_list_get(trak->Media->information->sampleTable->SampleDescription->child_boxes,0);
      if (pGVar1 == (GF_Box *)0x0) {
        if (puVar2 == (u32 *)0x0) {
          local_2c = 0;
        }
        else {
          local_2c = *puVar2;
        }
        local_c = local_2c;
      }
      else {
        if (puVar2 != (u32 *)0x0) {
          pGVar1[1].type = *puVar2;
        }
        local_c = pGVar1[1].type;
      }
    }
    else {
      local_c = pGVar1[1].type;
    }
  }
  else {
    local_c = 0;
  }
  return local_c;
}