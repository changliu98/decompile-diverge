int read_new_config_info(WavpackContext *wpc,WavpackMetadata *wpmd)

{
  int iVar1;
  uchar *puVar2;
  uint uVar3;
  int i;
  int nchans;
  uchar *byteptr;
  int bytecnt;
  WavpackMetadata *wpmd_local;
  WavpackContext *wpc_local;
  
  iVar1 = wpmd->byte_length;
  puVar2 = wpmd->data;
  wpc->version_five = 1;
  wpc->channel_layout = 0;
  (wpc->config).qmode = 0;
  wpc->file_format = '\0';
  if (wpc->channel_reordering != (uchar *)0x0) {
    free(wpc->channel_reordering);
    wpc->channel_reordering = (uchar *)0x0;
  }
  if (iVar1 != 0) {
    wpc->file_format = *puVar2;
    (wpc->config).qmode = (wpc->config).qmode & 0xffffff00U | (uint)puVar2[1];
    if (iVar1 != 2) {
      wpc->channel_layout = (uint)puVar2[2] << 0x10;
      if (iVar1 == 3) {
        wpc->channel_layout = (wpc->config).num_channels + wpc->channel_layout;
      }
      else {
        byteptr = puVar2 + 4;
        uVar3 = (uint)puVar2[3];
        wpc->channel_layout = uVar3 + wpc->channel_layout;
        bytecnt = iVar1 + -4;
        if (bytecnt != 0) {
          if ((int)uVar3 < bytecnt) {
            return 0;
          }
          puVar2 = malloc((long)(int)uVar3);
          wpc->channel_reordering = puVar2;
          if (wpc->channel_reordering != (uchar *)0x0) {
            for (i = 0; i < (int)uVar3; i = i + 1) {
              if (bytecnt == 0) {
                wpc->channel_reordering[i] = (uchar)i;
              }
              else {
                wpc->channel_reordering[i] = *byteptr;
                bytecnt = bytecnt + -1;
                byteptr = byteptr + 1;
              }
            }
          }
        }
      }
    }
  }
  return 1;
}