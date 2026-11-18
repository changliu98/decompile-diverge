// Checks if three integers can form a valid triangle
// Returns true if the sum of any two sides is greater than the third side
_Bool func0(int side1, int side2, int side3)
{
    // Triangle inequality theorem: each side must be less than the sum of the other two
    return (side3 < side1 + side2) && (side2 < side1 + side3) && (side1 < side2 + side3);
}