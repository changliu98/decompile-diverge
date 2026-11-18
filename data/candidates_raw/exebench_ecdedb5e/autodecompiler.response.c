int read_double_from_socket(int sockfd, double *element){
    int size;
    size = read(sockfd,element,sizeof(double));
    if(size < 0) error("ERROR reading from socket");
    return size;
}