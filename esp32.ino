#include <WiFi.h>
#include <WebServer.h>
#include <HardwareSerial.h>

// ------------------- WiFi 設定 -------------------
const char* ssid = "TP-LINK_FCC0";
const char* password = "aa518215";

WebServer server(80);
bool busy = false;          // 是否有訂單正在執行
String lastOrder = "";

// ------------------- 頁面內容 -------------------
String htmlPage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-TW">
<head>
  <meta charset="UTF-8">
  <title>訂單系統</title>
  <style>
    body { font-family: Arial; background:#f5f5f5; padding:20px; }
    h2 { text-align:center; }
    form { background:white; padding:20px; border-radius:15px; box-shadow:0 0 10px rgba(0,0,0,0.1); max-width:400px; margin:auto; }
    label { display:block; margin:10px 0; }
    input[type=number] { width:80px; }
    button { background:#007bff; color:white; padding:10px 15px; border:none; border-radius:10px; cursor:pointer; }
    button:hover { background:#0056b3; }
    #status { text-align:center; margin-top:20px; font-weight:bold; }
  </style>
</head>
<body>
  <h2>📦 智慧工廠訂單系統</h2>
  <form action="/order" method="GET">
    <label>物品 A 數量: <input type="number" name="A" min="0" max="5" value="0">(訂單數量0~5)</label>
    <label>物品 B 數量: <input type="number" name="B" min="0" max="5" value="0">(訂單數量0~5)</label>
    <label>物品 C 數量: <input type="number" name="C" min="0" max="4" value="0">(訂單數量0~4)</label>
    <label>物品 D 數量: <input type="number" name="D" min="0" max="4" value="0">(訂單數量0~4)</label>
    <button type="submit">送出訂單</button>
  </form>
  <div id="status">狀態：等待中</div>
</body>
</html>
)rawliteral";
  return page;
}

// ------------------- ESP32 初始化 -------------------
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);//RX 16 TX 17

  WiFi.softAP(ssid, password);


  Serial.print("WIFI Connecting");

  Serial.print("WiFi Connected! IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.send(200, "text/html", htmlPage());
  });

  // 處理訂單提交
  server.on("/order", []() {
    if (busy) {
      server.send(200, "text/html; charset=utf-8", "<h3>系統忙碌中，請稍候再試！</h3><a href='/'>返回</a>");
      return;
    }

    int A = server.arg("A").toInt();
    int B = server.arg("B").toInt();
    int C = server.arg("C").toInt();
    int D = server.arg("D").toInt();

    // 檢查是否全部為 0
    if (A==0 && B==0 && C==0 && D==0) {
      server.send(200, "text/html; charset=utf-8", "<h3>請至少選擇一個物品數量！</h3><a href='/'>返回</a>");
      return;
    }

    // 組成訂單字串，例如 "A:2,B:0,C:1,D:3\n"
    lastOrder = String(A) + "," + String(B) + "," + String(C) + "," + String(D);
    Serial2.println(lastOrder);
    busy = true;

    Serial.println("訂單送出: " + lastOrder);
    server.send(200, "text/html; charset=utf-8", "<h3>✅ 訂單已送出！</h3><a href='/'>返回</a>");
  });

  server.begin();
  Serial.println("HTTP 伺服器啟動完成");
}

// ------------------- 主迴圈 -------------------
void loop() {
  server.handleClient();
  
  // 等待 Mega 回覆
  if (Serial2.available()) {
    String reply = Serial2.readStringUntil('\n');
    reply.trim();
    if (reply == "nOK") {
      Serial.print(reply);
      busy = true;
    }
    if (reply == "OK") {
      Serial.print(reply);
      busy = false;
    }
  }
  
}
