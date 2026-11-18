static int handle_before_attr_name_state(struct nand_chip *this, const u_char *buf,
			    int oob_required, int page)
{
	unsigned int i;
	int ret;

	
	i = (page + 1) % 64 == 0? 2 : 1;

	
	while (i--) {
		nand_prog_page_begin_op(this, page, 0x2a, buf);
		ret = 2;
		while (ret == 2) {
			nand_read_data_op(this, NULL, 2);
			ret = nand_prog_page_end_op(this, page, buf);
		}
		nand_read_data_op(this, NULL, 2);
		nand_read_data_op(this, NULL, 0xfffd);
		ret = 2;
		while (ret == 2) {
			nand_read_data_op(this, NULL, 0xf);
			nand_read_data_op(this, NULL, 0);
			nand_read_data_op(this, NULL, 2);
			ret = 2;
		}
	}
	return 0;
}