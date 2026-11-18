// Calculates the curved surface area, total surface area, and volume of a cylinder
// Parameters:
//   r   - radius of the cylinder
//   h   - height of the cylinder
//   csa - pointer to store the curved surface area (2 * π * r * h)
//   tsa - pointer to store the total surface area (2 * π * r * (h + r))
//   vol - pointer to store the volume (π * r^2 * h)
// Note: DAT_0010200c, DAT_00102008, and DAT_00102004 are likely constants related to π
void cylinder(float radius,float height,float *curved_surface_area,float *total_surface_area,float *volume)
{
  // Curved Surface Area = 2 * π * r * h
  *curved_surface_area = (pi * radius * height * two) / one;
  
  // Total Surface Area = 2 * π * r * (h + r)
  *total_surface_area = (pi * radius * (height + radius) * two) / one;
  
  // Volume = π * r^2 * h
  *volume = (radius * radius * height * two) / one;
}