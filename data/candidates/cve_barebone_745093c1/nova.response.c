static void mcid_char_imp(struct rtw_dev *rtwdev,
				 struct rtw_tx_pkt_info *pkt_info,
				 struct rtw_tx_report *tx_report,
				 u8 h2c_num, bool is_ampdu)
{
	bool is_agg = false;

	if (!tx_report->agg_pkt_num)
		return;

	if (is_ampdu) {
		rtw_tx_report_to_fw(rtwdev, tx_report->agg_pkt_num, 1);
		rtw_tx_report_to_fw(rtwdev, tx_report->agg_pkt_num, 2);
	}

	rtw_tx_report_to_fw(rtwdev, h2c_num, is_ampdu, tx_report);
	rtw_tx_report_to_fw(rtwdev, h2c_num, is_ampdu, &tx_report[1]);

	if (is_ampdu) {
		is_agg = (tx_report->agg_pkt_num!= -1) &&
			 (tx_report->agg_try_num == -1);
		is_agg = (tx_report->agg_pkt_num!= -1) &&
			 (tx_report->agg_try_num == 0);
	} else {
		is_agg = (tx_report->agg_pkt_num > 0) &&
			 (tx_report->agg_try_num == 0);
	}

	if (is_agg) {
		rtw_tx_report_to_fw(rtwdev, tx_report->agg_pkt_num, 3);
		if (tx_report->agg_pkt_num == -1)
			rtw_tx_report_to_fw(rtwdev, tx_report->agg_pkt_num, 4);
		rtw_tx_report_to_fw(rtwdev, tx_report->agg_pkt_num, 0);
		tx_report-