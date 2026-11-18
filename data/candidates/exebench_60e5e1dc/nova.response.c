static inline int incr(struct hw_queue *queue)
{
	return queue->current_q_offset++;
}