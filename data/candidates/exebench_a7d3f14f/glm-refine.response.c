void __cdecl noise_est(float current_gain, float *noise_floor, float attack_rate, float release_rate, float min_floor, float max_floor)
{
  // 1. Adaptive tracking: Adjust the noise floor towards the current gain level
  if (current_gain > *noise_floor + attack_rate)
  {
    // Gain spiked above the noise floor: move floor up (Attack)
    *noise_floor += attack_rate;
  }
  else if (current_gain < *noise_floor + release_rate)
  {
    // Gain dropped below the noise floor: move floor down (Release)
    *noise_floor += release_rate; // Note: release_rate is expected to be negative
  }
  else
  {
    // Gain is within the attack/release threshold band: lock to gain
    *noise_floor = current_gain;
  }

  // 2. Clamping: Ensure the noise floor stays within legal boundaries
  if (*noise_floor < min_floor)
    *noise_floor = min_floor;
  if (*noise_floor > max_floor)
    *noise_floor = max_floor;
}