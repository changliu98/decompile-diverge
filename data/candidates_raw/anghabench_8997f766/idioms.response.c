int next_disk(int disk, int raid_disks)
{
  if (disk + 1 < raid_disks)
    return disk + 1;
  else
    return 0;
}