int best_decorr(int32_t *samples, int count, int stride)
{
    int best_magnitude = magnitude_bits(samples, count, stride);
    int best_decorr_index = 0;
    int decorr_index;

    for (decorr_index = 0; decorr_index < 6; decorr_index++) {
        int magnitude = decorrelate(samples, count, stride);
        if (magnitude < best_magnitude) {
            best_magnitude = magnitude;
            best_decorr_index = decorr_index;
        } else {
            correlate(samples, count, stride);
            break;
        }
    }

    if (best_decorr_index == 0) {
        int magnitude = correlate(samples, count, stride);
        if (magnitude < best_magnitude) {
            decorrelate(samples, count, stride);
        } else {
            best_decorr_index = -1;
        }
    }

    return best_decorr_index;
}