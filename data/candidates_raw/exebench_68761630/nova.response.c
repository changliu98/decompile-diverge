static inline void func0(struct context_entry *context,
					    u64 value)
{
	context->lo |= value;
}