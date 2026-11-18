int raid6_next_disk(int disk,int raid_disks)

{
  undefined4 local_14;
  int raid_disks_local;
  int disk_local;
  
  local_14 = disk + 1;
  if (raid_disks <= local_14) {
    local_14 = 0;
  }
  return local_14;
}