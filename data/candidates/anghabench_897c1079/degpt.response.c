// Activates a ramp function based on input x
// Calculates the result as: x * DAT_00102008 + x * (1 if x > 0 else 0)
// DAT_00102008 is a constant multiplier
// The term (0.0f < x) evaluates to 1.0f when x is positive, and 0.0f otherwise
float ramp_activate(float input_value)
{
  return input_value * multiplier_constant + input_value * (0.0f < input_value);
}