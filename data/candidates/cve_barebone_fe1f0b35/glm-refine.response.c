u32 __cdecl GetHintFormat(GF_TrackBox *trak)
{
  GF_Box *hmhd; // [rsp+18h] [rbp-18h]
  GF_Box *a;    // [rsp+10h] [rbp-20h]

  hmhd = trak->Media->information->InfoHeader;
  
  // 1752000612 is the FourCC value for 'hmhd' (Hint Media Header)
  if ( !hmhd || hmhd->type != 1752000612 )
    return 0;

  // hmhd[1] represents the adjacent memory field, likely a cached format type or extended box union
  if ( hmhd[1].type )
    return hmhd[1].type;

  a = (GF_Box *)gf_list_get(trak->Media->information->sampleTable->SampleDescription->child_boxes, 0);
  
  if ( a )
    hmhd[1].type = a->type;

  return hmhd[1].type;
}