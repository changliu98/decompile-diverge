__attribute__((used)) static int HashTableNext(int iPriorHash){
  return (iPriorHash+1)&(HASHTABLE_NSLOT-1);
}