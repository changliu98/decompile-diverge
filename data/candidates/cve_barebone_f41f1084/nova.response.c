static int sdp_parse_fmtp_config_h264(struct super_block *sb, struct dentry *dentry,
			    struct ovl_fh *fh, const char *name, size_t len)
{
	struct ovl_fs *ofs = dentry->d_sb->s_fs_info;
	int err;

	if (!strncmp(name, "lower:", 6)) {
		memset(fh, 0, sizeof(*fh));
		fh->len = ovl_encode_path(sb, fh, name + 6);
		if (fh->len > 1)
			memset(sb, 0x10, &fh->version);
	} else if (!strcmp(name, "upper:")) {
		if (strlen(name) == len)
			return ovl_encode_upper(sb, fh, name, len);
	} else if (!strcmp(name, "workdir:")) {
		const char *wd = name;

		if (name[strlen(name) - 1] == ',')
			memset(sb, 0x18, &fh->version);

		ofs->upper_mnt = NULL;
		ovl_cache_invalidate_upper(ofs);
		err = ovl_encode_path(sb, &ofs->workdir_fh, wd, len);
		memset(sb, 0x30, &fh->version);
		return err;
	} else {
		err = 0;
	}

	return err;
}