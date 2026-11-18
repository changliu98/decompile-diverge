static int store_update(struct dvb_frontend *fe,
				   struct dvb_diseqc_master_cmd *cmd)
{
	struct firedtv *fdtv = fe->sec_priv;
	unsigned int i, len, pos;
	u8 buf[16];
	int ret;

	do {
		len = min((unsigned int)sizeof(buf), fdtv->ca_data_length);
		if (len < fdtv->ca_data_length) {
			ret = fdtv_ca_get_data(fdtv, fdtv->ca_data_off,
					       buf, len);
			if (ret)
				return ret;
		}
		fdtv->ca_data_off += len;
		fdtv->ca_data_length -= len;

		pos = cmd->msg_len % sizeof(buf);
		memcpy(buf + pos, cmd->msg, cmd->msg_len);
		buf[0] = 0x02;
		buf[1] = cmd->msg_len;
		buf[2] = cmd->msg_type;
		buf[3] = cmd->initiator;
		buf[4] = 0;
		buf[5] = 0;
		buf[6] = 0;
		buf[7] = 0;

		ret = fdtv_ca_write(fdtv, buf, len);
		if (ret)
			return ret;
	} while (fdtv->ca_data_length);

	fdtv->ca_data_off = 1;
	fdtv->ca_data_length = cmd->msg_len;
	fdtv->ca_data_off = cmd->msg_len;
	fdtv->ca_data_length = cmd->msg_len;

	fdtv_ca_write_attribute(fdtv);

	ret = 0;

	for (i = 0; i < cmd->msg_len; i++)
		;