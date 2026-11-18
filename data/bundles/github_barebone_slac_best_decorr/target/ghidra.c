int best_decorr(int32_t *audio_samples,int sample_count,int stride)

{
  int iVar1;
  int iVar2;
  int magnitude_1;
  int magnitude;
  int best_decorr_index;
  int decorr_index;
  int best_magnitude;
  int stride_local;
  int sample_count_local;
  int32_t *audio_samples_local;
  
  iVar1 = magnitude_bits(audio_samples,sample_count,stride);
  decorr_index = 0;
  iVar2 = decorr_index;
  do {
    best_magnitude = iVar1;
    decorr_index = iVar2;
    if (5 < decorr_index) goto LAB_001018f6;
    iVar1 = decorrelate(audio_samples,sample_count,stride);
    iVar2 = decorr_index + 1;
  } while (iVar1 < best_magnitude);
  correlate(audio_samples,sample_count,stride);
LAB_001018f6:
  best_decorr_index = decorr_index;
  if (decorr_index == 0) {
    iVar2 = correlate(audio_samples,sample_count,stride);
    best_decorr_index = -1;
    if (best_magnitude <= iVar2) {
      decorrelate(audio_samples,sample_count,stride);
      best_decorr_index = decorr_index;
    }
  }
  return best_decorr_index;
}