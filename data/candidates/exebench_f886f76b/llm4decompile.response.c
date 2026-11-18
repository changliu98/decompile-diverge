int
proc_alloc_inum(struct vnode *vp, struct ucred *cred, ino_t *inump)
{
	*inump = 1;
	return (0);
}