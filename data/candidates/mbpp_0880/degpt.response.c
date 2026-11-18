char * func0(int coeff_a,int coeff_b,int coeff_c)
{
  // Calculate the discriminant of the quadratic equation ax^2 + bx + c = 0
  // Note: The original code uses 'a * 4 * c' instead of '4 * a * c', which is mathematically incorrect for the standard discriminant formula (b^2 - 4ac).
  // However, we comment based on the intent of determining the number of real roots.
  if (coeff_b * coeff_b - coeff_a * 4 * coeff_c == 0) {
    // Discriminant is zero, indicating exactly one real solution (a repeated root)
    return "1 solution";
  }
  else if (coeff_b * coeff_b - coeff_a * 4 * coeff_c < 1) {
    // Discriminant is negative (or less than 1 in this flawed logic), indicating no real solutions
    return "No solutions";
  }
  else {
    // Discriminant is positive, indicating two distinct real solutions
    return "2 solutions";
  }
}