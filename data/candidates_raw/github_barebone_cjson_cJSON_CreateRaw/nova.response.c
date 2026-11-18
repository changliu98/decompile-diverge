static struct inode *func0(struct super_block *sb)
{
	struct v9fs_inode *v9inode;
	struct inode *inode;

	v9inode = kmem_cache_alloc(&v9fs_inode_cache, GFP_KERNEL);
	if (!v9inode)
		goto error;

	
	v9inode->fscache = NULL;

	inode = &v9inode->vfs_inode;
	inode->i_sb = sb;
	if (inode_init_always(inode, &v9fs_inode_inode_fops)!= 0)
		goto error_init_inode;

	return inode;

error_init_inode:
	kmem_cache_free(&v9fs_inode_cache, v9inode);
error:
	return NULL;
}