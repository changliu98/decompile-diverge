static int func0(unsigned char c)
{
	int i;
	unsigned char j;

	j = c & 0x7f;
	i = 0;

	switch (j) {
	case MCI_CMD_RESET:
		i = 11;
		break;
	case MCI_CMD_INIT:
		i = 10;
		break;
	case MCI_CMD_SEND_OP_COND:
		i = 9;
		break;
	case MCI_CMD_SEND_CSD:
		i = 8;
		break;
	case MCI_CMD_SEND_CID:
		i = 7;
		break;
	case MCI_CMD_READ_SCR:
		i = 6;
		break;
	case MCI_CMD_SET_AREA:
		i = 5;
		break;
	case MCI_CMD_READ_BLOCK:
		i = 4;
		break;
	case MCI_CMD_STOP_TRANSMISSION:
		i = 3;
		break;
	case MCI_CMD_SET_BLOCKLEN:
		i = 2;
		break;
	case MCI_CMD_READY_FOR_DATA:
		i = 1;
		break;
	case MCI_CMD_WRITE_BLOCK:
		i = 0;
		break;
	}

	return i;
}