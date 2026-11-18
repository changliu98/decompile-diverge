unsigned short qla24xx_calc_ct_iocbs(u8 proto)
{
	unsigned short cmdlen = 1;

	switch (proto) {
	case 0:		/* Non-data */
		cmdlen += 0;
		break;

	case 3:		/* PIO Data-in */
	case 4:		/* PIO Data-out */
		cmdlen += 5;
		break;

	case 5:		/* DMA */
		cmdlen += 3;
		break;

	case 6:		/* DMA Queued */
		cmdlen += 5;
		break;

	case 7:		/* FPDMA */
		cmdlen += 8;
		break;

	case 8:		/* Return Response Info */
		cmdlen += 16;
		break;

	case 9:		/* Non-zero Buffer Offset */
		cmdlen += 16;
		break;

	default:	/* Reserved */
		return 0x0000;	/* Not valid */
	}

	if ((proto < 3) || (proto == 5) || (proto == 6))
		cmdlen += 1;

	return cmdlen;
}