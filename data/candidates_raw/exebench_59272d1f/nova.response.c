static void func0(struct rpc_wait_queue *queue, int priority)
{
	unsigned int old, new;

	old = queue->priority;
	while (1) {
		if (old == 0)
			new = priority;
		else
			new = old - 1;
		if (queue->priority == old)
			break;
		old = cmpxchg(&queue->priority, old, new);
	}
}