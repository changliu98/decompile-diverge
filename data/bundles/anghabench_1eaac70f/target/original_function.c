int unconv_uid (int user_id) {
	if (user_id >= 0) { return user_id * log_split_mod + log_split_min; }
	return -1;
}