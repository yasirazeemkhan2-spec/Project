#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int match_strings(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return 0;
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return 0;
        }
        s1++;
        s2++;
    }
    return (*s1 == '\0' && *s2 == '\0');
}


char** search_keyword(const char *keyword) {
    if (keyword == NULL || strlen(keyword) == 0) {
        return NULL;
    }

    cJSON *root = get_dataset_root();
    if (root == NULL) {
        printf("[Error] Dataset is not loaded in memory.\n");
        return NULL;
    }

    char *categories[3] = {
        "Networking",
        "Linux Commands",
        "Cyber Threats"
    };

    for (int i = 0; i < 3; i++) {
        cJSON *category_array = cJSON_GetObjectItemCaseSensitive(root, categories[i]);


        int count = cJSON_GetArraySize(category_array);

        for (int j = 0; j < count; j++) {
            cJSON *item = cJSON_GetArrayItem(category_array, j);


            cJSON *term_item = cJSON_GetObjectItemCaseSensitive(item, "term");
            cJSON *def_item  = cJSON_GetObjectItemCaseSensitive(item, "definition");
            cJSON *ex_item   = cJSON_GetObjectItemCaseSensitive(item, "example");

            char *term_str = cJSON_GetStringValue(term_item);

            if (match_strings(term_str, keyword)) {
                char **result = (char **)malloc(2 * sizeof(char *));
                if (result == NULL) {
                    return NULL;
                }
                result[0] = (char *)cJSON_GetStringValue(def_item);
                result[1] = cJSON_IsString(ex_item) ? (char *)cJSON_GetStringValue(ex_item) : "No example provided.";
                return result;
            }
        }
    }
    return NULL;
}
