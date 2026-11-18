int pid_to_processor_id(int pid) {
    int i = 0;
    int result;

    while (i < ncpus) {
        if (cpu_tasks[i] == pid) {
            result = i;
            return result;
        }
        i++;
    }
    
    result = -1;
    return result;
}