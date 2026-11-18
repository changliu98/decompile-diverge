static inline int func0(struct mon_msg *monmsg)
{
	return monmsg->pos += sizeof(struct mon_bin_hdr);
}