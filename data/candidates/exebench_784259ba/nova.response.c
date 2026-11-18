static int inet_close(struct usb_xpad *xpad)
{
	
	outb(0, xpad->xtype.pad_ctrl_addr);
	xpad->xtype.pad_ctrl_addr = 0;

	return 0;
}