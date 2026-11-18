struct hashtable *create_hash(size_t size) {

 struct hashtable *hashtable = NULL;
 size_t i;

 if((hashtable = malloc(sizeof(struct hashtable))) == NULL) {
  return NULL;
 }

 if((hashtable->table = malloc(sizeof(struct entry *) * size)) == NULL) {
  free(hashtable);
  return NULL;
 }
 for(i = 0; i < size; i++) {
  hashtable->table[i] = NULL;
 }

 hashtable->size = size;
 hashtable->entrycount = size;

 return hashtable;
}