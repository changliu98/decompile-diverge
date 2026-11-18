static inline int func0(struct cs_etm_queue *etmq,
					     u64 trace_chan_id)
{
	int trace_chan_idx;

	trace_chan_idx = etmq->trace_chan_id ^ trace_chan_id;
	etmq->trace_chan_id ^= trace_chan_id;

	return trace_chan_idx;
}