// Deinterlace the GIF frame by updating the current Y position and step pattern.
// Returns true if the current Y position is within the image height bounds.
_Bool nsgif__deinterlace(uint32_t image_height, uint32_t *current_y, uint8_t *interlace_step)
{
    // Update Y position based on the current step pattern.
    // The step value encodes the interlace pattern; lower 4 bits determine the offset.
    *current_y = (*interlace_step & 0xf) + *current_y;
    
    // Check if the updated Y position is still within the image height.
    if (*current_y < image_height) {
        return true;
    }
    
    // If Y exceeds height, advance to the next interlace pass.
    // Pass 1: Y positions 0, 4, 8, ... (step = 0x18)
    if (*interlace_step == '\x18') {
        *current_y = 4;
        *interlace_step = '\b'; // Step size 8 for next pass
        if (*current_y < image_height) {
            return true;
        }
    } 
    // Pass 2: Y positions 0, 2, 4, ... (step = 0x04)
    else if (*interlace_step != '\x04') {
        *current_y = 2;
        *interlace_step = '\x04'; // Step size 4 for next pass
        if (*current_y < image_height) {
            return true;
        }
    }
    
    // Pass 3: Y positions 0, 1, 2, ... (step = 0x02)
    *current_y = 1;
    *interlace_step = '\x02';
    return image_height > *current_y;
}