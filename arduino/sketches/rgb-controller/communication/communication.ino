
void setup()
{
  Serial.begin(9600);
}

String incomingString;
int incomingByte;

void loop()
{
  if (Serial.available() > 0)
  {
    incomingString = Serial.readString();
    if (incomingString.length() > 0) incomingString.remove(incomingString.length() - 1);
    if (incomingString.length() > 0) incomingString.remove(incomingString.length() - 1);

    Serial.flush();
    
    if (incomingString == "A")
    {
      Serial.println("WOW");
    }

    if (incomingString == "PING")
    {
      Serial.println("PONG");
    }

    else
      Serial.println(incomingString);
  }
}



void pingHandler ()
{
  Serial.println("PING");
}
