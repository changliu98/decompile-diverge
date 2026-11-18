// Calculates the slope of the line passing through two points (x1, y1) and (x2, y2).
// Returns the slope as a float value.
float func0(int startX, int startY, int endX, int endY)
{
    // Compute the difference in y-coordinates and cast to float to ensure floating-point division.
    // Compute the difference in x-coordinates and cast to float to ensure floating-point division.
    // Return the ratio of the differences, which represents the slope.
    return (float)(endY - startY) / (float)(endX - startX);
}