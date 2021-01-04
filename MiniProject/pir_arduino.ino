#include<SPI.h>
volatile boolean received_data;
volatile uint16_t Slavereceived_data;
void setup()
{
  Serial.begin(9600);
  pinMode(MISO,OUTPUT);                  
  pinMode(10,INPUT);
  digitalWrite(10,LOW);
  SPCR |= _BV(SPE);                      
  received_data = false;
  SPI.attachInterrupt();
  Serial.print("SYSTEM BOOTING>...........");
  delay(2000);
  Serial.print("SYSTEM READY");  
}

ISR(SPI_STC_vect)
{
  Slavereceived_data = SPDR;
  received_data = true;
}
void loop()
{
  if (received_data)
  {
    if (Slavereceived_data!=0)
    {
      received_data=false;
      Serial.println("Motion Detected");
      delay(200);
    }
    else
    {   
            received_data=false;
            Serial.println("No Motion");
            delay(200);

    }
  }
}
