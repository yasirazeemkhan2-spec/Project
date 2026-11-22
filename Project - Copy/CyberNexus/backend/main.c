#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cJSON/cJSON.h"
#include "reader.c"
#include "intent.c"
#include "searching.c"
#include "response.c"

int main (){
    FILE *file;
    char line[500];
    char input[256];
    char *intent[2];
    while (1){
        if (!fgets(input, sizeof(input), stdin)) {
            return 0;
        }
        input[strcspn(input,"\r\n")] = '\0';
        if (strcasecmp(input, "hi") == 0 || strcasecmp(input, "hello") == 0 || strcasecmp(input, "hey") == 0) {
            if (!load_dataset("../data/data.json")) {
                printf("[Error] Could not load dataset. Exiting.\n");
                return 1;
            }

            file = fopen("../data/greetings.txt", "r");
            if (file == NULL){
                printf("Greetings file not found!\n");
            }
            else{
                while (fgets(line, sizeof(line), file) != NULL)            {
                    printf("%s", line);
                }
                fclose(file);
            }
            break;
        }
    }
    while(1){
        printf("\nYou: ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        input[strcspn(input, "\r\n")] = '\0';
        detect_intent(input, intent);
        
        if (intent[0] == NULL && intent[1] == NULL) {
            printf("\n[CyberNexus]: Goodbye! Exiting session...\n");
            break;
        }
        if (intent[0] != NULL && intent[1] == NULL) {
            char **result1 = search_keyword(intent[0]);
            generate_response(intent, result1, NULL);
        }
        else if (intent[0] != NULL && intent[1] != NULL) {
            char **result1 = search_keyword(intent[0]);
            char **result2 = search_keyword(intent[1]);
            generate_response(intent, result1, result2);
        }
    }
    return 0;
}