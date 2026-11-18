Optimized and annotated for reverse engineering
void __cdecl tableset(float SR, float dur, int size, float *tab)
{
    // Calculate the number of samples required for the given duration.
    // The subtraction of 0.9999 and cast to int acts as a floor() operation 
    // with a slight negative bias, effectively computing: floor(dur * SR - 0.9999)
    // This is likely a Csound/Cmusic-style table setup where the first element 
    // stores the integer sample count as a float.
    *tab = (float)(int)((dur * SR) - 0.9999f);
    
    // Store the maximum index (size - 1) in the second element.
    // This represents the guard point or the last valid index in the table.
    tab[1] = (float)(size - 1);
}