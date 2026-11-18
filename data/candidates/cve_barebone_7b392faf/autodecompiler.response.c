__attribute__((used)) static int
xid_map_enter(struct l2tp_conn *conn, struct l2tp_data *data, u_int8_t *buf)
{
	struct l2tp_xid_map *xid;
	u_int8_t *buf_ip4 = NULL, *buf_ip6 = NULL;
	int type;
	int ret;

	if ((conn->recv_buf + sizeof(struct l2tp_data) - 4 > conn->recv_buf_ptr) ||
	    (data + sizeof(struct l2tp_data) + 4 > conn->recv_buf_ptr)) {
		ret = 0;
		goto out;
	}

	type = buf[0] >> 4;
	switch (type) {
	case 4:
		buf_ip4 = buf;
		break;
	case 6:
		buf_ip6 = buf;
		break;
	default:
		ret = 1;
		goto out;
	}

	xid = &xid_map[xid_map_next];
	xid_map_next++;
	if (xid_map_next >= 64)
		xid_map_next = 0;

	xid->tunnel_id = data->tunnel_id;
	if (buf_ip4 != NULL) {
		xid->type = 4;
		xid->peer_addr = *(u_int32_t *)(&buf_ip4[3]);
		xid->local_addr = *(u_int32_t *)(&buf_ip4[4]);
	} else if (buf_ip6 != NULL) {
		xid->type = 6;
		memcpy__bench(&xid->peer_addr, &buf_ip6[2], 16);
		memcpy__bench(&xid->local_addr, &buf_ip6[6], 16);
	}

	xid->peer_port = EXTRACT_32BITS(data + sizeof(struct l2tp_data) + 3);
	xid->local_port = EXTRACT_32BITS(data + sizeof(struct l2tp_data) + 2);

	ret = 1;
out:
	return ret;
}