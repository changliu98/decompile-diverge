unsigned int __cdecl get_high_speed_hz(unsigned int usb_rate)
{
  return (125 * usb_rate + 512) >> 10;
}