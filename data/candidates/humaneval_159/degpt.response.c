void func0(int baseValue, int requiredAmount, int availableAmount, int *outputArray)
{
  // If the remaining amount is less than the needed amount
  if (availableAmount < requiredAmount) {
    // Set the first element of result to the sum of number and remaining
    *outputArray = baseValue + availableAmount;
    // Set the second element of result to 0
    outputArray[1] = 0;
  }
  else {
    // Set the first element of result to the sum of number and need
    *outputArray = baseValue + requiredAmount;
    // Set the second element of result to the difference between remaining and need
    outputArray[1] = availableAmount - requiredAmount;
  }
}