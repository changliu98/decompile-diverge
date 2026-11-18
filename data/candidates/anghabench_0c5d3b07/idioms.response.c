char *get_priority_string(int prio)
{
    char *name;
    switch (prio) {
    case 128:
        name = "Unavailable";
        break;
    case 129:
        name = "Preferred";
        break;
    case 130:
        name = "Neutral";
        break;
    case 131:
        name = "Low";
        break;
    default:
        name = "Invalid";
        break;
    }
    return (name);
}