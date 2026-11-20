#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char tbuff1[128];
char tbuff2[128];
char *KEYWORDS[] = {"Computer Network", "IP Address", "MAC Address", "Default Gateway", "Subnet Mask", "Access Point", "Proxy Server", "Load Balancer", "OSI Model", "TCP/IP Model", "Packet Sniffing", "Packet Loss", "Spear Phishing", "Trojan Horse", "Logic Bomb", "Fileless Malware", "Root Access Exploitation", "Privilege Escalation", "Brute Force Attack", "Dictionary Attack", "Credential Stuffing", "Password Spraying", "Man-in-the-Middle Attack", "Denial of Service (DoS)", "Distributed Denial of Service (DDoS)", "SQL Injection", "Cross-Site Scripting (XSS)", "Cross-Site Request Forgery (CSRF)", "DNS Spoofing", "ARP Spoofing", "IP Spoofing", "Session Hijacking", "Replay Attack", "Evil Twin Attack", "Wi-Fi Deauthentication Attack", "Zero-Day Exploit", "Remote Code Execution (RCE)", "Directory Traversal", "Server-Side Request Forgery (SSRF)", "XML External Entity (XXE)", "Supply Chain Attack", "Insider Threat", "Social Engineering", "Data Exfiltration", "Watering Hole Attack", "DNS Tunneling", "Business Email Compromise (BEC)", "IPv4", "IPv6", "DNS", "DHCP", "Subnetting", "LAN", "WAN", "WLAN", "PAN", "MAN", "Router", "Switch", "Hub", "Modem", "Firewall", "NAT", "Port", "Protocol", "TCP", "UDP", "HTTP", "HTTPS", "FTP", "SSH", "Telnet", "SMTP", "POP3", "IMAP", "ICMP", "ARP", "Packet", "Bandwidth", "Latency", "Ping", "Traceroute", "VPN", "VLAN", "Routing", "pwd", "ls", "cd", "mkdir", "rmdir", "touch", "cp", "mv", "rm", "cat", "less", "head", "tail", "nano", "grep", "find", "locate", "which", "whereis", "chmod", "chown", "chgrp", "umask", "whoami", "id", "who", "passwd", "useradd", "usermod", "userdel", "groupadd", "groups", "sudo", "su", "ps", "top", "kill", "killall", "df", "du", "free", "uname", "hostname", "ip", "ping", "ss", "curl", "wget", "systemctl", "journalctl", "Phishing", "Whaling", "Smishing", "Vishing", "Ransomware", "Spyware", "Adware", "Worm", "Virus", "Rootkit", "Keylogger", "Botnet", "Backdoor", "Cryptojacking", "Malvertising"};
int keycoun = sizeof(KEYWORDS) / sizeof(KEYWORDS[0]);
void detect_intent(char *input, char *intent[2]) {
    intent[0] = NULL;
    intent[1] = NULL;
    char strin[256];
    strncpy(strin, input, sizeof(strin) - 1);
    strin[sizeof(strin) - 1] = '\0';
    _strlwr(strin);
    if (strstr(strin, "exit") || strstr(strin, "quit") || strstr(strin, "bye") ) {
        return;
    }
    int coun = 0;
    for (int i = 0; i < keycoun && coun < 2; i++) {
        char keylow[128];
        strncpy(keylow, KEYWORDS[i], sizeof(keylow) - 1);
        keylow[sizeof(keylow) - 1] = '\0';
        _strlwr(keylow);
        if (strstr(strin, keylow) != NULL) {
            if (coun == 0) {
                strcpy(tbuff1, KEYWORDS[i]);
                intent[0] = tbuff1;
                coun++;
            } 
            else if (coun == 1) {
                if (strcmp(tbuff1, KEYWORDS[i]) != 0){
                    strcpy(tbuff2, KEYWORDS[i]);
                    intent[1] = tbuff2;
                    coun = coun + 1;
                }
            }
        }
    }
    if (coun == 0) {
        strcpy(tbuff1, strin);
        intent[0] = tbuff1;
        intent[1] = NULL;
    }
}
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