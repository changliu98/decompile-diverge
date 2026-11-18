void __cdecl i8253_cascade_ns_to_timer_power(
        int i8253_osc_base,
        unsigned int *d1,
        unsigned int *d2,
        unsigned int *nanosec,
        int round_mode)
{
  unsigned int base;
  unsigned int div2;
  unsigned int div1;

  // The mask is loop-invariant and can be safely moved outside the loop.
  // It isolates the rounding mode bits.
  unsigned int mode = round_mode & 0x30000u;

  // Iterate div1 as powers of 2 from 2 up to 65536 (0x10000)
  for ( div1 = 2; div1 <= 0x10000; div1 *= 2 )
  {
    base = div1 * i8253_osc_base;

    // Calculate div2 based on the specified rounding mode
    switch ( mode )
    {
      case 0x10000:
        // Truncate (floor)
        div2 = *nanosec / base;
        break;
      case 0x20000:
        // Round up (ceiling)
        div2 = (base + *nanosec - 1) / base;
        break;
      case 0:
      default:
        // Round to nearest
        div2 = ((base / 2) + *nanosec) / base;
        break;
    }

    // Enforce minimum divisor value for the i8253 timer
    if ( div2 < 2 )
      div2 = 2;

    // Check if div2 fits within the 16-bit limit of the i8253 timer
    if ( div2 <= 0x10000 )
    {
      *nanosec = base * div2;
      *d1 = (unsigned __int16)div1;
      *d2 = (unsigned __int16)div2;
      return;
    }
  }

  // Fallback if no suitable divisors were found within the limits
  *nanosec = 0;
  *d1 = 0;
  *d2 = 0;
}