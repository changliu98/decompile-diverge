void __cdecl ecRotate(double *c, double soe, double coe)
{
  // Store the newly calculated Y-component (or 2nd element) in a temporary variable
  double temp = c[2] * soe + c[1] * coe;
  
  // Update the Z-component (or 3rd element)
  c[2] = c[2] * coe - c[1] * soe;
  
  // Assign the temporary variable back to the Y-component
  c[1] = temp;
}