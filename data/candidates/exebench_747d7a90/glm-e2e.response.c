void fork_child(struct pipe_fds *fds, struct pipe_fds *out_fds, struct counter *cnt) {
    close(fds->write_fd);
    out_fds->read_fd = fds->read_fd;
    cnt->count++;
}