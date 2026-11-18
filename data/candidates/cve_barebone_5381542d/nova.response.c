static int adjust_plines_for_skipcol(struct btrfs_fs_info *fs_info)
{
	int num_workers;
	int num_bitmaps;
	int num_disks;
	int min_disks;

	if (!fs_info->qgroup_auto_xmit_limit)
		num_workers = 0;
	else {
		num_bitmaps = fs_info->qgroup_info.num_bitmaps;
		num_disks = btrfs_num_clusters(fs_info) - num_bitmaps;
		if (fs_info->qgroup_auto_xmit_limit >= num_disks) {
			min_disks = fs_info->qgroup_auto_xmit_limit - num_disks;
			num_workers = min_disks /
				(num_bitmaps + btrfs_qgroup_rsv_ratio(fs_info)) +
				1;
		} else
			num_workers = 0;
	}
	return num_workers;
}