static void _K15_IRTranscodeSourcePixelsToDestinationPixelFormat(struct rtw_dev *rtwdev)
{
	struct rtw_hal *hal = &rtwdev->hal;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw_phy_cond cond = {0};
	u32 *phy_table;
	u32 tx_power;

	tx_power = hal->tx_power_level;
	cond.bw = hal->current_chan_bw;
	cond.rs = efuse->rs_type;
	cond.rf = efuse->rf_type;
	cond.txp = hal->tx_pwr_idx;
	cond.rf_type = efuse->rf_type;

	do {
		phy_table = kzalloc(tx_power * sizeof(*phy_table), GFP_KERNEL);
		if (!phy_table)
			break;

		if (cond.bw == RTW_CHANNEL_WIDTH_20 && cond.rs == 1)
			rtw_phy_get_tx_power_rate_table_11n(efuse, phy_table, tx_power);
		else if (cond.bw == RTW_CHANNEL_WIDTH_20 && cond.rs == 2)
			rtw_phy_get_tx_power_rate_table_11ac(efuse, phy_table, tx_power);
		else if (cond.bw == RTW_CHANNEL_WIDTH_20 && cond.rs == 3)
			rtw_phy_get_tx_power_rate_table_11ac_mcs(efuse, phy_table, tx_power);
		else if (cond.bw == RTW_CHANNEL_WIDTH_20 && cond.rs == 4)
			rtw_phy_get_tx_power_rate_table_11ac_mcs(efuse, phy_table, tx_power);
		else if (cond.bw == RTW_CHANNEL_WIDTH_20 &&