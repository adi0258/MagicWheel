# MagicWheel
🚗 Adventure Steering Wheel
An interactive hardware-software educational game designed to teach Arabic-speaking kindergarteners basic Hebrew words through a simulated driving experience.

🌐 Live Demo: https://magic-wheel-two.vercel.app/

⚙️ System Architecture
Controller (Arduino Uno): Reads the physical steering wheel's potentiometer and transmits navigation commands via RF.

Receiver (Arduino Leonardo): Uses an RF receiver (via VirtualWire) to get commands and acts as a keyboard emulator, translating movements into keystrokes (Left Arrow, Right Arrow, Enter).

Web App (HTML/CSS/JS): A browser-based frontend featuring 4 interactive worlds (Home, Street, Beach, Forest). It uses the native Web Speech API to pronounce the selected Hebrew words.

🚀 Quick Setup
Hardware: Flash the transmitter code to the Uno and the receiver code to the Leonardo. Plug the Leonardo into the computer running the web app via USB.

Safety Pin: Ensure the Leonardo's designated safety pin is connected to GND to enable keyboard emulation.

Software: Open the Live Demo in a modern browser (Google Chrome recommended for optimal Text-to-Speech support), or open your local index.html. No local server is required.

📁 Project Structure
/hardware/uno_transmitter/ - Steering wheel RF transmitter code.

/hardware/leonardo_receiver/ - USB keyboard emulator code.

/web_app/ - Frontend files (index.html, style.css, script.js, and visual assets).
