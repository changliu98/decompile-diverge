void
atomic_clear_mask (pixman_format_t *format,
      pixman_bits_t *constant_alpha)
{
    *constant_alpha &= ~format->alpha_mask;
}