static inline struct i915_request *
increment(struct i915_active_request *active)
{
	return active->requests++;
}