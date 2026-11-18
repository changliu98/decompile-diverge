static inline void func0(struct intel_engine_cs *engine)
{
	++engine->stats.tasklet_count;
}