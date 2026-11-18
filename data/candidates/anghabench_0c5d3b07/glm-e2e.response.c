const char* get_priority_string(int priority) {
    const char* result;
    
    // The assembly subtracts 128 (0xffffff80 is -128 in 2's complement) 
    // and checks if the value is > 3 (unsigned), which means it checks 
    // if priority is between 128 and 131 inclusive.
    if (priority >= 128 && priority <= 131) {
        switch (priority) {
            case 128:
                result = "Low";    // 0x2014
                break;
            case 129:
                result = "Medium"; // 0x2020
                break;
            case 130:
                result = "High";   // 0x2024
                break;
            case 131:
                result = "Urgent"; // 0x202c
                break;
        }
    } else {
        result = "Unknown";        // 0x2036
    }
    
    return result;
}