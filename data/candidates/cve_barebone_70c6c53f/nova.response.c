static int parse_speex_extradata(struct mtd_info *mtd, const char *name, int index)
{
	struct onenand_chip *this = mtd->priv;
	unsigned long freq;
	unsigned long clk_period;
	unsigned long clk_time;
	unsigned long page_time;
	unsigned long bbt_time;
	unsigned long sr_time;
	unsigned long i;

	
	freq = clk_get_rate(&clk_onenand);

	
	clk_period = 1000000000 / freq;

	
	clk_time = clk_period;

	
	page_time = clk_time;

	
	bbt_time = clk_time;

	
	sr_time = clk_time;

	
	do {
		page_time = clk_time;

		
		do {
			bbt_time = clk_time;

			
			do {
				sr_time = clk_time;

				
				do {
					i = clk_time;
					clk_time = (i / 2) + (i % 2);
				} while (clk_time > 0x7fffffff);
			} while (sr_time > 0x40 && sr_time < (0x7fffffff / freq));
		} while (bbt_time > 0x4 && bbt_time < (0x7fffffff / freq));
	} while (page_time > 0x40 && page_time < (0x7fffffff / freq));

	
	this->page_size = page_time;
	this->oobsize = (this->page_size > 0x40? 0x40 : 0x20);
	this->writesize = this->page_size;
	this->oobavail = this->oobsize;

	
	if (this->page_size > 0x40 && this->page_size < 0x40000