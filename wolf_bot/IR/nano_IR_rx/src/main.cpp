#include <Arduino.h>

#include <IRremote.h> // >v4.0.0

#define PIN_RECV 2
#define PIN_LED 7

void setup()
{
  //   Serial.begin(9600);     
  // irrecv.enableIRIn(); 


  Serial.begin(115200);       // initialize serial connection to print on the Serial Monitor of the Arduino IDE
  IrReceiver.begin(PIN_RECV); // Initializes the IR receiver object
  IrReceiver.blink13(true);   // enable blinking of the built-in LED when an IR signal is received
}

void loop()
{

    // if (irrecv.decode(&results))// Returns 0 if no data ready, 1 if data ready.     
  //   {     
  //   int value = results.value;// Results of decoding are stored in result.value     
  //   Serial.println(" ");     
  //   Serial.print("Code: ");     
  //   Serial.println(value, HEX); //prints the value a a button press     
  //   Serial.println(" ");     
  //   irrecv.resume(); // Restart the ISR state machine and Receive the next value     
  //   } 


  if (IrReceiver.decode())
  {
    //uint8_t *data;
    Serial.println("Received something...");
    IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data
    // IrReceiver.printIRResultRawFormatted(&Serial);
    // IrReceiver.printIRResultMinimal(&Serial);
    //IrReceiver.compensateAndStoreIRResultInArray(data); // Compensates the received data and stores it in an array

    //IrReceiver.decodedIRDat;

      digitalWrite(PIN_LED, !digitalRead(PIN_LED));   // Toggle led

//    IRData* data = IrReceiver.read();
//    Serial.print("From arr - Addr: ");
//    Serial.print(data->address, HEX);
//    Serial.print(" | Cmd: ");
//    Serial.println(data->command, HEX);

    // Serial.println();


    IrReceiver.resume(); // Important, enables to receive the next IR signal

    // for (int i = 0; i < size_of_myArray; i++)
    // {
    //   Serial.println(myArray[i]);
    // }

    // IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data
    // IrReceiver.printIRResultMinimal(&Serial); // Prints a minimal summary of the received data
  }
}
