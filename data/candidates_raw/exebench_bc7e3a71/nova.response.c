static int func0(struct mtd_info *mtd, int section)
{
	u32 ret;

	switch (section) {
	case 0:
		ret = mtd->writesize;
		break;
	case 1:
		ret = mtd->oobsize;
		break;
	default:
		ret = 0;
	}

	return ret;
}