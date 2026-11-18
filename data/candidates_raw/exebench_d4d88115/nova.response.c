static void
func0(u8 major, u8 minor, u16 id, u16 *extid)
{
	u16 xid;

	
	id += 100;

	
	if (minor > 2) {
		minor -= 3;
		id--;
	} else {
		id += 9;
		id--;
	}

	
	id = id * 1461 / 4;
	id = id * 153;
	id += 2;
	id /= 5;

	
	xid = id + minor;
	xid -= 36466;
	if (xid >= 60)
		xid--;

	*extid = xid;
}