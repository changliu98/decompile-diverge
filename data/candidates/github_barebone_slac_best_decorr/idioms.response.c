int best_decorr(int *audio_samples, int sample_count, int stride)
{
  int best_magnitude = magnitude_bits(audio_samples, sample_count, stride);
  int decorr_index = 0;
  int best_decorr_index = 0;
  int magnitude;
  while (decorr_index < 6)
  {
    magnitude = decorrelate(audio_samples, sample_count, stride);
    decorr_index++;
    if (magnitude < best_magnitude)
    {
      correlate(audio_samples, sample_count, stride);
      decorr_index--;
      break;
    }
    else
    {
      best_decorr_index = decorr_index;
      best_magnitude = magnitude;
    }
  }
  if (decorr_index == 0)
  {
    if (correlate(audio_samples, sample_count, stride) < best_magnitude)
    {
      return -1;
    }
    else
    {
      decorrelate(audio_samples, sample_count, stride);
    }
  }
  return best_decorr_index;
}