document.addEventListener('DOMContentLoaded', () => {
    const heroView = document.getElementById('hero-view');
    const chatView = document.getElementById('chat-view');
    const messagesList = document.getElementById('messages-list');
    const chatForm = document.getElementById('chat-form');
    const userInput = document.getElementById('user-input');
    const resetBtn = document.getElementById('reset-btn');
    const chips = document.querySelectorAll('.chip');

    let isHeroActive = true;

    // ----------------------------------------------------
    // 1. REVOLVING 3D CYBER GLOBE ANIMATION (CANVAS)
    // ----------------------------------------------------
    const canvas = document.getElementById('globe-canvas');
    if (canvas) {
        const ctx = canvas.getContext('2d');
        const cx = canvas.width / 2;
        const cy = canvas.height / 2;
        const radius = 95;
        let rotationAngle = 0;

        // Satellite cyber nodes orbiting the globe
        const satellites = [
            { angle: 0, speed: 0.02, tilt: -0.3, r: 104, size: 2.5 },
            { angle: 2.1, speed: 0.015, tilt: 0.4, r: 108, size: 2 },
            { angle: 4.2, speed: 0.025, tilt: 0.1, r: 100, size: 3 }
        ];

        function drawCyberGlobe() {
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            // 1. Outer boundary aura
            ctx.beginPath();
            ctx.arc(cx, cy, radius, 0, Math.PI * 2);
            ctx.strokeStyle = 'rgba(16, 185, 129, 0.4)';
            ctx.lineWidth = 1.5;
            ctx.stroke();

            // 2. Horizontal Latitude Lines
            const latitudes = [-65, -35, 0, 35, 65];
            latitudes.forEach(latY => {
                const rLat = Math.sqrt(radius * radius - latY * latY);
                ctx.beginPath();
                ctx.ellipse(cx, cy + latY, rLat, rLat * 0.25, 0, 0, Math.PI * 2);
                ctx.strokeStyle = 'rgba(16, 185, 129, 0.15)';
                ctx.lineWidth = 1;
                ctx.stroke();
            });

            // 3. Rotating Longitude Meridians (3D sphere effect)
            const meridianCount = 6;
            for (let i = 0; i < meridianCount; i++) {
                const phi = rotationAngle + (i * Math.PI) / meridianCount;
                const cosPhi = Math.cos(phi);

                ctx.beginPath();
                // Major axis is vertical, minor axis shrinks with cos(phi)
                ctx.ellipse(cx, cy, Math.abs(cosPhi) * radius, radius, 0, 0, Math.PI * 2);
                
                // Front hemisphere is brighter, back hemisphere is dimmer
                if (cosPhi >= 0) {
                    ctx.strokeStyle = 'rgba(0, 255, 102, 0.45)';
                    ctx.lineWidth = 1.2;
                } else {
                    ctx.strokeStyle = 'rgba(16, 185, 129, 0.12)';
                    ctx.lineWidth = 0.8;
                }
                ctx.stroke();
            }

            // 4. Orbiting Cyber Satellites
            satellites.forEach(sat => {
                sat.angle += sat.speed;
                const x = cx + Math.cos(sat.angle) * sat.r;
                const y = cy + Math.sin(sat.angle) * (sat.r * 0.35) + (x - cx) * sat.tilt;

                ctx.beginPath();
                ctx.arc(x, y, sat.size, 0, Math.PI * 2);
                ctx.fillStyle = '#00ff66';
                ctx.shadowColor = '#00ff66';
                ctx.shadowBlur = 6;
                ctx.fill();
                ctx.shadowBlur = 0;
            });

            rotationAngle += 0.01;
            requestAnimationFrame(drawCyberGlobe);
        }

        drawCyberGlobe();
    }

    // ----------------------------------------------------
    // 2. CHAT & INTERACTION LOGIC
    // ----------------------------------------------------
    chatForm.addEventListener('submit', (e) => {
        e.preventDefault();
        const query = userInput.value.trim();
        if (!query) return;

        handleUserQuery(query);
        userInput.value = '';
    });

    // Quick chips click
    chips.forEach(chip => {
        chip.addEventListener('click', () => {
            const query = chip.dataset.query;
            handleUserQuery(query);
        });
    });

    // Reset button / ESC
    resetBtn.addEventListener('click', resetSession);
    document.addEventListener('keydown', (e) => {
        if (e.key === 'Escape') resetSession();
    });

    function resetSession() {
        messagesList.innerHTML = '';
        heroView.classList.remove('hidden');
        chatView.classList.add('hidden');
        isHeroActive = true;
        userInput.value = '';
        userInput.focus();
    }

    async function handleUserQuery(query) {
        if (isHeroActive) {
            heroView.classList.add('hidden');
            chatView.classList.remove('hidden');
            isHeroActive = false;
        }

        // Add user message
        appendMessage('user', query);

        // Check if query is a greeting
        const GREETINGS = ['hi', 'hello', 'hey', 'greetings', 'start', 'sup', 'yo', 'welcome', 'who are you', 'help'];
        const cleanQuery = query.toLowerCase().trim().replace(/[?!.,]/g, '');
        const isGreetingQuery = GREETINGS.includes(cleanQuery) || 
                                cleanQuery.startsWith('hello') || 
                                cleanQuery.startsWith('hi ') || 
                                cleanQuery.startsWith('hey ');

        if (isGreetingQuery) {
            const greetingMsg = `[CyberNexus]: Hello! Welcome to CyberNexus.
Ready to explore the world of Cybersecurity?
I can help you explore, understand, and master three essential domains:
• [01] NETWORKING (e.g. DNS, IP Address, Subnetting, TCP vs UDP)
• [02] LINUX COMMANDS (e.g. ls, grep, chmod, systemctl)
• [03] CYBER THREATS (e.g. Phishing, Ransomware, DDoS, SQL Injection)

Ask me about any term or compare two concepts!`;
            appendMessage('bot', greetingMsg);
            return;
        }

        // Check if query is a farewell (bye, exit, quit)
        const FAREWELLS = ['bye', 'goodbye', 'exit', 'quit', 'cya', 'see you', 'leave'];
        const isFarewellQuery = FAREWELLS.includes(cleanQuery) || 
                                cleanQuery.startsWith('bye ') || 
                                cleanQuery.startsWith('goodbye');

        if (isFarewellQuery) {
            const farewellMsg = `[CyberNexus]: Goodbye! Stay safe in cyberspace.
Feel free to ask about any Networking, Linux, or Cyber Threat topics whenever you are ready!`;
            appendMessage('bot', farewellMsg);
            return;
        }

        // Check if query is a thank you
        const THANKS = ['thanks', 'thank you', 'thx', 'thankyou', 'appreciate it'];
        const isThanksQuery = THANKS.includes(cleanQuery) || 
                              cleanQuery.startsWith('thanks ') || 
                              cleanQuery.startsWith('thank you');

        if (isThanksQuery) {
            const thanksMsg = `[CyberNexus]: You're very welcome!
Let me know if you need any more explanations or comparisons across Cybersecurity, Linux, or Networking!`;
            appendMessage('bot', thanksMsg);
            return;
        }

        // Add typing indicator
        const typingId = appendTyping();

        try {
            const res = await fetch('/api/chat', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ message: query })
            });
            const data = await res.json();
            removeElement(typingId);

            if (data && data.reply) {
                appendMessage('bot', data.reply);
            } else {
                appendMessage('bot', 'No response received from engine.');
            }
        } catch (err) {
            removeElement(typingId);
            appendMessage('bot', '[ERROR] Failed to reach backend server. Ensure server is active.');
        }
    }

    function getTimeString() {
        const d = new Date();
        return d.getHours().toString().padStart(2, '0') + ':' + 
               d.getMinutes().toString().padStart(2, '0');
    }

    function appendMessage(sender, content) {
        const row = document.createElement('div');
        row.className = `message-row ${sender}`;

        const badge = document.createElement('div');
        badge.className = 'msg-badge';
        badge.textContent = sender === 'user' ? 'USER' : 'BOT';

        const wrapper = document.createElement('div');
        wrapper.className = 'msg-content-wrapper';

        const bubble = document.createElement('div');
        bubble.className = 'msg-content';

        if (sender === 'user') {
            bubble.textContent = content;
        } else {
            bubble.innerHTML = formatBotResponse(content);
        }

        const time = document.createElement('div');
        time.className = 'msg-time';
        time.textContent = getTimeString();

        wrapper.appendChild(bubble);
        wrapper.appendChild(time);

        row.appendChild(badge);
        row.appendChild(wrapper);

        messagesList.appendChild(row);
        chatView.scrollTop = chatView.scrollHeight;
    }

    function appendTyping() {
        const id = 'typing-' + Date.now();
        const row = document.createElement('div');
        row.id = id;
        row.className = 'message-row bot';
        row.innerHTML = `
            <div class="msg-badge">BOT</div>
            <div class="msg-content-wrapper">
                <div class="msg-content" style="color: var(--neon-green); font-family: var(--font-mono); font-size: 13px;">
                    &gt; QUERYING_DATABASE...
                </div>
            </div>
        `;
        messagesList.appendChild(row);
        chatView.scrollTop = chatView.scrollHeight;
        return id;
    }

    function removeElement(id) {
        const el = document.getElementById(id);
        if (el) el.remove();
    }

    // Clean formatting for terminal C output
    function formatBotResponse(raw) {
        if (!raw) return 'No response.';

        const cleanLines = raw.split('\n')
            .map(l => l.trim())
            .filter(l => l.length > 0 && !l.startsWith('===') && !l.startsWith('---') && !l.startsWith('You:'));

        if (cleanLines.length === 0) return escapeHtml(raw);

        let html = '';
        cleanLines.forEach(line => {
            if (line.includes('[CyberNexus] COMPARISON:')) {
                const title = line.replace('[CyberNexus] COMPARISON:', '').trim();
                html += `<div class="term-header">COMPARISON // ${escapeHtml(title)}</div>`;
            } else if (line.startsWith('[CyberNexus]:')) {
                const term = line.replace('[CyberNexus]:', '').trim();
                html += `<div class="term-header">${escapeHtml(term)}</div>`;
            } else if (line.startsWith('[01]') || line.startsWith('[02]')) {
                html += `<div class="split-line"></div><div class="term-header" style="font-size: 13px;">${escapeHtml(line)}</div>`;
            } else if (line.startsWith('Definition :')) {
                const val = line.replace('Definition :', '').trim();
                html += `<div class="data-block"><span class="block-tag">[DEFINITION]</span><div class="block-body">${escapeHtml(val)}</div></div>`;
            } else if (line.startsWith('Example :')) {
                const val = line.replace('Example :', '').trim();
                html += `<div class="data-block"><span class="block-tag">[EXAMPLE]</span><div class="block-body">${escapeHtml(val)}</div></div>`;
            } else if (line.startsWith('•') || line.startsWith('-')) {
                html += `<div class="block-body" style="color: var(--neon-green); margin-left: 8px; margin-top: 4px;">${escapeHtml(line)}</div>`;
            } else {
                html += `<div class="block-body" style="margin-top: 4px;">${escapeHtml(line)}</div>`;
            }
        });

        return html || escapeHtml(raw);
    }

    function escapeHtml(str) {
        return str.replace(/&/g, '&amp;')
                  .replace(/</g, '&lt;')
                  .replace(/>/g, '&gt;');
    }
});
