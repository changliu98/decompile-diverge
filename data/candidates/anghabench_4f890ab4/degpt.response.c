int ff_norm_qscale(int quantization_scale, int scale_type)
{
    // Normalize quantization scale based on the specified type
    switch(scale_type) {
    case 0x80:
        // Type 0x80: Adjust qscale by subtracting shifted value from 0x41
        return 0x41 - (quantization_scale >> 2);
    case 0x81:
        // Type 0x81: Right shift qscale by 1
        return quantization_scale >> 1;
    case 0x82:
        // Type 0x82: Return qscale unchanged
        return quantization_scale;
    case 0x83:
        // Type 0x83: Right shift qscale by 2
        return quantization_scale >> 2;
    }
    // Default case: Return qscale unchanged if type is unrecognized
    return quantization_scale;
}