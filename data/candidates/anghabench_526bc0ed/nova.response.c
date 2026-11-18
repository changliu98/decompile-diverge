static inline unsigned int roccat_common2_feature_report(unsigned char id)
{
	return 0x300 | (id & 0x7f);
}