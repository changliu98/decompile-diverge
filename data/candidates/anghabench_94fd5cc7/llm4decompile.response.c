int wifirate2_ratetbl_inx(int rate)
{
	int inx = 0;

	switch (rate & 0x7f) {
	case 130:
		inx = 11;
		break;
	case 110:
		inx = 10;
		break;
	case 90:
		inx = 9;
		break;
	case 60:
		inx = 8;
		break;
	case 48:
		inx = 7;
		break;
	case 36:
		inx = 6;
		break;
	case 22:
		inx = 5;
		break;
	case 18:
		inx = 4;
		break;
	case 11:
		inx = 2;
		break;
	case 24:
		inx = 3;
		break;
	case 4:
		inx = 1;
		break;
	case 2:
		inx = 0;
		break;
	}
	return inx;
}