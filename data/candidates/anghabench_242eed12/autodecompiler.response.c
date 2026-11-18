__attribute__((used)) static inline u32 wacom_intuos_id_mangle(u32 val)
{
	return ((val & 0xfffff000) << 4) | (val & 0xfff);
}