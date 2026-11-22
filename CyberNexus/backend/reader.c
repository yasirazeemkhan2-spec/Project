#include <stdio.h>
#include <stdlib.h>
#include <string.h>
cJSON *dataset_root = NULL;
int flag = 0;

int load_dataset(const char *filename) {
    int is_data_loaded;
    if (flag && dataset_root != NULL) {
        return 1; 
    }
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("[Error] Cannot open dataset file: %s\n", filename);
        return 0;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        printf("[Error] Memory allocation failed while loading dataset.\n");
        fclose(file);
        return 0;
    }
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);
    dataset_root = cJSON_Parse(buffer);
    
    free(buffer);
    if (dataset_root == NULL) {
        printf("[Error] Failed to parse JSON data.\n");
        return 0;
    }
    if (!cJSON_IsObject(dataset_root)) {
        printf("[Error] Invalid JSON format: root is not an object.\n");
        cJSON_Delete(dataset_root);
        dataset_root = NULL;
        return 0;
    }
    is_data_loaded = 1;
    return 1;
}
cJSON* get_dataset_root(void) {
    return dataset_root;
}