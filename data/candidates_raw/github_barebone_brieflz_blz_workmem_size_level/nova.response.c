static inline long func0(long val, int atomic)
{
	long ret;

	switch (atomic) {
	case 0:
		ret = __func0(&val);
		break;
	case 1:
		ret = __func016(&val);
		break;
	case 2:
		ret = __func032(&val);
		break;
	case 4:
		ret = __func064(&val);
		break;
	case -1:
	default:
		ret = -1;
		break;
	}
	return ret;
}