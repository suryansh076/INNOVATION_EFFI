int voltage=A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(voltage,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
   int value=analogRead(voltage);
   float curr_voltage=(value/float(1023))*54;

 Serial.print(value);
  Serial.print("    ");
  int charge_per=map(curr_voltage, 39, 54, 0, 100);
   Serial.print(curr_voltage);
   Serial.print("    ");
   Serial.println(charge_per);
}
