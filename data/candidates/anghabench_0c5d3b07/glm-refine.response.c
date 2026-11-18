const char *get_priority_string(int prio)
{
    switch (prio)
    {
        case 128:
            return "Unavailable";
        case 129:
            return "Preferred";
        case 130:
            return "Neutral";
        case 131:
            return "Low";
        default:
            return "Invalid";
    }
}