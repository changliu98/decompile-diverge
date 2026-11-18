int lzma_get_dist_state(int dist) {
    long long result;
    
    if (dist < (long long)DIST_STATES + MATCH_LEN_MIN) {
        result = dist - MATCH_LEN_MIN;
    } else {
        result = DIST_STATES - 1;
    }
    
    return result;
}