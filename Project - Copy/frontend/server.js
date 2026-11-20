const http = require('http');
const fs = require('fs');
const path = require('path');
const { spawn } = require('child_process');

const PORT = 3000;
const BACKEND_DIR = path.join(__dirname, '..', 'backend');
const EXE_PATH = path.join(BACKEND_DIR, 'cybernexus.exe');
const DATA_PATH = path.join(__dirname, '..', 'data', 'data.json');

let botProcess = null;
let currentResolve = null;
let responseBuffer = '';

// Spawn C executable in the background
function initCyberNexusProcess() {
    try {
        if (!fs.existsSync(EXE_PATH)) {
            console.log('[Warning] cybernexus.exe not found. Running with direct JSON search mode.');
            return;
        }

        botProcess = spawn(EXE_PATH, [], {
            cwd: BACKEND_DIR,
            stdio: ['pipe', 'pipe', 'pipe']
        });

        botProcess.stdout.on('data', (data) => {
            const chunk = data.toString();
            responseBuffer += chunk;

            // When C process is asking for input (prompting with "You: " or greeting)
            if (responseBuffer.includes('You:') || responseBuffer.includes('say \'hi\' or \'hello\'')) {
                if (currentResolve) {
                    const output = responseBuffer;
                    responseBuffer = '';
                    const cb = currentResolve;
                    currentResolve = null;
                    cb(output);
                }
            }
        });

        botProcess.stderr.on('data', (err) => {
            console.error('[Bot Error]:', err.toString());
        });

        botProcess.on('close', (code) => {
            console.log(`[Bot Exited with code ${code}]. Restarting...`);
            botProcess = null;
        });

        // Initialize with greeting
        setTimeout(() => {
            if (botProcess && botProcess.stdin.writable) {
                botProcess.stdin.write('hi\n');
            }
        }, 500);

    } catch (e) {
        console.error('Failed to launch cybernexus.exe:', e);
    }
}

// Send message to C executable
function askCyberNexus(message) {
    return new Promise((resolve) => {
        if (!botProcess || !botProcess.stdin.writable) {
            initCyberNexusProcess();
        }

        if (botProcess && botProcess.stdin.writable) {
            currentResolve = resolve;
            responseBuffer = '';
            botProcess.stdin.write(message + '\n');

            // Timeout safety (2 seconds)
            setTimeout(() => {
                if (currentResolve === resolve) {
                    currentResolve = null;
                    resolve(responseBuffer || fallbackSearch(message));
                    responseBuffer = '';
                }
            }, 1500);
        } else {
            resolve(fallbackSearch(message));
        }
    });
}

// Word boundary check helper
function hasWord(text, word) {
    const w = word.toLowerCase();
    const t = text.toLowerCase();
    const idx = t.indexOf(w);
    if (idx === -1) return false;
    const before = idx === 0 ? ' ' : t[idx - 1];
    const after = (idx + w.length >= t.length) ? ' ' : t[idx + w.length];
    const isAlphaNum = c => /[a-z0-9]/i.test(c);
    return !isAlphaNum(before) && !isAlphaNum(after);
}

// Resilient Search: Searches data.json with full support for Single Terms and Comparisons
function fallbackSearch(keyword) {
    try {
        const raw = fs.readFileSync(DATA_PATH, 'utf8');
        const data = JSON.parse(raw);
        const categories = ["Networking", "Linux Commands", "Cyber Threats"];
        const matches = [];

        // 1. Scan across categories for matched terms
        for (const cat of categories) {
            const arr = data[cat] || [];
            for (const item of arr) {
                if (hasWord(keyword, item.term)) {
                    if (!matches.some(m => m.term.toLowerCase() === item.term.toLowerCase())) {
                        matches.push(item);
                    }
                }
            }
        }

        // 2. Comparison detected: 2 or more terms
        if (matches.length >= 2) {
            const m1 = matches[0];
            const m2 = matches[1];
            return `  [CyberNexus] COMPARISON: ${m1.term} vs ${m2.term}\n\n[01] ${m1.term}:\n  Definition : ${m1.definition}\n  Example    : ${m1.example}\n\n[02] ${m2.term}:\n  Definition : ${m2.definition}\n  Example    : ${m2.example}`;
        }

        // 3. Single question: 1 term
        if (matches.length === 1) {
            const m = matches[0];
            return `  [CyberNexus]: ${m.term}\n  Definition : ${m.definition}\n  Example    : ${m.example}`;
        }

        return `[CyberNexus]: Sorry, "${keyword}" was not found in the database.`;
    } catch (e) {
        return `[CyberNexus]: Error reading database.`;
    }
}

