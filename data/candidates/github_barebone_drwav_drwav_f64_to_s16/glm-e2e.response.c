void drwav_f64_to_s16(int16_t* dst, const double* src, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        double sample = src[i];
        double clamped;
        
        // Clamp sample between -1.0 and 1.0
        if (sample < -1.0) {
            clamped = -1.0;
        } else if (sample > 1.0) {
            clamped = 1.0;
        } else {
            clamped = sample;
        }
        
        // Convert to signed 16-bit integer
        // The assembly adds 1.0 to the clamped value, multiplies by 32767.0, 
        // converts to a 32-bit integer, and then subtracts 0x8000 (32768).
        // This effectively maps [-1.0, 1.0] to [-32768, 32767].
        int32_t scaled = (int32_t)((clamped + 1.0) * 32767.0) - 32768;
        
        dst[i] = (int16_t)scaled;
    }
}