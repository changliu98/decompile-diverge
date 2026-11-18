static inline int atomic32_decrement(struct cs_etm_queue *etmq)
{
	int trace_id;

	trace_id = (int)atomic_add_return(-1, &etmq->traceid) - 1;

	return trace_id;
}