void func0(struct job_t *jobs) {
    int i;

    if (jobs == NULL)
        return;

    for (i = 0; i < MAXJOBS; i++)
        clearjob(&jobs[i]);
}