static void decode_mode10_short_delta(u32 reg, u32 *p_phy_id, u32 *p_phy_rev,
				 u32 *p_phy_flags)
{
	*p_phy_flags = reg & 0x1f;
	if (*p_phy_flags & 0x10)
		*p_phy_flags |= ~0x1f;
	*p_phy_flags <<= 1;

	*p_phy_id = (reg & 0x1e0) >> 5;
	if (*p_phy_id & 0x10)
		*p_phy_id |= ~0x1f;

	*p_phy_rev = (reg & 0x7800) >> 10;
	if (*p_phy_rev & 0x10)
		*p_phy_rev |= ~0x1f;
}