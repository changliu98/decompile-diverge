void NearestNeighbor(int32_t *out_idx, const float *array, float target, int32_t count) {
    float diff = array[0] - target;
    float min_dist = diff * diff;
    *out_idx = 0;

    for (int32_t i = 1; i < count; i++) {
        diff = array[i] - target;
        float dist = diff * diff;
        
        if (min_dist > dist) {
            min_dist = dist;
            *out_idx = i;
        }
    }
}