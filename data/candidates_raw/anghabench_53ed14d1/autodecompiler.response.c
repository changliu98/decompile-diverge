__attribute__((used)) static inline u64 ZIP_QUEX_SLI_GPA(u64 param1)
{
	u64 offset;

	if (param1 < 8)
		offset = param1 * 0x10;
	else
		offset = 0x900 + ((param1 - 8) * 0x10);
	return offset;
}