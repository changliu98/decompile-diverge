unsigned int __cdecl get_high_speed_hz(unsigned int usb_rate)
{
  // (usb_rate + 4) is used to round to the nearest integer before dividing by 1024
  return (usb_rate + 4) / 1024;
}