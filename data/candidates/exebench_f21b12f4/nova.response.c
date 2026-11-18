static inline void nm_writel(u32 v, struct gma_write_queue *queue)
{
	queue->last_reg = v;
}