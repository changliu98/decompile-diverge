static inline int inc2(struct intel_guc *guc)
{
	return ++guc->doorbell_id;
}