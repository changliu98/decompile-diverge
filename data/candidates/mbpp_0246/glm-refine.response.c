double __cdecl func0(double number)
{
  double current_guess; // [rsp+8h] [rbp-20h]
  double previous_guess; // [rsp+10h] [rbp-18h]

  // A square root of 0 is exactly 0
  if (number == 0.0)
    return 0.0;

  // Initialize the guess to number / 2.0
  current_guess = number / 2.0;
  
  // Initialize previous_guess to a value that ensures the loop executes at least once
  previous_guess = number / 2.0 + 1.0;

  // Newton's Method (Babylonian method) for finding the square root
  // Iterate until the guess converges (i.e., stops changing between iterations)
  while (current_guess != previous_guess)
  {
    previous_guess = current_guess;
    current_guess = (current_guess + number / current_guess) / 2.0;
  }

  return current_guess;
}