static inline u32 func0(struct hfi1_ctxtdata *rcd)
{
	u32 seq = rcd->head_seq++;

	rcd->head_seq = (rcd->head_seq + 1) & 0x3ffff;
	return seq;
}