uint get_high_speed_hz(uint usb_rate)

{
  uint usb_rate_local;
  
  return usb_rate * 0x7d + 0x200 >> 10;
}