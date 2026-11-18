void uppercase(int *c)
{
    int uc = *c;
    if ((uc >= 'a' && uc <= 'i') || (uc >= 'j' && uc <= 'r') || (uc >= 's' && uc <= 'z')) {
        uc += ('A' - 'a');
        *c = uc;
    }
}