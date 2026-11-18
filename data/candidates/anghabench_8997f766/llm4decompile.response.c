int raid6_next_disk(int disk, int raid_disks)
{
	return (disk + 1 < raid_disks) ? disk + 1 : 0;
}