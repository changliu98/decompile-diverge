
void cgi_network_get_action(char * shm){
 *(int *)(shm+sizeof(int)) = 2;
 *(int *)(shm+sizeof(int)*2) = 1;
}
