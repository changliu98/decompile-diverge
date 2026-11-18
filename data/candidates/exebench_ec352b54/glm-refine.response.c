void __cdecl swap(float *min, float *max)
{
  if ( *min > *max )
  {
    // Type-punning via union to safely and cleanly swap the raw 32-bit IEEE 754 representations
    union { float f; int i; } temp;
    
    temp.f = *max;
    *max = *min;
    *min = temp.f;
  }
}