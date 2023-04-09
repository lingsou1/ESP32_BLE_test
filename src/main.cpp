/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */

#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

#define z 16 
#define y 17 
#define x 18 


void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  pinMode(x,INPUT);
  pinMode(y,INPUT);
  pinMode(z,INPUT);
  Serial.print("sensor config is OK!!!\n");
}

void loop(){
  int x_value = analogRead(x);
  int y_value = analogRead(y);
  int z_value = analogRead(z);

  Serial.print("x_value is :   ");
  Serial.print(x_value);
  Serial.print("\n");
  Serial.print("y_value is :   ");
  Serial.print(y_value);
  Serial.print("\n");
  Serial.print("z_value is :   ");
  Serial.print(z_value);
  Serial.print("\n");

  delay(20);
  Serial.print("\n\n\n");


  bool mediaStatus = true;
  if(bleKeyboard.isConnected()) {
    if(x_value == 0){//音量减
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      delay(20);
    }
    else if (x_value > 4000 and y_value > 4000 and z_value > 4000){//音量加
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      delay(20);
    }
    // else if(){//下一曲
    //   bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
    // }
    else if(y_value == 0){//上一曲
      bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
      delay(20);

    }
    else if(z_value == 0 ){//控制暂停或开启
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      delay(200);
      bleKeyboard.releaseAll();
    }


  // //使用蓝牙输出字符串
  // Serial.println("Sending 'Hello world'...");
  // bleKeyboard.print("Hello world");

  // delay(1000);

  // Serial.println("Sending Enter key...");
  // bleKeyboard.write(KEY_RETURN);

  // delay(1000);

  // Serial.println("Sending Play/Pause media key...");
  // bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

  // delay(1000);

   
   // Below is an example of pressing multiple keyboard modifiers 
   // which by default is commented out.
    /*
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    delay(100);
    bleKeyboard.releaseAll();
    */
   
  }

  // Serial.println("Waiting 5 seconds...");
  // delay(5000);
}