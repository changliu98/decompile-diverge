void func0(struct vnic_wq *wq, unsigned int cq_index,
	unsigned int fetch_index, struct vnic_wq_buf *buf)
{
	unsigned int index_incr;
	unsigned int wrap_point;
	unsigned int fetch_index_incr;
	unsigned int fetch_wrap_point;
	unsigned int fetch_index_diff;
	unsigned int index_diff;

	index_incr = fetch_index % wq->ring.desc_count;
	wrap_point = (fetch_index - index_incr) / wq->ring.desc_count;

	fetch_index_incr = (fetch_index - cq_index) % wq->ring.desc_count;
	fetch_wrap_point = (fetch_index - cq_index - fetch_index_incr) /
		wq->ring.desc_count;

	fetch_index_diff = fetch_wrap_point - wrap_point;
	index_diff = index_incr - fetch_index_incr;

	if (fetch_index_diff < 0)
		fetch_index_diff += wq->ring.desc_count;

	if (index_diff < 0)
		index_diff += wq->ring.desc_count;

	buf->index = cq_index + index_diff;
	buf->fetch_index = fetch_index + fetch_index_diff;
	buf->index_to_fetch = buf->index + index_incr;
	buf->next_index_to_fetch = buf->fetch_index + fetch_index_incr;
}