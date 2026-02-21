#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Harish";
const char* password = "harish0527";

ESP8266WebServer server(80);

// Store HTML in flash memory
const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>SportKing | Intro</title>
<style>
body, html {
    margin: 0; padding: 0;
    width: 100%; height: 100vh;
    background: #000; overflow: hidden;
    display: flex; justify-content: center;
    align-items: center;
    perspective: 1200px;
    font-family: 'Segoe UI', sans-serif;
}
.ball {
    position: absolute;
    width: 140px; height: 140px;
    background: radial-gradient(circle at 30% 30%, #a50000, #5d0000);
    border-radius: 50%;
    z-index: 30;
    box-shadow: inset -10px -10px 30px rgba(0,0,0,0.7),
                0 0 50px rgba(165, 0, 0, 0.5);
    display: flex; justify-content: center; align-items: center;
    animation: userThrow 0.8s ease-in forwards;
}
.ball::after {
    content: "";
    position: absolute;
    top: 50%; left: 0;
    width: 100%; height: 14px;
    background: repeating-linear-gradient(
        90deg, #fff 0px, #fff 4px,
        #a50000 4px, #a50000 8px);
    border-top: 2px solid #400000;
    border-bottom: 2px solid #400000;
    transform: translateY(-50%);
}
.flash {
    position: absolute;
    width: 100%; height: 100%;
    background: #fff;
    z-index: 40;
    opacity: 0;
}
.logo-container {
    font-size: 5.5rem;
    font-weight: 900;
    color: #fff;
    z-index: 10;
    opacity: 0;
    display: flex;
    text-transform: uppercase;
    animation: showLogo 0.5s forwards;
    animation-delay: 1s;
}
.highlight {
    color: #ffd700;
    text-shadow: 0 0 30px rgba(255, 215, 0, 0.8);
}
.expandable {
    display: inline-block;
    overflow: hidden;
    white-space: nowrap;
    width: 0;
    opacity: 0;
    animation: expandText 1.2s forwards ease-in-out;
    animation-delay: 1.8s;
}
@keyframes userThrow {
    0% { transform: translateZ(900px) rotate(0deg) scale(5);
         filter: blur(15px); opacity: 0; }
    80% { transform: translateZ(0) rotate(360deg) scale(1);
          filter: blur(0px); opacity: 1; }
    100% { transform: scale(8); opacity: 0; }
}
@keyframes showLogo { to { opacity: 1; } }
@keyframes expandText { to { width: 220px; opacity: 1; } }
</style>
</head>
<body>

<div class="flash" id="screenFlash"></div>
<div class="ball"></div>
<div class="logo-container">
    <span class="highlight">S</span>
    <span class="expandable">port</span>
    <span class="highlight">King</span>
</div>

<script>
setTimeout(() => {
    document.getElementById('screenFlash')
        .style.animation = "flashImpact 0.3s ease-out forwards";
}, 800);

setTimeout(() => {
    window.location.href = "landing_page.php";
}, 4500);
</script>

</body>
</html>

)=====";

void handleRoot() {
    server.send_P(200, "text/html", MAIN_page);
}

void setup() {
    WiFi.softAP(ssid, password);
    server.on("/", handleRoot);
    server.begin();
}

void loop() {
    server.handleClient();
}