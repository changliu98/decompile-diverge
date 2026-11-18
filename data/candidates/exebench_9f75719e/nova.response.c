static void motorctrl_forward(struct fm10k_mbx_info *mbx)
{
	mbx->mbx_lock += 0x80;
}