static inline size_t ring_size_to_bytes(unsigned int n)
{
	return sizeof(struct ib_uverbs_ex_create_qp_resp) +
		n * sizeof(struct ib_uverbs_ex_create_qp_resp_attr);
}