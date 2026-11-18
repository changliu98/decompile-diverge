int __cdecl read_new_config_info(WavpackContext *wpc, WavpackMetadata *wpmd)
{
  unsigned __int8 *v2; // rax
  unsigned __int8 *v3; // rax
  unsigned __int8 *v4; // rax
  unsigned __int8 *v5; // rax
  int i; // [rsp+0h] [rbp-30h]
  int nchans; // [rsp+4h] [rbp-2Ch]
  unsigned __int8 *byteptr; // [rsp+8h] [rbp-28h]
  unsigned __int8 *byteptra; // [rsp+8h] [rbp-28h]
  unsigned __int8 *byteptrb; // [rsp+8h] [rbp-28h]
  unsigned __int8 *byteptrc; // [rsp+8h] [rbp-28h]
  int bytecnt; // [rsp+14h] [rbp-1Ch]
  int bytecnta; // [rsp+14h] [rbp-1Ch]
  int bytecntb; // [rsp+14h] [rbp-1Ch]
  int bytecntc; // [rsp+14h] [rbp-1Ch]

  bytecnt = wpmd->byte_length;
  byteptr = (unsigned __int8 *)wpmd->data;
  wpc->version_five = 1;
  wpc->channel_layout = 0;
  wpc->config.qmode = 0;
  wpc->file_format = 0;
  if ( wpc->channel_reordering )
  {
    free(wpc->channel_reordering);
    wpc->channel_reordering = 0LL;
  }
  if ( !bytecnt )
    return 1;
  wpc->file_format = *byteptr;
  v2 = byteptr + 1;
  byteptra = byteptr + 2;
  wpc->config.qmode = *v2 | wpc->config.qmode & 0xFFFFFF00;
  bytecnta = bytecnt - 2;
  if ( !bytecnta )
    return 1;
  v3 = byteptra;
  byteptrb = byteptra + 1;
  wpc->channel_layout = *v3 << 16;
  bytecntb = bytecnta - 1;
  if ( !bytecntb )
  {
    wpc->channel_layout += wpc->config.num_channels;
    return 1;
  }
  v4 = byteptrb;
  byteptrc = byteptrb + 1;
  nchans = *v4;
  wpc->channel_layout += nchans;
  bytecntc = bytecntb - 1;
  if ( !bytecntc )
    return 1;
  if ( bytecntc <= nchans )
  {
    wpc->channel_reordering = (unsigned __int8 *)malloc(nchans);
    if ( wpc->channel_reordering )
    {
      for ( i = 0; i < nchans; ++i )
      {
        if ( bytecntc )
        {
          v5 = byteptrc++;
          wpc->channel_reordering[i] = *v5;
          --bytecntc;
        }
        else
        {
          wpc->channel_reordering[i] = i;
        }
      }
    }
    return 1;
  }
  return 0;
}