int unconv_uid(int uid) {
    int result;
    if (uid >= 0) {
        result = uid * log_split_mod + log_split_min;
    } else {
        result = -1;
    }
    return result;
}