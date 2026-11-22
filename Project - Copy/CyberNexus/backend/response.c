#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_response(char *intent[2], char **result1, char **result2) {
    printf("\n");

    if (result2 != NULL) {
        printf("  [CyberNexus] COMPARISON: %s vs %s\n", intent[0], intent[1]);

        printf("\n[01] %s:\n", intent[0]);
        if (result1 != NULL) {
            printf("  Definition : %s\n", result1[0]);
            printf("  Example    : %s\n", result1[1]);
        } else {
            printf("  [!] Record not found in database.\n");
        }

        printf("\n");

        printf("[02] %s:\n", intent[1]);
        if (result2 != NULL) {
            printf("  Definition : %s\n", result2[0]);
            printf("  Example    : %s\n", result2[1]);
        } else {
            printf("  [!] Record not found in database.\n");
        }

    }

    else {
        if (result1 != NULL) {
            printf("  [CyberNexus]: %s\n", intent[0]);
            printf("  Definition : %s\n", result1[0]);
            printf("  Example    : %s\n", result1[1]);
        } else {
            printf("[CyberNexus]: Sorry, \"%s\" I am unable to answer this question. To train me further, you must have admin access to the source code.\n", intent[0]);
        }
    }
}