// Start bot process
initCyberNexusProcess();

const GREETINGS = ['hi', 'hello', 'hey', 'greetings', 'start', 'sup', 'yo', 'welcome', 'who are you', 'help'];

function isGreeting(text) {
    const clean = (text || '').toLowerCase().trim().replace(/[?!.,]/g, '');
    return GREETINGS.includes(clean) || 
           clean.startsWith('hello') || 
           clean.startsWith('hi ') || 
           clean.startsWith('hey ');
}

const GREETING_RESPONSE = `[CyberNexus]: Hello! Welcome to CyberNexus.
Ready to explore the world of Cybersecurity?
I can help you explore, understand, and master three essential domains:
• [01] NETWORKING (e.g. DNS, IP Address, Subnetting, TCP vs UDP)
• [02] LINUX COMMANDS (e.g. ls, grep, chmod, systemctl)
• [03] CYBER THREATS (e.g. Phishing, Ransomware, DDoS, SQL Injection)

Ask me about any term or compare two concepts!`;

const FAREWELLS = ['bye', 'goodbye', 'exit', 'quit', 'cya', 'see you', 'leave'];
function isFarewell(text) {
    const clean = (text || '').toLowerCase().trim().replace(/[?!.,]/g, '');
    return FAREWELLS.includes(clean) || 
           clean.startsWith('bye ') || 
           clean.startsWith('goodbye');
}

const FAREWELL_RESPONSE = `[CyberNexus]: Goodbye! Stay safe in cyberspace.
Feel free to ask about any Networking, Linux, or Cyber Threat topics whenever you are ready!`;

const THANKS = ['thanks', 'thank you', 'thx', 'thankyou', 'appreciate it'];
function isThanks(text) {
    const clean = (text || '').toLowerCase().trim().replace(/[?!.,]/g, '');
    return THANKS.includes(clean) || 
           clean.startsWith('thanks ') || 
           clean.startsWith('thank you');
}

const THANKS_RESPONSE = `[CyberNexus]: You're very welcome!
Let me know if you need any more explanations or comparisons across Cybersecurity, Linux, or Networking!`;

// HTTP Server
const server = http.createServer(async (req, res) => {
    // API: POST /api/chat
    if (req.method === 'POST' && req.url === '/api/chat') {
        let body = '';
        req.on('data', chunk => { body += chunk; });
        req.on('end', async () => {
            try {
                const parsed = JSON.parse(body || '{}');
                const message = (parsed.message || '').trim();

                // Intercept greetings directly
                if (isGreeting(message)) {
                    res.writeHead(200, { 'Content-Type': 'application/json' });
                    res.end(JSON.stringify({ reply: GREETING_RESPONSE }));
                    return;
                }

                // Intercept farewells directly so cybernexus.exe does not exit
                if (isFarewell(message)) {
                    res.writeHead(200, { 'Content-Type': 'application/json' });
                    res.end(JSON.stringify({ reply: FAREWELL_RESPONSE }));
                    return;
                }

                // Intercept thank you courtesies
                if (isThanks(message)) {
                    res.writeHead(200, { 'Content-Type': 'application/json' });
                    res.end(JSON.stringify({ reply: THANKS_RESPONSE }));
                    return;
                }

                const reply = await askCyberNexus(message);
                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ reply }));
            } catch (err) {
                res.writeHead(500, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ error: err.message }));
            }
        });
        return;
    }

    // Static Files: GET /
    let filePath = path.join(__dirname, req.url === '/' ? 'index.html' : req.url);
    const ext = path.extname(filePath);
    const contentTypes = {
        '.html': 'text/html',
        '.css': 'text/css',
        '.js': 'application/javascript',
        '.svg': 'image/svg+xml',
        '.json': 'application/json'
    };

    fs.readFile(filePath, (err, content) => {
        if (err) {
            res.writeHead(404, { 'Content-Type': 'text/plain' });
            res.end('404 Not Found');
        } else {
            res.writeHead(200, { 'Content-Type': contentTypes[ext] || 'text/plain' });
            res.end(content);
        }
    });
});

server.listen(PORT, () => {
    console.log(`====================================================`);
    console.log(`  Cyber Bot GUI Server running at: http://localhost:${PORT}`);
    console.log(`====================================================`);
});
