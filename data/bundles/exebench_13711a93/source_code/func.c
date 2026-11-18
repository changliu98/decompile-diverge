
void cgi_sys_get_action(char * shm){
 *(int *)(shm+sizeof(int)) = 6;
 *(int *)(shm+sizeof(int)*2) = 1;
}
