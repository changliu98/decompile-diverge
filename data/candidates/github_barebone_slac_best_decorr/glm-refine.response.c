int __cdecl best_decorr(int32_t *audio_samples, int sample_count, int stride)
{
  int best_magnitude = magnitude_bits(audio_samples, sample_count, stride);
  int best_decorr_index = 0;
  int decorr_index = 0;

  // Try up to 6 decorrelation passes
  while (decorr_index < 6)
  {
    int magnitude = decorrelate(audio_samples, sample_count, stride);
    ++decorr_index;

    // If decorrelating doesn't improve the magnitude, revert and stop
    if (magnitude >= best_magnitude)
    {
      correlate(audio_samples, sample_count, stride);
      --decorr_index;
      break;
    }

    // Update best metrics if improved
    best_decorr_index = decorr_index;
    best_magnitude = magnitude;
  }

  // Handle the case where the very first decorrelation pass failed
  if (!decorr_index)
  {
    if (correlate(audio_samples, sample_count, stride) >= best_magnitude)
    {
      // Revert the correlation if it didn't help either
      decorrelate(audio_samples, sample_count, stride);
    }
    else
    {
      // Signal that correlation was the better operation
      return -1;
    }
  }

  return best_decorr_index;
}