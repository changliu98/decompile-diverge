static struct mlxsw_sp_fid *
set_iter_next(struct mlxsw_sp_bridge_device *bridge_device)
{
	struct mlxsw_sp_fid_family *fid_family = bridge_device->fid_family;
	struct mlxsw_sp_fid *fid;
	unsigned long fid_index;
	unsigned int fid_count;

	if (!bridge_device->vids_count) {
		fid = NULL;
		goto out;
	}

	fid = bridge_device->fid_head;
	fid_count = fid->fid_index;

	if (fid->fid_index) {
		bridge_device->fid_head = fid->fid_next;
		goto out;
	}

	bridge_device->fid_head = NULL;
	fid_index = bridge_device->fid_index + 1;
	while (fid_index < fid_family->fids_count) {
		if (fid_family->fids[fid_index]) {
			bridge_device->fid_head = fid_family->fids[fid_index];
			break;
		}
		fid_index++;
	}
	bridge_device->fid_index = fid_index;

out:
	fid_count = fid->fid_count;
	return fid;
}