int read_double(int qid, double *time_recvd) {
    int rc;
    struct msg msg;

    rc = rcv_msg(qid, &msg, sizeof(msg));
    *time_recvd = msg.body.time_recvd;

    return rc;
}