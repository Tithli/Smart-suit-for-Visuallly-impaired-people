#include<ESP8266WiFi.h>
#include<SoftwareSerial.h>

SoftwareSerial es(D1,D2);

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL3JIdR1cam"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "47D_cec92r3EgIeQ7kSXBvphvVA1vzw4"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial



#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] =  "----";// enter your ssid
char pass[] = "----";//enter password

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud

BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  
  
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000); //T_on calculation
while(es.available()){  //arduino data read
String  data =  es.readStringUntil('\n');
data.trim();

int8_t inf =  data.indexOf("F");
int8_t inb =  data.indexOf("B");

String f = data.substring(0,inf);// converting string input to integer
String b = data.substring(inf +1 , inb);

int forward = f.toInt();
int backward = b.toInt();
Serial.print("foreard  ");Serial.print(forward);Serial.print("  backeard  ");Serial.println(backward);
  Blynk.virtualWrite(V3, forward);//distance
  Blynk.virtualWrite(V5,1000/(forward/2+20));//frequency
  Blynk.virtualWrite(V4, backward); 
  Blynk.virtualWrite(V6,1000/(backward/2+20));
}}

void setup()
{
  // Debug console
  Serial.begin(57600);

  es.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);


}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

  
}
