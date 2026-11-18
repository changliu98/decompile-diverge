static inline void func0(struct cm_req_msg *req_msg,
						u8 local_ack_timeout)
{
	req_msg->alt_offset138 = (u8) ((req_msg->alt_offset138 & 0x01) |
				       (local_ack_timeout << 1));
}