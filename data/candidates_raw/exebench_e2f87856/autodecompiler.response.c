void swap(int * firstNumber, int * secondNumber)
{
    int temp;
    temp = *firstNumber;
    *firstNumber = *secondNumber;
    *secondNumber = temp;
}