void __cdecl func0(int value, char *result_buffer)
{
    // Static data recovered from &unk_2040 and &off_3D70
    const int thresholds[13] = { /* ... */ };
    const char *symbols[13] = { /* ... */ };
    
    int index = 0;
    int remaining_value = value;
    
    result_buffer[0] = '\0';

    while (remaining_value > 0)
    {
        while (remaining_value >= thresholds[index])
        {
            strcat(result_buffer, symbols[index]);
            remaining_value -= thresholds[index];
        }
        
        if (remaining_value > 0)
        {
            ++index;
        }
    }
}