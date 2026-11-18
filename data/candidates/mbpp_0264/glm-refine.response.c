#include <stdlib.h>

/**
 * @brief Calculates the equivalent human age based on a dog's age.
 * 
 * @param dog_age The age of the dog in years.
 * @return double The equivalent human age.
 */
double __cdecl CalculateDogAge(int dog_age)
{
  // Exit the program with an error code if the input age is invalid (negative)
  if (dog_age < 0)
  {
    exit(1);
  }

  // For dogs older than 2 years, each human year is roughly equivalent to 4 dog years.
  // The first 2 years account for 21 human years (10.5 * 2).
  if (dog_age > 2)
  {
    return (double)(4 * (dog_age - 2) + 21);
  }
  
  // For dogs 2 years old or younger, each dog year is equivalent to 10.5 human years.
  return (double)dog_age * 10.5;
}