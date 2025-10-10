#include <WiFi.h>

const char* ssid     = "OLAX-4G-959A";
const char* password = "48668917";

HardwareSerial MySerial(2);  // UART2: GPIO17(TX2), GPIO16(RX2)
WiFiServer server(80);       // HTTP Server (기존 유지)

// === TCP 클라이언트용 ===
const char* tcpServerIP   = "183.101.110.160";  // KT 공유기 공인 IP
const uint16_t tcpServerPort = 6000;            // 포트포워딩된 포트
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

  // KT 공유기 서버에 TCP 연결 시도
  while (!tcpClient.connect(tcpServerIP, tcpServerPort)) {
    Serial.println("Trying to connect to KT Server...");
    delay(2000);
  }
  Serial.println("Connected to KT TCP server!");
}

void loop() {
  // ──────────────
  // [Serial2 Loopback Echo]
  // ──────────────
  // MySerial(TX2→RX2 점퍼)로 들어오는 문자 읽어서
  // USB 시리얼로 출력
  if (MySerial.available()) {
    char c = MySerial.read();
    Serial.print("Loopback received on Serial2: ");
    Serial.println(c);
  }

  // === [1] TCP 서버에서 명령 수신 ===
  if (tcpClient.connected() && tcpClient.available()) {
    String cmd = tcpClient.readStringUntil('\n');
    cmd.trim();
    Serial.println("[TCP 수신 명령]: " + cmd);

    if (cmd.length() == 1) {
      char c = cmd.charAt(0);
      MySerial.write(c);
      Serial.print("[UART 송신 → Serial2]: ");
      Serial.println(c);
    }
  } else if (!tcpClient.connected()) {
    Serial.println("[TCP 연결 끊김] 재연결 시도 중...");
    tcpClient.connect(tcpServerIP, tcpServerPort);
    delay(2000);
  }

  // === [2] HTTP 요청 처리 (기존 코드 유지) ===
  WiFiClient client = server.available();
  if (!client) return;

  Serial.println("\n[클라이언트 접속됨]");
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
    Serial.print("[UART 송신 → Serial2]: ");
    Serial.println(txChar);
  } else {
    Serial.println("알 수 없는 명령: " + command);
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println();
  client.println("Command received: " + command);
  client.stop();

  Serial.println("[클라이언트 연결 종료]");
}
