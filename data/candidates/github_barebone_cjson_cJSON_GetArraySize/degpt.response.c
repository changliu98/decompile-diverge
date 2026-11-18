// Get the number of elements in a JSON array
int cJSON_GetArraySize(cJSON *json_array)
{
    int element_count = 0;
    if (json_array) {
        // Iterate through all child nodes of the array
        for (cJSON *current_node = json_array->child; current_node; current_node = current_node->next) {
            element_count++;
        }
    }
    return element_count;
}