/**
 * @brief Get the temperature scale factor for the AD7192 ADC.
 *
 * @param unipolar If true, returns the scale factor for unipolar mode.
 *                 If false, returns the scale factor for bipolar mode.
 * @return The temperature scale factor as a 16-bit unsigned integer.
 *         - 0x15FE for unipolar mode.
 *         - 0x0AFF for bipolar mode.
 */
uint ad7192_get_temp_scale(bool is_unipolar)
{
  return is_unipolar ? 0x15fe : 0xaff;
}