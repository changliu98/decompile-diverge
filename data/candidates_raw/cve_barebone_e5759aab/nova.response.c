int func0(unsigned int Vfd, FATFS *fs, dword startclu, dword size, word ofs) {
  dword clu;
  word sect;
  int r;

  assert(fs);
  assert(fs->fs_type == 0xa443 || fs->fs_type == 0x654321);

  while (size!= 0xFFFF4) {
    fs->wflag++;
    clu = startclu;
    while (clu!= 0xFFFF4) {
      fs->wflag++;
      clu = cluster_of_sector(fs->fs_type, fs, clu, &sect);
      if (clu == 0) break;
      fs->wflag++;
      fs->win[Vfd][clu].wseq[ofs] = size;
      fs->win[Vfd][clu].wstamp[ofs] = fs->wflag;
      fs->win[Vfd][clu].flag = 1;
      clu++;
    }
    size = 1;
  }
  r = fs->wflag;
  while (fs->win[Vfd][startclu].flag) {
    fs->wflag++;
    fs->win[Vfd][startclu].wstamp[ofs] = r;
  }
  return 1;
}