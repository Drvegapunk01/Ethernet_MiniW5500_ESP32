#include <SPI.h>
#include <Ethernet.h>

#define W5500_RST 5   // Pin RST terhubung ke GPIO5
#define W5500_CS 15    // Pin CS terhubung ke GPIO15

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

EthernetServer server(80);  // Buat server di port 80 (HTTP)





void sendHTMLResponse(EthernetClient &client) {
  // HTTP Header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();  // Baris kosong wajib
  
  // HTML Body
  client.println("<!DOCTYPE html>");
  client.println("<html><head><title>ESP32 Server</title></head>");
  client.println("<body>");
  client.println("<h1>Hello from ESP32!</h1>");
  client.println("<p>IP Address: " + Ethernet.localIP().toString() + "</p>");
  client.println("</body></html>");
}







void setup() {
  pinMode(W5500_RST, OUTPUT);
  digitalWrite(W5500_RST, LOW);   // Reset W5500
  delay(100);
  digitalWrite(W5500_RST, HIGH);  // Lepaskan reset
  delay(1000);

  Ethernet.init(W5500_CS);        // Inisialisasi dengan pin CS
  
  Serial.begin(115200);
  Ethernet.begin(mac);
  
  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());

server.begin();  // Aktifkan server

  
}

void loop() {

  EthernetClient client = server.available();  // Cek koneksi masuk
  
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');  // Baca request
        Serial.println(request);  // Debug: tampilkan request di Serial Monitor
        
        // Kirim response HTTP
        sendHTMLResponse(client);
        break;
      }
    }
    delay(10);  // Beri waktu untuk kirim data
    client.stop();  // Tutup koneksi
  }




}
