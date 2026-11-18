static int best_decorr (int32_t *audio_samples, int sample_count, int stride)
{
    int best_magnitude = magnitude_bits (audio_samples, sample_count, stride);
    int decorr_index = 0, best_decorr_index = 0;

    // first, continue to call decorrelate() until the result gets worse, then back up 1

    while (decorr_index < MAX_DECORR) {
        int magnitude = decorrelate (audio_samples, sample_count, stride); decorr_index++;

        if (magnitude < best_magnitude) {
            best_decorr_index = decorr_index;
            best_magnitude = magnitude;
        }
        else {
            correlate (audio_samples, sample_count, stride); decorr_index--;
            break;
        }
    }

    // if that didn't work at all, maybe negative decorrelation (i.e. correlation) will

    if (decorr_index == 0) {
        int magnitude = correlate (audio_samples, sample_count, stride); decorr_index--;

        if (magnitude < best_magnitude) {
            best_decorr_index = decorr_index;
            best_magnitude = magnitude;
        }
        else {
            decorrelate (audio_samples, sample_count, stride); decorr_index++;
        }
    }

    return best_decorr_index;
}