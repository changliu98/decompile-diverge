float __cdecl func0(float a, float b, float c)
{
  // Check triangle inequality
  if (a + b <= c || a + c <= b || b + c <= a)
    return -1.0;

  // Calculate semi-perimeter
  float s = (a + b + c) / 2.0;

  // Heron's formula for the area of a triangle
  float area = sqrtf(s * (s - a) * (s - b) * (s - c));

  // Round to 2 decimal places
  return roundf(area * 100.0) / 100.0;
}