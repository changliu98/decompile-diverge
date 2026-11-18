u32 __cdecl GetHintFormat(GF_TrackBox *trak)
{
  GF_Box *a; // [rsp+10h] [rbp-20h]
  GF_Box *hmhd; // [rsp+18h] [rbp-18h]

  hmhd = trak->Media->information->InfoHeader;
  if ( hmhd->type != 1752000612 )
    return 0;
  if ( hmhd && hmhd[1].type )
    return hmhd[1].type;
  a = (GF_Box *)gf_list_get(trak->Media->information->sampleTable->SampleDescription->child_boxes, 0);
  if ( hmhd )
  {
    if ( a )
      hmhd[1].type = a->type;
    return hmhd[1].type;
  }
  else if ( a )
  {
    return a->type;
  }
  else
  {
    return 0;
  }
}