const canvas = document.getElementById('entropyCanvas');
const ctx = canvas.getContext('2d');
const progressBar = document.querySelector('#progressBar div');
const entropyInput = document.getElementById('entropy');
const generateButton = document.getElementById('generateButton');
let entropyData = [];
let entropyCount = 0;
const maxEntropy = 100;

ctx.fillStyle = '#0d0d0d';
ctx.fillRect(0, 0, canvas.width, canvas.height);
ctx.font = '12px Courier New';
ctx.fillStyle = '#00ffcc';
ctx.fillText('Move mouse here', 10, 50);

canvas.addEventListener('mousemove', (e) => {
    if (entropyCount >= maxEntropy) return;

const rect = canvas.getBoundingClientRect();
const x = e.clientX - rect.left;
const y = e.clientY - rect.top;
const time = Date.now();

entropyData.push(`${x},${y},${time}`);
entropyCount++;

const progress = (entropyCount / maxEntropy) * 100;
progressBar.style.width = `${progress}%`;

ctx.fillStyle = '#ff00cc';
ctx.fillRect(x, y, 2, 2);

    if (entropyCount >= maxEntropy) {
        entropyInput.value = entropyData.join(';');
        generateButton.style.display = 'block';
        ctx.fillStyle = '#0d0d0d';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = '#00ffcc';
        ctx.fillText('Entropy collected!', 10, 50);
    }
});

            // Valorant-style click animation
generateButton.addEventListener('click', () => {
    generateButton.style.transform = 'scale(0.95)';
    setTimeout(() => {
        generateButton.style.transform = 'scale(1)';
    }, 100);
});
