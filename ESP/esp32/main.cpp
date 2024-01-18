#include <WiFi.h>

const char* ssid = "your_SSID";
const char* password = "your_password";

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
}

void loop() {
    // Your code here
}
#include <WiFiClient.h>
#include <ArduinoJson.h>

void sendJson(int servo, int motora, int motorb, float wheelaspeed, float wheelbspeed, int usonic, int hsv_h, int hsv_s, int hsv_v, float imu_acc_a, float imu_acc_b, float imu_acc_c, float imu_gyro_x, float imu_gyro_y, float imu_gyro_z, float imu_temp) {
    WiFiClient client;
    
    if (!client.connect("your_server_address", 80)) {
        Serial.println("Connection failed");
        return;
    }
    
    StaticJsonDocument<256> doc;
    
    doc["servo"] = servo;
    doc["motora"] = motora;
    doc["motorb"] = motorb;
    doc["wheelaspeed"] = wheelaspeed;
    doc["wheelbspeed"] = wheelbspeed;
    doc["usonic"] = usonic;
    
    JsonObject hsv = doc.createNestedObject("hsv");
    hsv["h"] = hsv_h;
    hsv["s"] = hsv_s;
    hsv["v"] = hsv_v;
    
    JsonObject imu = doc.createNestedObject("imu");
    
    JsonObject imu_acc = imu.createNestedObject("acc");
    imu_acc["a"] = imu_acc_a;
    imu_acc["b"] = imu_acc_b;
    imu_acc["c"] = imu_acc_c;
    
    JsonObject imu_gyro = imu.createNestedObject("gyro");
    imu_gyro["x"] = imu_gyro_x;
    imu_gyro["y"] = imu_gyro_y;
    imu_gyro["z"] = imu_gyro_z;
    
    imu["temp"] = imu_temp;
    
    String jsonStr;
    serializeJson(doc, jsonStr);
    
    client.println("POST /your_endpoint HTTP/1.1");
    client.println("Host: your_server_address");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(jsonStr.length());
    client.println();
    client.println(jsonStr);
    
    delay(1000);
    
    while (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }
    
    client.stop();
}
