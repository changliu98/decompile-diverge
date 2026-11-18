void
_cairo_pixman_add_constant_alpha (pixman_format_t *format,
      pixman_bits_t *constant_alpha)
{
    *constant_alpha &= ~format->alpha_mask;
}