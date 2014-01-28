#define GPRMC_TERM "$GPRMS,"

char nmeaSentence[68];

void setup()
{
  Serial.begin(115200);
  //ss.begin(4800);
  Serial2.begin(9600);
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial2.available())
    {
      char c = Serial2.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      switch(c)
      {
        //case '\r': //do nothing
        //case '\n': //do nothing
        case '$':
          Serial2.readBytesUntil(0x2A, nmeaSentence, 67);
          Serial.println(nmeaSentence);
      }
    }
  }
}

// Turn char[] array into String object
String charToString(char *c)
{

 String val = "";

 for(int i = 0; i <= sizeof(c); i++) 
 {
   val = val + c[i];
 }
 
return val;
}

//Parse GPRMC NMEA sentence data from String
//String must be GPRMC or no data will be parsed
String parseGprmcLon(String s)
{
  int delimCntr = 0; //count number or delimiters
  int pLoc = 0; //paramater location pointer
  int pEndLoc = 0; //parameter end location
  String lon;
  if(s.substring(0,4) == 'GPRMC')
  {
    for(int i = 0; i < 3; i++)
    {
      if(delimCntr < 2) 
      {
        pLoc = s.indexOf(',', pLoc+1);
      }
      else
      {
        pEndLoc = s.indexOf(',', pLoc+1);
        lon = s.substring(pLoc+1, pEndLoc);
      }
      return lon;
    }
      
  }
}
