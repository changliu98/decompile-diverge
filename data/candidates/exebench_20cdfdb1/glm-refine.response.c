void __cdecl liefere_double_array_statistik(
        const double *array,
        int laenge,
        double *min,
        double *max,
        double *summe,
        double *durchschnitt)
{
    double current_min = array[0];
    double current_max = array[0];
    double current_sum = 0.0;

    for (int i = 0; i < laenge; ++i)
    {
        double value = array[i];

        if (value < current_min)
            current_min = value;
        if (value > current_max)
            current_max = value;

        current_sum += value;
    }

    *min = current_min;
    *max = current_max;
    *summe = current_sum;
    *durchschnitt = current_sum / (double)laenge;
}