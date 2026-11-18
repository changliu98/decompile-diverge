static inline void setarr(struct rq *rq, bool is_idle)
{
	rq->is_idle = is_idle;
}