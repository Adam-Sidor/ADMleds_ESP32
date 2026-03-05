#ifndef HTML_RESPONSE_H
#define HTML_RESPONSE_H

#include "GlobalConfig.h"

String getStatusJSON(DeviceConfig &config) {
    String json = "{";
    json += "\"ledStatus\":" + String(config.ledStatus ? "true" : "false") + ",";
    json += "\"ledMode\":" + String(config.ledMode) + ",";
    json += "\"isNightModeOn\":" + String(config.isNightModeOn ? "true" : "false");
    json += "}";
    return json;
}

String getHTMLResponse() {
    String html = R"rawtext(
<!DOCTYPE html>
<html>
<head>
    <title>ADM control</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { background-color: rgb(47, 47, 47); margin: 0; font-family: Arial, sans-serif; }
        #top { background-image: linear-gradient(#2e5096, rgb(47, 47, 47)); height: 20vh; text-align: center; display: flex; align-items: center; justify-content: center; }
        p { font-size: 24px; color: #d61c1c; text-shadow: 2px 2px 3px rgba(0,0,0,0.26); font-weight: bold; padding: 10px; }
        h1 { color: #d61c1c; text-shadow: 2px 2px 3px rgba(0,0,0,0.26); margin: 0; }
        button { background-color: #2e5096; border: none; border-radius: 5px; color: #d61c1c; padding: 15px 40px; font-size: 20px; box-shadow: 2px 2px 3px rgba(0,0,0,0.26); font-weight: bold; margin: 10px; cursor: pointer; width: 80%; max-width: 300px; }
        .panel { background-color: rgba(32, 32, 32, 0.8); border-radius: 10px; width: 90%; margin: 20px auto; text-align: center; padding: 10px; box-shadow: 5px 5px 5px rgba(0,0,0,0.26); }
    </style>
</head>
<body>
    <div id="top"><h1>Panel sterowania ADM</h1></div>
    <div class="panel">
        <p>Zasilanie (Kolor):</p>
        <button onclick="fetch('/set?status=1')">Wlacz</button>
        <button onclick="fetch('/set?status=0')">Wylacz</button>
        <p>Zasilanie (Biale):</p>
        <button onclick="fetch('/set?status=2')">Wlacz</button>
        <button onclick="fetch('/set?status=0')">Wylacz</button>
        <p>Tryb nocny:</p>
        <button onclick="fetch('/set?nightmode=1')">Wlacz</button>
        <button onclick="fetch('/set?nightmode=0')">Wylacz</button>
    </div>
</body>
</html>
)rawtext";
    return html;
}

#endif