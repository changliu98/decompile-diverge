static const char *func0(u8 status)
{
	const char *str = NULL;
	static const char unknown[] = "unknown";

	switch (status) {
	case MTHCA_CMD_STAT_OK:
		str = "OK";
		break;
	case MTHCA_CMD_STAT_DB_BUSY:
		str = "device busy";
		break;
	case MTHCA_CMD_STAT_DB_ERR:
		str = "DB error";
		break;
	case MTHCA_CMD_STAT_INVALID:
		str = "invalid command";
		break;
	case MTHCA_CMD_STAT_DB_NO_REC:
		str = "no record found";
		break;
	case MTHCA_CMD_STAT_FAIL:
		str = "internal error";
		break;
	case MTHCA_CMD_STAT_INVALID_FIELD:
		str = "invalid field";
		break;
	case MTHCA_CMD_STAT_CONSTRAINT_ERR:
		str = "constraint error";
		break;
	case MTHCA_CMD_STAT_INSUFF_PRIVILEGE:
		str = "insufficient privilege";
		break;
	case MTHCA_CMD_STAT_INVALID_STATE:
		str = "invalid state";
		break;
	case MTHCA_CMD_STAT_INVALID_SGE:
		str = "invalid SGE";
		break;
	case MTHCA_CMD_STAT_INVALID_SIZE:
		str = "invalid size";
		break;
	case MTHCA_CMD_STAT_INVALID_ADDRESS:
		str = "invalid address";
		break;
	case MTHCA_CMD_STAT_ARM_INCOMPLETE:
		str = "arm incomplete";
		break;
	case MTHCA_CMD_STAT_TIMED_OUT:
		str = "timed out";
		break;
	case MTHCA_CMD_STAT_NO_WORK:
		str = "no work";
		break;