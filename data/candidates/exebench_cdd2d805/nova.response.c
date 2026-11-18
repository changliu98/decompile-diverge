static inline void atomic_retain(struct intel_engine_cs *engine)
{
	++engine->stats.tasklet_count;
}