void noise_est(float current_gain, float *estimated_noise_gain, float upper_threshold, float lower_threshold, float min_gain, float max_gain)
{
  // If current gain is within the upper threshold of the estimated noise gain
  if (current_gain <= *estimated_noise_gain + upper_threshold) {
    // If current gain is also above the lower threshold of the estimated noise gain
    if (*estimated_noise_gain + lower_threshold <= current_gain) {
      // Update noise gain to the current gain value
      *estimated_noise_gain = current_gain;
    } else {
      // Gain is below the lower threshold; decrease noise gain by 'down' amount
      *estimated_noise_gain += lower_threshold;
    }
  } else {
    // Gain is above the upper threshold; increase noise gain by 'up' amount
    *estimated_noise_gain += upper_threshold;
  }
  // Clamp the noise gain to the minimum allowed value
  if (*estimated_noise_gain < min_gain) {
    *estimated_noise_gain = min_gain;
  } 
  // Clamp the noise gain to the maximum allowed value
  else if (*estimated_noise_gain > max_gain) {
    *estimated_noise_gain = max_gain;
  }
}