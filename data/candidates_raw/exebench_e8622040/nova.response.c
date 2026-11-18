static int func0(struct btrfs_raid_bio *rbio,
				      int nr_data)
{
	int ret;

	if (rbio->nr_data > nr_data) {
		rbio->nr_data = nr_data;
		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}