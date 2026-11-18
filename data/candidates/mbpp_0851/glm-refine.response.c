double __cdecl func0(int N, int Sum)
{
    // Calculate the average of Sum over N
    double average = (double)Sum / (double)N;
    
    // Scale to percentage, round to nearest integer, and scale back
    // This effectively rounds the average to 2 decimal places
    return round(average * 100.0) / 100.0;
}