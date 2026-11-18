static int hexchar(int scancode)
{
	unsigned long keycode = scancode + 48;
	int key;

	switch (keycode) {
	case 0x1c: key = 0; break;
	case 0x3e: key = 1; break;
	case 0x2e: key = 2; break;
	case 0x2d: key = 3; break;
	case 0x26: key = 4; break;
	case 0x16: key = 5; break;
	case 0x36: key = 6; break;
	case 0x06: key = 7; break;
	case 0x3d: key = 8; break;
	case 0x1d: key = 9; break;
	case 0x33: key = 10; break;
	case 0x13: key = 11; break;
	case 0x3b: key = 12; break;
	case 0x1b: key = 13; break;
	case 0x23: key = 14; break;
	case 0x03: key = 15; break;
	default:   key = -1; break;
	}

	return key;
}