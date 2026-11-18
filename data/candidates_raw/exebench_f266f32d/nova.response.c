static void func0(void *info, u64 start, u64 end, u64 br_type)
{
	struct msr_hwp_request *hwp_req = info;
	u64 *msrpm = &hwp_req->hwp_req;
	u64 *msr_start = &hwp_req->msr_start;
	u64 *msr_end = &hwp_req->msr_end;

	__smp_store_u64(msrpm, start);
	__smp_store_u64(msr_start, end);
	__smp_store_u64(msr_end, br_type);
}