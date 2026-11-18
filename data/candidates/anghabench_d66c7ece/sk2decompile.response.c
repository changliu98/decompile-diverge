static inline unsigned int sizeof_pwm_leds_priv(int n_leds) {
  return sizeof(struct pwm_leds_priv) + n_leds * sizeof(struct pwm_led);
}