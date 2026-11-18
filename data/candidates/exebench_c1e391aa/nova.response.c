static inline u8 set_bit(u8 *bitmap, enum CUDBG_DBG_ENTITY_TYPE type)
{
	u8 val = bitmap[type >> 3];

	val |= (1 << (type & 0x07));
	bitmap[type >> 3] = val;
	return val;
}