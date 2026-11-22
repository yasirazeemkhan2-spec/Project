#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char tbuff1[128];
char tbuff2[128];
char *KEYWORDS[] = {
    "Computer Network", "IP Address", "IPv4", "IPv6", "MAC Address", "DNS", "DHCP", "Default Gateway",
    "Subnet Mask", "Subnetting", "LAN", "WAN", "WLAN", "PAN", "MAN", "Router", "Switch", "Hub", "Modem",
    "Access Point", "Firewall", "NAT", "Port", "Protocol", "TCP", "UDP", "HTTP", "HTTPS", "FTP", "SSH",
    "Telnet", "SMTP", "POP3", "IMAP", "ICMP", "ARP", "Packet", "Bandwidth", "Latency", "Packet Loss", "Ping",
    "Traceroute", "VPN", "Proxy Server", "Load Balancer", "VLAN", "OSI Model", "TCP/IP Model", "Routing",
    "Packet Sniffing", "Network Topology", "Bus Topology", "Star Topology", "Ring Topology", "Mesh Topology",
    "Hybrid Topology", "Client-Server Model", "Peer-to-Peer (P2P) Network", "Intranet", "Extranet",
    "Network Interface Card (NIC)", "Ethernet", "Wi-Fi", "Bluetooth", "Fiber Optic Cable",
    "Twisted Pair Cable", "Coaxial Cable", "RJ45 Connector", "Repeater", "Bridge", "Gateway",
    "Layer 3 Switch", "Patch Panel", "Network Attached Storage (NAS)", "Physical Layer", "Data Link Layer",
    "Network Layer", "Transport Layer", "Session Layer", "Presentation Layer", "Application Layer", "Frame",
    "Segment", "Datagram", "MTU", "Encapsulation", "Throughput", "Jitter", "Round-Trip Time (RTT)",
    "Time to Live (TTL)", "Quality of Service (QoS)", "Traffic Shaping", "Full Duplex", "Half Duplex",
    "Unicast", "Broadcast", "Multicast", "Anycast", "Broadcast Domain", "Collision Domain", "CSMA/CD",
    "CSMA/CA", "Circuit Switching", "Packet Switching", "Multiplexing", "Three-Way Handshake",
    "Flow Control", "Congestion Control", "Sliding Window", "Trunk Port", "Spanning Tree Protocol (STP)",
    "Link Aggregation", "Port Mirroring", "Power over Ethernet (PoE)", "Port Forwarding", "DMZ",
    "Intrusion Detection System (IDS)", "Intrusion Prevention System (IPS)", "Honeypot",
    "Network Segmentation", "Zero Trust", "Access Control List (ACL)", "TLS", "SSL", "IPsec", "WPA2", "WPA3",
    "WEP", "SSID", "802.11", "Wi-Fi Channel", "Captive Portal", "Wi-Fi Protected Setup (WPS)",
    "Site-to-Site VPN", "CIDR", "VLSM", "Private IP Address", "Public IP Address", "Static IP Address",
    "Dynamic IP Address", "APIPA", "Loopback Address", "Localhost", "Broadcast Address", "Network Address",
    "Default Route", "Static Routing", "Dynamic Routing", "RIP", "OSPF", "BGP", "EIGRP",
    "Autonomous System (AS)", "Routing Table", "Hop Count", "Route Convergence", "Domain Name", "FQDN",
    "DNS Resolver", "Root Name Server", "Authoritative Name Server", "DNS Cache", "A Record", "AAAA Record",
    "CNAME Record", "MX Record", "NS Record", "PTR Record", "TXT Record", "DNSSEC", "URL", "Web Server",
    "HTTP Status Code", "HTTP GET", "HTTP POST", "Cookie", "CDN", "REST API", "WebSocket", "Reverse Proxy",
    "SNMP", "NTP", "TFTP", "SFTP", "LDAP", "Kerberos", "RDP", "SMB", "NFS", "DHCP Lease", "VoIP", "SIP",
    "Wireshark", "Nmap", "Network Monitoring", "PAT", "Software-Defined Networking (SDN)", "Wake-on-LAN",
    "IoT", "Port Security", "pwd", "ls", "cd", "mkdir", "rmdir", "touch", "cp", "mv", "rm", "cat", "less",
    "head", "tail", "nano", "grep", "find", "locate", "which", "whereis", "chmod", "chown", "chgrp", "umask",
    "whoami", "id", "who", "passwd", "useradd", "usermod", "userdel", "groupadd", "groups", "sudo", "su",
    "ps", "top", "kill", "killall", "df", "du", "free", "uname", "hostname", "cd /", "ping", "cd -", "curl",
    "wget", "systemctl", "journalctl", "tree", "stat", "file", "ln", "basename", "dirname", "realpath",
    "shred", "dd", "wc", "sort", "uniq", "cut", "tr", "sed", "awk", "diff", "tee", "xargs", "echo", "printf",
    "more", "hexdump", "xxd", "strings", "man", "info", "whatis", "apropos", "type", "updatedb", "tar",
    "gzip", "gunzip", "bzip2", "xz", "zip", "unzip", "setfacl", "getfacl", "chattr", "lsattr", "visudo",
    "gpasswd", "chage", "last", "lastb", "lastlog", "adduser", "deluser", "groupdel", "groupmod", "chsh",
    "newgrp", "pstree", "pgrep", "pkill", "nice", "renice", "nohup", "bg", "fg", "jobs", "htop", "watch",
    "lsof", "strace", "vmstat", "iostat", "uptime", "dmesg", "time", "timeout", "sleep", "crontab", "tmux",
    "lscpu", "lsblk", "lsusb", "lspci", "lshw", "dmidecode", "mount", "umount", "fdisk", "mkfs", "fsck",
    "blkid", "swapon", "sync", "reboot", "shutdown", "poweroff", "date", "timedatectl", "hostnamectl", "env",
    "export", "alias", "history", "source", "clear", "ulimit", "ip", "ss", "ifconfig", "netstat", "nslookup",
    "dig", "host", "route", "tcpdump", "nc", "iptables", "ufw", "sshd", "ssh-agent", "ssh-keygen",
    "ssh-copy-id", "scp", "rsync", "whois", "mtr", "nmcli", "ethtool", "tracepath", "openssl", "gpg",
    "sha256sum", "md5sum", "base64", "apt", "dpkg", "dnf", "rpm", "service", "modprobe", "lsmod", "sysctl",
    "chkrootkit", "rkhunter", "lynis", "clamscan", "fail2ban-client", "auditctl", "getenforce", "sestatus",
    "aa-status", "logrotate", "logger", "Phishing", "Spear Phishing", "Whaling", "Smishing", "Vishing",
    "Ransomware", "Spyware", "Adware", "Trojan Horse", "Worm", "Virus", "Rootkit", "Keylogger", "Botnet",
    "Backdoor", "Logic Bomb", "Cryptojacking", "Fileless Malware", "Root Access Exploitation",
    "Privilege Escalation", "Brute Force Attack", "Dictionary Attack", "Credential Stuffing",
    "Password Spraying", "Man-in-the-Middle Attack", "Denial of Service (DoS)",
    "Distributed Denial of Service (DDoS)", "SQL Injection", "Cross-Site Scripting (XSS)",
    "Cross-Site Request Forgery (CSRF)", "DNS Spoofing", "ARP Spoofing", "IP Spoofing", "Session Hijacking",
    "Replay Attack", "Evil Twin Attack", "Wi-Fi Deauthentication Attack", "Zero-Day Exploit",
    "Remote Code Execution (RCE)", "Directory Traversal", "Server-Side Request Forgery (SSRF)",
    "XML External Entity (XXE)", "Supply Chain Attack", "Insider Threat", "Social Engineering",
    "Data Exfiltration", "Watering Hole Attack", "Malvertising", "DNS Tunneling",
    "Business Email Compromise (BEC)", "Malware", "Scareware", "Ransomware-as-a-Service (RaaS)",
    "Wiper Malware", "Bootkit", "Polymorphic Malware", "Metamorphic Malware", "Macro Virus",
    "Boot Sector Virus", "Remote Access Trojan (RAT)", "Banking Trojan", "Dropper", "Loader", "Payload",
    "Exploit Kit", "Infostealer", "Mobile Malware", "Stalkerware", "Browser Hijacker",
    "Potentially Unwanted Program (PUP)", "Command and Control (C2)", "Zombie Computer", "Spam",
    "Drive-by Download", "Advanced Persistent Threat (APT)", "Living off the Land (LotL)",
    "Process Injection", "DLL Hijacking", "Lateral Movement", "Code Injection", "Zero-Click Exploit",
    "Persistence Mechanism", "Buffer Overflow", "Heap Overflow", "Format String Attack", "Integer Overflow",
    "Race Condition", "Use-After-Free", "Return-Oriented Programming (ROP)", "Shellcode", "Reverse Shell",
    "Bind Shell", "Web Shell", "Command Injection", "LDAP Injection", "NoSQL Injection", "XPath Injection",
    "Blind SQL Injection", "HTML Injection", "Host Header Injection", "Insecure Deserialization",
    "Broken Authentication", "Broken Access Control", "Insecure Direct Object Reference (IDOR)",
    "Security Misconfiguration", "Sensitive Data Exposure", "Open Redirect", "Local File Inclusion (LFI)",
    "Remote File Inclusion (RFI)", "Unrestricted File Upload", "HTTP Request Smuggling",
    "HTTP Parameter Pollution", "Clickjacking", "CORS Misconfiguration", "Subdomain Takeover",
    "DNS Hijacking", "DNS Cache Poisoning", "DNS Amplification Attack", "SYN Flood", "UDP Flood",
    "ICMP Flood", "Ping of Death", "Smurf Attack", "Slowloris", "HTTP Flood", "Teardrop Attack",
    "MAC Flooding", "MAC Spoofing", "VLAN Hopping", "DHCP Starvation", "Rogue DHCP Server",
    "Rogue Access Point", "Bluejacking", "Bluesnarfing", "KRACK Attack", "Wardriving", "Wireless Jamming",
    "Port Scanning", "Footprinting", "OSINT", "Banner Grabbing", "Vulnerability Scanning", "Enumeration",
    "Pretexting", "Baiting", "Tailgating", "Quid Pro Quo", "Shoulder Surfing", "Dumpster Diving",
    "Typosquatting", "Pharming", "Clone Phishing", "Credential Harvesting", "Deepfake", "Email Spoofing",
    "Quishing", "SIM Swapping", "Pass-the-Hash", "Pass-the-Ticket", "Kerberoasting", "Golden Ticket Attack",
    "Rainbow Table Attack", "Hash Collision Attack", "Birthday Attack", "BadUSB Attack", "Cold Boot Attack",
    "Evil Maid Attack", "Side-Channel Attack", "Spectre", "Meltdown", "Rowhammer", "Downgrade Attack",
    "SSL Stripping", "Padding Oracle Attack", "Heartbleed", "Shellshock", "Log4Shell", "EternalBlue",
    "Mirai Botnet", "Stuxnet", "Data Breach", "Data Leak", "Identity Theft", "Account Takeover", "Doxing",
    "Cyberstalking", "Click Fraud", "Card Skimming", "Formjacking", "Carding", "Misconfigured Cloud Storage",
    "Cloud Account Hijacking", "API Abuse", "Container Escape", "Prompt Injection", "Data Poisoning",
    "Adversarial Attack", "Dependency Confusion", "Malicious Browser Extension", "Hacktivism"
};
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