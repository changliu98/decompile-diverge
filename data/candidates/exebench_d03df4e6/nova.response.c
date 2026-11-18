static void SN_set_nb_iters(struct dma_desc *p, dma_addr_t addr)
{
	p->des2 = addr;
}