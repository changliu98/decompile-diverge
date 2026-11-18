static int func0(struct gspca_dev *gspca_dev)
{
	gspca_dev->usb_buf[0] = 0x00;
	gspca_dev->usb_buf[1] = 0x02;
	gspca_dev->usb_buf[2] = 0x00;
	gspca_dev->usb_buf[3] = 0x08;
	gspca_dev->usb_buf[4] = 0x00;
	gspca_dev->usb_buf[5] = 0x00;
	gspca_dev->usb_buf[6] = 0x00;
	gspca_dev->usb_buf[7] = 0x00;
	gspca_dev->usb_buf[8] = 0x00;
	gspca_dev->usb_buf[9] = 0x00;
	gspca_dev->usb_buf[10] = 0x00;
	gspca_dev->usb_buf[11] = 0x00;
	gspca_dev->usb_buf[12] = 0x00;
	gspca_dev->usb_buf[13] = 0x00;
	gspca_dev->usb_buf[14] = 0x00;
	gspca_dev->usb_buf[15] = 0x00;
	return 0;
}