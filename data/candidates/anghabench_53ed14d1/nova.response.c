static inline u64 mv78xx0_mbus_win_cfg_offset(u64 param1)
{
	u64 tmp;
	tmp = (param1 < 9? (param1 <= 1? 0 : 2304) : 0) + (param1 * 16);
	return tmp;
}