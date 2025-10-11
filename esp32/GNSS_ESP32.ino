#include <WiFi.h>

const char* ssid     = "OLAX-4G-959A";
const char* password = "48668917";

HardwareSerial MySerial(2);  // UART2: GPIO17(TX2), GPIO16(RX2)
WiFiServer server(80);       // HTTP Server (湲곗〈 ?좎?)

// === TCP ?대씪?댁뼵?몄슜 ===
const char* tcpServerIP   = "183.101.110.160";  // KT 怨듭쑀湲?怨듭씤 IP
const uint16_t tcpServerPort = 6000;            // ?ы듃?ъ썙?⑸맂 ?ы듃
WiFiClient   tcpClient;

void setup() {
  Serial.begin(115200);
  MySerial.begin(115200, SERIAL_8N1, 16, 17);

  Serial.println("Connect try: " + String(ssid));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   
    Serial.print(".");
  }

  Serial.println("\nWIFI connected, IP: " + WiFi.localIP().toString());
  server.begin();

  // KT 怨듭쑀湲??쒕쾭??TCP ?곌껐 ?쒕룄
  while (!tcpClient.connect(tcpServerIP, tcpServerPort)) {
    Serial.println("Trying to connect to KT Server...");
    delay(2000);
  }
  Serial.println("Connected to KT TCP server!");
}

void loop() {
  // ??????????????
  // [Serial2 Loopback Echo]
  // ??????????????
  // MySerial(TX2?뭃X2 ?먰띁)濡??ㅼ뼱?ㅻ뒗 臾몄옄 ?쎌뼱??  // USB ?쒕━?쇰줈 異쒕젰
  if (MySerial.available()) {
    char c = MySerial.read();
    Serial.print("Loopback received on Serial2: ");
    Serial.println(c);
  }

  // === [1] TCP ?쒕쾭?먯꽌 紐낅졊 ?섏떊 ===
  if (tcpClient.connected() && tcpClient.available()) {
    String cmd = tcpClient.readStringUntil('\n');
    cmd.trim();
    Serial.println("[TCP ?섏떊 紐낅졊]: " + cmd);

    if (cmd.length() == 1) {
      char c = cmd.charAt(0);
      MySerial.write(c);
      Serial.print("[UART ?≪떊 ??Serial2]: ");
      Serial.println(c);
    }
  } else if (!tcpClient.connected()) {
    Serial.println("[TCP ?곌껐 ?딄?] ?ъ뿰寃??쒕룄 以?..");
    tcpClient.connect(tcpServerIP, tcpServerPort);
    delay(2000);
  }

  // === [2] HTTP ?붿껌 泥섎━ (湲곗〈 肄붾뱶 ?좎?) ===
  WiFiClient client = server.available();
  if (!client) return;

  Serial.println("\n[?대씪?댁뼵???묒냽??");
  client.setTimeout(5000);

  String requestLine = "";
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    line.trim();
    if (line.startsWith("GET")) {
      requestLine = line;
      break;
    }
    if (line.length() == 0) break;
  }
  Serial.println("Request line: " + requestLine);

  String command = "";
  int start = requestLine.indexOf("GET /") + 5;
  int end   = requestLine.indexOf(" ", start);
  if (start > 4 && end > start) {
    command = requestLine.substring(start, end);
  }

  char txChar = '\0';
  if (command.length() == 1) {
    switch (command.charAt(0)) {
      case 'f': txChar = 'F'; break;
      case 'b': txChar = 'B'; break;
      case 'l': txChar = 'L'; break;
      case 'r': txChar = 'R'; break;
      case 's': txChar = 'S'; break;
      case 'e': txChar = 'E'; break;
      case 'c': txChar = 'C'; break;
      case 'w': txChar = 'W'; break;
      case 'a': txChar = 'A'; break;
      case 'd': txChar = 'D'; break;
      case 'g': txChar = 'G'; break;
      case 'h': txChar = 'H'; break;
      case 'i': txChar = 'I'; break;
      case 'j': txChar = 'J'; break;
      case 'k': txChar = 'K'; break;
      case 'm': txChar = 'M'; break;
      case 'n': txChar = 'N'; break;
      case 'o': txChar = 'O'; break;
      case 'p': txChar = 'P'; break;
      case 'q': txChar = 'Q'; break;
      case 't': txChar = 'T'; break;
    }
  }

  if (txChar != '\0') {
    MySerial.write(txChar);
    Serial.print("[UART ?≪떊 ??Serial2]: ");
    Serial.println(txChar);
  } else {
    Serial.println("?????녿뒗 紐낅졊: " + command);
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println();
  client.println("Command received: " + command);
  client.stop();

  Serial.println("[?대씪?댁뼵???곌껐 醫낅즺]");
}


