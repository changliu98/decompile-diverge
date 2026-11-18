int stszin(int size)

{
  uint32_t uVar1;
  uint32_t fsize;
  uint32_t ofs;
  int cnt;
  int size_local;
  int local_c;
  
  u32in();
  u32in();
  mp4config.frame.ents = u32in();
  mp4config.frame.data = malloc((ulong)(mp4config.frame.ents + 1) << 2);
  if (mp4config.frame.data == (uint32_t *)0x0) {
    local_c = -1;
  }
  else {
    ofs = 0;
    *mp4config.frame.data = 0;
    for (cnt = 0; local_c = size, (uint)cnt < mp4config.frame.ents; cnt = cnt + 1) {
      uVar1 = u32in();
      ofs = uVar1 + ofs;
      if ((uint)mp4config.frame.maxsize < uVar1) {
        mp4config.frame.maxsize = uVar1;
      }
      mp4config.frame.data[cnt + 1] = ofs;
      if (ofs < mp4config.frame.data[cnt]) {
        return -1;
      }
    }
  }
  return local_c;
}