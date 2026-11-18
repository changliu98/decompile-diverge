static int murmur3_init_hash(struct gspca_dev *gspca_dev)
{
	gspca_dev->cam.cam_mode = vga_mode;
	return 0;
}