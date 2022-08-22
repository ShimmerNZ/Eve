#include "Arduino.h"
#include <DFMiniMp3.h>


class Mp3Notify
{
public:
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
  {
    if (source & DfMp3_PlaySources_Sd) 
    {
        Serial.print("SD Card, ");
    }
    if (source & DfMp3_PlaySources_Usb) 
    {
        Serial.print("USB Disk, ");
    }
    if (source & DfMp3_PlaySources_Flash) 
    {
        Serial.print("Flash, ");
    }
    Serial.println(action);
  }
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }
  static void OnPlayFinished(DfMp3_PlaySources source, uint16_t track)
  {
    Serial.print("Play finished for #");
    Serial.println(track);  
  }
  static void OnPlaySourceOnline(DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "online");
  }
  static void OnPlaySourceInserted(DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "inserted");
  }
  static void OnPlaySourceRemoved(DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "removed");
  }
};

SoftwareSerial maestroSerial(0, 1);

DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(mySoftwareSerial);
void printDetail(uint8_t type, int value);
MicroMaestro maestro(maestroSerial);

void waitMilliseconds(uint16_t msWait)
{
  uint32_t start = millis();
  
  while ((millis() - start) < msWait)
  {
    // calling mp3.loop() periodically allows for notifications 
    // to be handled without interrupts
    mp3.loop(); 
    delay(1);
  }
}

void setup()
{
  mySoftwareSerial.begin(9600);
  randomSeed(analogRead(2));
  Serial.begin(115200);
  mp3.begin();
  Serial.println();
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  uint16_t volume = mp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
  mp3.setVolume(20);
  
  uint16_t count = mp3.getTotalTrackCount(DfMp3_PlaySource_Sd);
  Serial.print("files ");
  Serial.println(count);
  Serial.println("starting...");
}

void loop()
{
    randomSeed(analogRead(0));
    randNumber = random(5);
    Serial.println(randNumber);
    if (randNumber == 0)
    {
      Serial.println(F("Sequence 1"));
      maestro.restartScript(1);
      mp3.playMp3FolderTrack(1);
      Serial.println("track 1"); 
      delay(5000);
    }
    if (randNumber == 1)
    {
      Serial.println(F("Sequence 2"));
      maestro.restartScript(2);
      delay(100);
      mp3.playMp3FolderTrack(2);
      Serial.println("track 2"); 
      delay(5000);
    }                                                   
    if (randNumber == 2)
    {
      Serial.println(F("Sequence 3"));
      maestro.restartScript(3);
      delay(100);
      mp3.playMp3FolderTrack(3);
      Serial.println("track 3"); 
      delay(5000);
    } 
        if (randNumber == 3)
    {
      Serial.println(F("Sequence 4"));
      maestro.restartScript(4);
      delay(100);
      mp3.playMp3FolderTrack(4);
      Serial.println("track 3"); 
      delay(5000);
    } 
    if (randNumber > 3)
    {
      Serial.println(F("Sequence 5"));
      maestro.restartScript(5);
      delay(100);
      mp3.playMp3FolderTrack(3);
      Serial.println("track 4"); 
      delay(5000);
    }

  }

}                                          
