/**
 * @brief Checks if an integer is not congruent to 2 modulo 4.
 * 
 * Mathematically, this evaluates to false only for positive integers of the form 4k + 2 
 * (e.g., 2, 6, 10, 14, ...). 
 * 
 * Note on semantics: For negative integers, the C modulo operator (%) yields a negative 
 * remainder (e.g., -2 % 4 = -2). Therefore, this function will always return true for 
 * negative inputs. This behavior is preserved exactly as in the original decompilation.
 * 
 * @param n The integer to check.
 * @return true if n % 4 != 2, false otherwise.
 */
bool __cdecl is_not_2_mod_4(int n)
{
  return n % 4 != 2;
}