int read_double(int sockfd, double *element){
    int size;
    size = read(sockfd,element,sizeof(double));
    if(size < 0) error("ERROR reading from socket");
    return size;
}