int foo(float *distances, int threshold)
{
    // Check if the sign of the first element differs from the sign of the second element
    // Specifically, check if one is positive and the other is not
    if ((0.0f < *distances) != (0.0f < distances[1])) {
        return 0;
    }
    return threshold;
}