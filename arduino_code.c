#include <Keypad.h>
#include <SoftwareSerial.h>

char * password = "2210"; // To increase the passcode length change the numerical to the size after position

#define rxPin 8
#define txPin 9
SoftwareSerial sim800(rxPin,txPin);

int position = 0;

const byte ROWS = 4; // 4 rows
const byte COLS = 3; // 4 columns

char keys[ROWS][COLS] =
{
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
}; //mapping of the keys done w.r.t to the grid keypad

byte rowPins[ROWS] = { 6, 5, 4, 3 }; //connection of rows pins to the Arduino
byte colPins[COLS] = { 2, 1, 0 }; // connection of the columns pins to the Arduino

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int Lock = 10; // Connecting the relay to the 5th pin

void setup()
{

pinMode(Lock, OUTPUT);
LockedPosition(true);
}

void loop()
{
  char key = keypad.getKey();
  
  if (key == '*' || key == '#') //OR operator used to lock the device back again
  {
    position = 0;
    LockedPosition(true);
  }
  if (key == password[position])
  {
    position ++;
  }
  if (position == 4) // change this if you want to increase the password length
  {
    LockedPosition(false);
  }else if (key != NO_KEY) {
    sendSMSAlert();
  }
  delay(100);   
}
void LockedPosition(int locked)
{
  if (locked)
  {
    digitalWrite(Lock, LOW);
  }
  else
  {
    digitalWrite(Lock, HIGH);
  }
}

void sendSMSAlert() {
  // Replace with the phone number you want to send the alert to
  char phoneNumber[] = "+919503334639";

  // The message to be sent
  char message[] = "Unaurthoried Entry!";

}
