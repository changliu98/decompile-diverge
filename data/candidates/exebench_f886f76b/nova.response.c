static int proc_alloc_inum(struct ci_hdrc *ci)
{
	ci->fsm.proc_alloc_inum = 1;
	return 0;
}