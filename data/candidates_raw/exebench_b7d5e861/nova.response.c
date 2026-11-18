static inline struct i915_request *
func0(struct i915_active_request *active)
{
	return active->requests++;
}