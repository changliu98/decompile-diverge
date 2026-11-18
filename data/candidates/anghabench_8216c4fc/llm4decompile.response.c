u64 create_ce_flags(unsigned int stage)
{
	return (u64)stage << CE_STAGESHIFT;
}