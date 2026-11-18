cJSON *get_object_item( cJSON *object, const char *string, cJSON_bool case_sensitive )
{
 cJSON *current_element = NULL;

 if ( ( object == NULL ) || ( string == NULL ) )
 {
  return NULL;
 }

 current_element = object->child;
 if ( case_sensitive )
 {
  while ( ( current_element != NULL ) && ( strcmp( string, current_element->string ) != 0 ) )
  {
   current_element = current_element->next;
  }
 }
 else
 {
  while ( ( current_element != NULL ) && ( case_insensitive_strcmp( string, current_element->string ) != 0 ) )
  {
   current_element = current_element->next;
  }
 }

 return current_element;
}