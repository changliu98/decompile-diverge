static int func0(struct scsi_cmnd *scp, int ip)
{
	int ret;

	if (ip == 3) {
		ret = 1;
	} else if (ip == 0) {
		if (scp->cmd_len == 16) {
			scp->cmnd[2] = 0x0f;
			scp->cmnd[3] = 0x00;
			scp->cmnd[4] = 0x1f;
		} else if (scp->cmd_len == 32) {
			scp->cmnd[2] = 0xff;
			scp->cmnd[3] = 0xff;
			scp->cmnd[4] = 0xff;
			scp->cmnd[5] = 0xff;
			scp->cmnd[6] = 0x00;
		} else {
			scp->cmnd[2] = 0;
			scp->cmnd[3] = 0;
			scp->cmnd[4] = 0;
			scp->cmnd[5] = 0;
		}
	} else {
		ret = 0;
	}
	return ret;
}