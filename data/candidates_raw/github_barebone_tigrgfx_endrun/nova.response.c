static void func0(struct rtsx_pcr *pcr)
{
	pcr->reg_pm_ctrl_1b--;
	rtsx_pci_write_register(pcr, pcr->reg_pm_ctrl_1b, 0xFF, pcr->pm_ctrl_1b);

	if (pcr->reg_pm_ctrl_1b >= 0x44)
		rtsx_pci_write_phy_register(pcr, 0x115, 0x04, pcr->pm_ctrl_1b - 0x44 + 1);
	else if (pcr->reg_pm_ctrl_1b >= 0x23)
		rtsx_pci_write_phy_register(pcr, 0x111, 0x03, pcr->pm_ctrl_1b - 0x23 + 1);
	else if (pcr->reg_pm_ctrl_1b >= 0x13)
		rtsx_pci_write_phy_register(pcr, 0x10D, 0x02, pcr->pm_ctrl_1b - 0x13 + 1);
	else if (pcr->reg_pm_ctrl_1b >= 0x0B)
		rtsx_pci_write_phy_register(pcr, 0x109, 0x01, pcr->pm_ctrl_1b - 0x0B + 1);
	else if (pcr->reg_pm_ctrl_1b >= 0x03)
		rtsx_pci_write_phy_register(pcr, 0x101, 0x00, pcr->pm_ctrl_1b - 0x03 + 1);

	while (pcr->reg_pm_ctrl_1b) {
		pcr->reg_pm_ctrl_1b--;
		rtsx_pci_write_register(pcr, pcr->reg_pm_ctrl_1b, 0xFF,
					pc