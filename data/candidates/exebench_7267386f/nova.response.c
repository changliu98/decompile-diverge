static inline int _hclib_atomic_dec_release(struct csio_scsim *scm)
{
	return scm->next_lnode_idx++ - 1;
}