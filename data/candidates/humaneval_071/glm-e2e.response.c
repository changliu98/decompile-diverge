float func0(float a, float b, float c) {
    float result;
    
    // Check if the given sides can form a valid triangle
    if (a + b <= c || a + c <= b || b + c <= a) {
        result = -1.0f;
    } else {
        // Calculate the semi-perimeter
        float s = (a + b + c) / 2.0f;
        
        // Calculate the area using Heron's formula
        float area = sqrtf(s * (s - a) * (s - b) * (s - c));
        
        // Round the area to 2 decimal places
        result = roundf(area * 100.0f) / 100.0f;
    }
    
    return result;
}