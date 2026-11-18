static inline void a_or(struct context_entry *context,
					    u64 value)
{
	context->lo |= value;
}