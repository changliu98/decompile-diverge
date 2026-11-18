int raid6_next_disk(int disk, int raid_disks)
{
	int ret;

	disk++;
	if (disk < raid_disks) {
		ret = disk;
		goto out;
	}

	disk = 0;
out:
	return disk;
}