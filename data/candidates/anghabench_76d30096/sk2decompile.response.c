static inline unsigned int sizeof_ns2_led_priv(int nr_leds) {
  unsigned int size;
  size = sizeof(struct ns2_led_priv);
  size += nr_leds * sizeof(struct ns2_led_data);
  return size;
}