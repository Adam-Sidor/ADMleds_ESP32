#include <WiFi.h>
#include "webConfig.h"

WiFiServer server(80);

short ledMode=0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(10);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  HTTPRecive();
  Serial.println(ledMode);
  delay(100);
}


void HTTPRecive()
{
  WiFiClient client = server.available();
  if (client)
  {
    String currentLine = "";
    bool doonce;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
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
            client.println("                <button onclick=\"window.location.href='ledstatus=001'\">");
            client.println("                    Wlacz");
            client.println("                </button>");
            client.println("                <button onclick=\"window.location.href='ledstatus=000'\">");
            client.println("                    Wylacz");
            client.println("                </button>");
            client.println("            </div>");
            client.println("            <p>Ledy (Biale):</p>");
            client.println("            <div class=\"buttons\">");
            client.println("                <button onclick=\"window.location.href='ledstatus=002'\">");
            client.println("                    Wlacz");
            client.println("                </button>");
            client.println("                <button onclick=\"window.location.href='ledstatus=000'\">");
            client.println("                    Wylacz");
            client.println("                </button>");
            client.println("            </div>");
            client.println("        </div><br>");
            client.println("        <div class=\"panel\">");
            client.println("            <p>Tryb nocny:</p>");
            client.println("            <div class=\"buttons\">");
            client.println("                <button onclick=\"window.location.href='nightmode=001'\">");
            client.println("                    Wlacz");
            client.println("                </button>");
            client.println("                <button onclick=\"window.location.href='nightmode=000'\">");
            client.println("                    Wylacz");
            client.println("                </button>");
            client.println("            </div>");
            client.println("        </div>");
            client.println("    </div>");
            client.println("</body>");
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
        if (currentLine.indexOf("/mode=") != -1)
        {
          ledMode = catchValue("/mode=",currentLine);
          doonce = 0;
        }
      }
    }
    client.stop();
    if (doonce == 0)
    {
      doonce = 1;
    }
  }
}

int catchValue(String valName,String currentLine) {
  String inputValue = "-1";
  int where=currentLine.indexOf(valName);
  if (where != -1) {
    inputValue = currentLine.substring(where+valName.length(), currentLine.length());
  }
  if(inputValue!="")
    return inputValue.toInt();
  else
   return -1;
}