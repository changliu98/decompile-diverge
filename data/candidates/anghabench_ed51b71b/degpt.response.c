/*
 * Calculate the high-speed clock frequency in Hz based on the USB rate.
 *
 * The formula performs a fixed-point multiplication and shift:
 *   result = (usb_rate * 125 + 512) / 1024
 *
 * Explanation:
 * - 0x7d is 125 in decimal.
 * - 0x200 is 512 in decimal.
 * - >> 10 is equivalent to dividing by 1024 (2^10).
 *
 * This effectively computes: (usb_rate * 125 + 512) >> 10
 * Which approximates: usb_rate * (125 / 1024) ≈ usb_rate * 0.12207
 *
 * Note: Operator precedence means multiplication happens before addition,
 * and addition happens before the right shift.
 */
uint get_high_speed_hz(uint usb_clock_hz)
{
  return usb_clock_hz * 0x7d + 0x200 >> 10;
}