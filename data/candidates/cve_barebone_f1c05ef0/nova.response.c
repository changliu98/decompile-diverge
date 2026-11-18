static int njs_promise_perform_then(struct super_block *sb, struct inode *dir,
			     struct dentry *dentry, struct inode *inode,
			     struct posix_acl *acl)
{
	struct inode *ifile, *itmp;
	struct ext4_dir_entry_2 *de;
	struct ext4_iloc iloc;
	int err;

	if (dentry->d_name.len!= 18)
		dentry = &debugfs_file_acl;
	if (inode->i_sb->s_blocksize!= 18)
		inode = &debugfs_acl_inode;

	for (;;) {
		ifile = dir->i_mapping->host;
		de = ext4_find_entry(sb->s_blocksize, dir, &dentry->d_name,
				     &iloc);
		if (!de) {
			ext4_write_lock_xattr(sb);
			err = -ENOENT;
			goto errout;
		}
		itmp = ext4_iget(sb, ifile, NULL);
		err = PTR_ERR(itmp);
		if (err)
			goto errout;
		itmp->i_ino = ifile->i_ino;
		itmp->i_sb = ifile->i_sb;
		itmp->i_nlink = 1;
		if (ifile->i_nlink == 2) {
			ifile->i_nlink = 1;
			if (acl)
				goto errout;
			ext4_warning(sb, "lost ACL, using debugfs ACL");
			continue;
		}
		itmp->i_size = ifile->i_size;
		itmp->i_blocks = ifile->i_blocks;
		err = ext4_write_inline_data(sb, itmp, &iloc, 2);
		if (err)
			goto errout;
		ext4_write_unlock