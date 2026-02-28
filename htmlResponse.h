#ifndef HTML_RESPONSE_H
#define HTML_RESPONSE_H

#include <WiFiClient.h>

void sendStatusJSON(WiFiClient &client, bool ledStatus, short ledMode, bool isNightModeOn)
{
    String json = "{";
    json += "\"ledStatus\":" + String(ledStatus ? "true" : "false") + ",";
    json += "\"ledMode\":" + String(ledMode) + ",";
    json += "\"isNightModeOn\":" + String(isNightModeOn ? "true" : "false");
    json += "}";

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Access-Control-Allow-Origin: *");
    client.println("Connection: close");
    client.println();
    client.println(json);
}

void sendHTMLResponse(WiFiClient &client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<head>");
    client.println("    <title>");
    client.println("        ADM control");
    client.println("    </title>");
    client.println("</head>");
    client.println("");
    client.println("<style>");
    client.println("    body {");
    client.println("        background-color: rgb(47, 47, 47);");
    client.println("        margin: 0;");
    client.println("    }");
    client.println("");
    client.println("    #top {");
    client.println("        background-image: linear-gradient(#2e5096, rgb(47, 47, 47));");
    client.println("        height: 25%;");
    client.println("        text-align: center;");
    client.println("        display: flex;");
    client.println("        align-items: center;");
    client.println("        justify-content: center;");
    client.println("    }");
    client.println("");
    client.println("    p {");
    client.println("        font-size: 30px;");
    client.println("        color: #d61c1c;");
    client.println("        text-shadow: 2px 2px 3px rgba(0, 0, 0, 0.26);");
    client.println("        font-weight: bold;");
    client.println("        font-family: Arial, Helvetica, sans-serif;");
    client.println("        padding: 10px;");
    client.println("    }");
    client.println("");
    client.println("");
    client.println("    h1,");
    client.println("    h2,");
    client.println("    h3 {");
    client.println("        color: #d61c1c;");
    client.println("        text-shadow: 2px 2px 3px rgba(0, 0, 0, 0.26);");
    client.println("        font-weight: bold;");
    client.println("        font-family: Arial, Helvetica, sans-serif;");
    client.println("    }");
    client.println("");
    client.println("    button {");
    client.println("        background-color: #2e5096;");
    client.println("        border: none;");
    client.println("        border-radius: 5px;");
    client.println("        color: #d61c1c;");
    client.println("        padding: 20px 60px;");
    client.println("        text-align: center;");
    client.println("        display: inline-block;");
    client.println("        font-size: 25px;");
    client.println("        box-shadow: 2px 2px 3px rgba(0, 0, 0, 0.26);");
    client.println("        font-weight: bold;");
    client.println("        margin: 10px;");
    client.println("    }");
    client.println("");
    client.println("    .panel {");
    client.println("        background-color: rgba(32, 32, 32, 0.8);");
    client.println("        border-radius: 10px;");
    client.println("        width: 90%;");
    client.println("        box-shadow: 5px 5px 5px rgba(0, 0, 0, 0.26);");
    client.println("        position: relative;");
    client.println("        margin: auto;");
    client.println("    }");
    client.println("");
    client.println("    .buttons {");
    client.println("        text-align: center;");
    client.println("    }");
    client.println("</style>");
    client.println("");
    client.println("");
    client.println("<body>");
    client.println("    <div id=\"top\">");
    client.println("        <h1>Panel sterowania ADM led online</h1>");
    client.println("    </div>");
    client.println("    <div id=\"content\">");
    client.println("        <div class=\"panel\">");
    client.println("            <p>Ledy (Kolor):</p>");
    client.println("            <div class=\"buttons\">");
    client.println("                <button onclick=\"window.location.href='status=1'\">");
    client.println("                    Wlacz");
    client.println("                </button>");
    client.println("                <button onclick=\"window.location.href='status=0'\">");
    client.println("                    Wylacz");
    client.println("                </button>");
    client.println("            </div>");
    client.println("            <p>Ledy (Biale):</p>");
    client.println("            <div class=\"buttons\">");
    client.println("                <button onclick=\"window.location.href='status=2'\">");
    client.println("                    Wlacz");
    client.println("                </button>");
    client.println("                <button onclick=\"window.location.href='status=0'\">");
    client.println("                    Wylacz");
    client.println("                </button>");
    client.println("            </div>");
    client.println("        </div><br>");
    client.println("        <div class=\"panel\">");
    client.println("            <p>Tryb nocny:</p>");
    client.println("            <div class=\"buttons\">");
    client.println("                <button onclick=\"window.location.href='nightmode=1'\">");
    client.println("                    Wlacz");
    client.println("                </button>");
    client.println("                <button onclick=\"window.location.href='nightmode=0'\">");
    client.println("                    Wylacz");
    client.println("                </button>");
    client.println("            </div>");
    client.println("        </div>");
    client.println("    </div>");
    client.println("</body>");
}

#endif