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