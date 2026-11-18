static inline struct i915_request *
f(struct i915_active_request *active)
{
	return active->requests++;
}