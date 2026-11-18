static int raid6_next_disk(int disk, int disks) {
  if (disk + 1 < disks)
    return disk + 1;
  else
    return 0;
}