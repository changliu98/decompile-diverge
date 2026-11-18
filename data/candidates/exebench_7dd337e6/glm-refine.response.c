/**
 * @brief Performs one step of the Kahan summation algorithm.
 * 
 * The Kahan algorithm is used to minimize numerical precision loss 
 * (floating-point round-off error) when adding a sequence of finite 
 * floating-point numbers.
 *
 * @param new_value      The next value to be added to the total.
 * @param sum            Pointer to the running total sum.
 * @param err            Pointer to the running compensation error.
 * @param loc            Pointer to a temporary variable (holds value to be added).
 * @param tmp            Pointer to a temporary variable (holds the preliminary new sum).
 */
void __cdecl kahan_summation_step(double new_value, double *sum, double *err, double *loc, double *tmp)
{
  // Step 1: 'new_value' is adjusted by subtracting the error from the previous step.
  // This recovers bits of precision that were lost in the prior addition.
  *loc = new_value - *err;

  // Step 2: The adjusted value is added to the running sum.
  // Due to floating-point limits, the lower bits of '*loc' might be lost here.
  *tmp = *sum + *loc;

  // Step 3: Calculate the new round-off error.
  // Algebraically, this evaluates to 0. However, in floating-point arithmetic, 
  // '(*tmp - *sum)' yields the high-order bits of '*loc', leaving behind the 
  // low-order bits that were truncated during the Step 2 addition.
  // Subtracting '*loc' extracts this lost precision to be compensated in the next step.
  *err = (*tmp - *sum) - *loc;

  // Step 4: Update the running sum to the newly calculated total.
  *sum = *tmp;
}