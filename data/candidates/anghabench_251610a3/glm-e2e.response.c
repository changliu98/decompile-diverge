const char *get_level_str(int level) {
    const char *level_str;
    
    // The assembly subtracts 128 (0x80) from the level and checks if it's > 7
    // This is equivalent to checking if level is between 128 and 135 inclusive
    switch (level) {
        case 128:
            level_str = "DEBUG";   // 0x2024
            break;
        case 129:
            level_str = "INFO";    // 0x202a
            break;
        case 130:
            level_str = "NOTICE";  // 0x2030
            break;
        case 131:
            level_str = "WARNING"; // 0x2038
            break;
        case 132:
            level_str = "ERROR";   // 0x203d
            break;
        case 133:
            level_str = "CRIT";    // 0x2045
            break;
        case 134:
            level_str = "ALERT";   // 0x204b
            break;
        case 135:
            level_str = "FATAL";   // 0x2051
            break;
        default:
            level_str = "UNKNOWN"; // 0x206f
            break;
    }
    
    return level_str;
}