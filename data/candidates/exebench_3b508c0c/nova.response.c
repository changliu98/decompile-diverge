static inline void bnode_link_set_ref(struct cm_req_msg *req_msg,
						u8 local_ack_timeout)
{
	req_msg->alt_offset138 = (u8) ((req_msg->alt_offset138 & 0x01) |
				       (local_ack_timeout << 1));
}