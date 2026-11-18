
void cgi_store_get_action(char * shm){
 *(int *)(shm+sizeof(int)) = 4;
 *(int *)(shm+sizeof(int)*2) = 1;
}
