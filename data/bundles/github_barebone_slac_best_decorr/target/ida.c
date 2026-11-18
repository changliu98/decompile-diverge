int __cdecl best_decorr(int32_t *audio_samples, int sample_count, int stride)
{
  int magnitude; // [rsp+10h] [rbp-20h]
  int best_decorr_index; // [rsp+14h] [rbp-1Ch]
  int decorr_index; // [rsp+18h] [rbp-18h]
  int best_magnitude; // [rsp+1Ch] [rbp-14h]

  best_magnitude = magnitude_bits(audio_samples, sample_count, stride);
  decorr_index = 0;
  best_decorr_index = 0;
  while ( decorr_index < 6 )
  {
    magnitude = decorrelate(audio_samples, sample_count, stride);
    ++decorr_index;
    if ( magnitude >= best_magnitude )
    {
      correlate(audio_samples, sample_count, stride);
      --decorr_index;
      break;
    }
    best_decorr_index = decorr_index;
    best_magnitude = magnitude;
  }
  if ( !decorr_index )
  {
    if ( correlate(audio_samples, sample_count, stride) >= best_magnitude )
      decorrelate(audio_samples, sample_count, stride);
    else
      return -1;
  }
  return best_decorr_index;
}