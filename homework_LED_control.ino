#include <SoftwareSerial.h>
#define max_char 12

SoftwareSerial BluetoothSerial( 2, 3 );    
char message[max_char];
char r_char;
byte index=0;
int i;
   

int redPin=9;
int greenPin=10;
int bluePin=11;

int redValue=255;
int greenValue=255;
int blueValue=255;

String redTempValue;
String greenTempValue;
String blueTempValue;

int flag=0;
char currentColor;



void setup() {
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  
  Serial.begin(9600);
  BluetoothSerial.begin( 9600 );

}

char Bluetooth = 0;


void loop() {

  if ( BluetoothSerial.available() )
 {
   Bluetooth = BluetoothSerial.read ();
   Serial.println ( Bluetooth );
/*밝기제어*/
  if (BluetoothSerial.read() == 'a') { 
   int brightness = BluetoothSerial.parseInt();
      analogWrite( redPin, brightness);
       analogWrite( greenPin, brightness);
        analogWrite( bluePin, brightness);
  }
   /*버튼제어*/
   if ( Bluetooth == '1' ){
    digitalWrite ( redPin, HIGH );
    digitalWrite ( greenPin, HIGH );
    digitalWrite ( bluePin, HIGH );
   }
   
   if ( Bluetooth == '0' ){
    digitalWrite ( redPin, LOW );
    digitalWrite ( greenPin, LOW );
    digitalWrite ( bluePin, LOW );
   }
   /*색상제어*/
   char c = BluetoothSerial.read();
    switch (c) {
      case 'r':
        analogWrite( redPin, BluetoothSerial.parseInt());
        break;
      case 'g':
        analogWrite(greenPin, BluetoothSerial.parseInt());
        break;
      case 'b':
        analogWrite(bluePin, BluetoothSerial.parseInt());
        break;
  }

  
  while(Serial.available()>0){
    flag=0;
    if(index<(max_char-1)){
      r_char=Serial.read();
      message[index]=r_char;
    

       if(r_char=='R'){
        currentColor='R';
        redTempValue="";
       }
       else if(r_char=='G'){
        currentColor='G';
        greenTempValue="";
       }
       else if(r_char=='B'){
        currentColor='B';
        blueTempValue="";
        }
    }
    
  if(currentColor=='R'&&r_char!='R'){
    redTempValue += r_char;
  }
  else if(currentColor=='G'&&r_char!='G'){
    greenTempValue += r_char;
  }
  else if(currentColor=='B'&&r_char!='B'){
    blueTempValue += r_char;
  }
  index++;
  message[index]='\0';
    }
  
  if(flag==0){
    analogWrite(redPin,255-redTempValue.toInt());
    analogWrite(greenPin,255-greenTempValue.toInt());
    analogWrite(bluePin,255-blueTempValue.toInt());
  
  Serial.println(message);
  flag=1;
  for(i=0;i<12;i++){
    message[i]='\0';
  }
  index=0;
}
 }
}
