// Function to calculate the sum of 8*i^3 for i from 1 to n
int func0(int n)
{
    int totalSum = 0; // Initialize sum to 0
    for (int index = 1; index <= n; index++) { // Loop from 1 to n
        totalSum += 8 * index * index * index; // Add 8*i^3 to sum
    }
    return totalSum; // Return the calculated sum
}