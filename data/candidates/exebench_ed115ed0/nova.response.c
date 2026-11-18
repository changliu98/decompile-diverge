static void operacao_dist(const struct ieee80211_reg_rule *rule,
				     struct iwl_nvm_data *data,
				     int tfd_queue, int queue)
{
	int ch_idx = rule->cqm_ch_idx + tfd_queue;
	int band = rule->cqm_band + queue;

	data->channel_index[ch_idx] = band;
}