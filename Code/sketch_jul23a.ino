#include <SPI.h>
#include <Ethernet.h>

#define W5500_RST 5   // Pin RST terhubung ke GPIO5
#define W5500_CS 15    // Pin CS terhubung ke GPIO15

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

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
}

void loop() {
  // Kode utama
}
