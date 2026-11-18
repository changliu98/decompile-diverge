static void func0(struct pm8001_hba_info *pm8001_ha,
	void *piomb, int sz, struct pm8001_ccb_info *ccb)
{
	int status, sge_cnt, sge_num, sge_len;
	u32 sge_offset;

	if (sz == 1 && *(u8 *)piomb == 0xff) {
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("Chip Handshake failed!\n"));
		return;
	}
	if (sz < 5)
		return;
	if (*(u8 *)piomb == 0 && *(u8 *)(piomb + 1) == 0 &&
		*(u8 *)(piomb + 2) == 0 && *(u8 *)(piomb + 3) == 0) {
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("Chip Handshake failed!\n"));
		pm8001_chip_phy_disable(pm8001_ha, (u8 *)piomb + 4, sz - 4, ccb);
		return;
	}
	PM8001_MSG_DBG(pm8001_ha,
		pm8001_printk("Chip Handshake success!\n"));
	status = pm8001_chip_phy_enable(pm8001_ha, (u8 *)piomb, sz,
		&sge_cnt, &sge_num, &sge_offset);
	if (status > 0) {
		piomb += status;
		sz -= status;
	} else {
		return;
	}
	sge_len = sge_offset & 0xff;
	pm8001_chip_phy_sgl_enable(pm8001_ha, (u8 *)piomb, sz, sge_len, ccb);
}