int func0(int circle_radius)
{
    int valid_points_count = 0;
    // Iterate through possible widths 'a' from 1 to 2*radius - 1
    for (int width = 1; width < circle_radius * 2; width++) {
        // Iterate through possible heights 'b' from 1 to 2*radius - 1
        for (int height = 1; height < circle_radius * 2; height++) {
            // Check if the point (a, b) lies within or on the boundary of a circle with radius*2 centered at origin
            // This is equivalent to checking if a^2 + b^2 <= (radius*2)^2
            if (width * width + height * height <= circle_radius * 2 * circle_radius * 2) {
                valid_points_count++;
            }
        }
    }
    // Return the count of integer coordinate pairs (a, b) satisfying the condition
    return valid_points_count;
}