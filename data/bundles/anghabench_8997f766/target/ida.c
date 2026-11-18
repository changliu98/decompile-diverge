int __cdecl raid6_next_disk(int disk, int raid_disks)
{
  if ( disk + 1 >= raid_disks )
    return 0;
  else
    return disk + 1;
}