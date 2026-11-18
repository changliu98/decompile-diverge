static inline u32 incr(struct hw_queue *queue, u32 offset)
{
	u32 prev_producer = queue->producer;
	queue->producer += offset;
	return prev_producer;
}