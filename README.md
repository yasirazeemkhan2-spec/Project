# CyberNexus - Cybersecurity AI Assistant

An intelligent, modular cybersecurity assistant featuring a high-performance **C backend** and a modern **Dark-Green Hacker Web GUI**.

---

## 🚀 Features

- **Modular Pointer-Based C Backend:** Clean separation of concerns across `main.c`, `reader.c`, `intent.c`, `searching.c`, and `response.c`.
- **In-Memory cJSON Search Engine:** Parses `data.json` once into RAM upon greeting for instant queries.
- **Multi-Term Comparison Engine:** Automatically detects and contrasts concepts (e.g., `compare TCP and UDP` or `difference between hub and switch`).
- **Dark-Green Hacker Web Interface:** Responsive terminal UI with a revolving 3D wireframe cyber-globe and animated blinking hacker avatar.
- **150+ Built-In Cybersecurity Topics:** Across three core domains:
  1. **Networking:** DNS, IPv4/IPv6, Subnetting, TCP, UDP, Routers, Switches, Firewalls, etc.
  2. **Linux Commands:** pwd, ls, cd, grep, chmod, chown, systemctl, etc.
  3. **Cyber Threats:** Phishing, Ransomware, DDoS, SQL Injection, Zero-Day Exploits, etc.

---

## 📁 Project Structure

```text
Project/
├── backend/
│   ├── cJSON/           # cJSON library (cJSON.c, cJSON.h)
│   ├── cybernexus.exe   # Compiled standalone executable
│   ├── intent.c         # Keyword extraction & intent classification
│   ├── main.c           # Main controller loop
│   ├── reader.c         # In-memory dataset loader
│   ├── response.c       # Output formatting (comparisons & single terms)
│   └── searching.c      # Case-insensitive in-memory search engine
├── data/
│   ├── data.json        # 150+ cybersecurity definitions & examples
│   └── greetings.txt    # ASCII banner
├── frontend/
│   ├── app.js           # Client-side chat logic & 3D canvas animation
│   ├── data.js          # Standalone client data fallback
│   ├── index.html       # Cyberpunk terminal interface
│   ├── server.js        # Lightweight Node.js bridge to C backend
│   └── style.css        # Hacker dark-green neon styling
├── Run_GUI.bat          # 1-click launcher for the Web GUI
└── Run_Console.bat      # 1-click launcher for the C Console
```

---

## 💻 How to Run (Zero Setup Required)

### Option 1: Interactive Web GUI (Recommended)
Double-click **`Run_GUI.bat`**.
- If Node.js is installed on your PC, it starts the local server and connects directly to the C backend.
- If Node.js is **not** installed, it automatically launches the Cyber Bot GUI directly in your default browser in offline mode.

### Option 2: Pure C Terminal Console
Double-click **`Run_Console.bat`** (or run `backend/cybernexus.exe`).
- Requires zero dependencies—runs natively on any Windows computer.
- Type `hi` or `hello` to begin the session, then ask queries or comparisons.
