static inline bool nsgif__deinterlace(uint32_t height, uint32_t *y, uint8_t *step)
{
	*y += *step & 0xf;

	if (*y < height) return true;

	switch (*step) {
	case 24: *y = 4; *step = 8; if (*y < height) return true;
	         /* Fall through. */
	case  8: *y = 2; *step = 4; if (*y < height) return true;
	         /* Fall through. */
	case  4: *y = 1; *step = 2; if (*y < height) return true;
	         /* Fall through. */
	default:
		break;
	}

	return false;
}