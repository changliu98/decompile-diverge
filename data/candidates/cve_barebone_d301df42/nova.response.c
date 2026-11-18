static int call_backend(char *path, int argc, char **argv, char **envp) {
    char cwd[1024];
    char *p;
    char *prog;
    char *args[1024];
    int status;

    strncpy(cwd, path, sizeof(cwd) - 1);
    if (strlen(path) > sizeof(cwd) - 1)
        cwd[sizeof(cwd) - 1] = '\0';
    p = strrchr(cwd, ':');
    if (p)
        *p = '\0';
    prog = getenv("_");
    if (prog == NULL)
        prog = "/bin/sh";
    if (strncmp(path, "/", 5) == 0 || path[0] == '/')
        args[0] = path;
    else
        args[0] = prog;
    args[1] = argv[1];
    args[2] = argv[2];
    args[3] = argv[3];
    if (argc == 6)
        args[4] = argv[4];
    else
        args[4] = argv[5];
    args[5] = NULL;
    execve(args[0], args, envp);
    sprintf(errmsg, "exec %s: %s", path, strerror(errno));
    perror(errmsg);
    status = WEXITSTATUS(status);
    if (status == -1) {
        char *s = strerror(errno);
        sprintf(errmsg, "exec %s: %s", path, s);
    }
    return status;
}