
char mac_get_deveui[] = "mac get deveui \r\n";
uint8_t rx_buffer_data[50];

String incoming_byte;  

void setup() {
  Serial1.begin(57600, SERIAL_8N1);
  Serial.begin(57600); 

  while(incoming_byte != "accepted\r\n") {
  Serial.print("sys reset\r\n");
  Serial1.print("sys reset\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }
     //delay(100);
     
  Serial.print("mac get deveui\r\n");
  Serial1.print("mac get deveui\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  Serial.print("mac set appeui 00250C0000010001\r\n");
  Serial1.print("mac set appeui 00250C0000010001\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  Serial.print("mac set appkey E343A7D5F8FA3F1241607C432D9D4457\r\n");
  Serial1.print("mac set appkey E343A7D5F8FA3F1241607C432D9D4457\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 

  Serial.print("mac set pwridx 10\r\n");
  Serial1.print("mac set pwridx 10\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 

  Serial.print("mac save\r\n");
  Serial1.print("mac save\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  Serial.print("sys reset\r\n");
  Serial1.print("sys reset\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 

  Serial.print("mac join otaa\r\n");
  Serial1.print("mac join otaa\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 

  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
     //delay(1000);      
}
  Serial.print("mac tx cnf 4 5A5B5B\r\n");
  Serial1.print("mac tx cnf 4 5A5B5B\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }
}
bool ryanDebug = true;


void loop() {


  
}
