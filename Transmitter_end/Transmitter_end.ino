String command;

#include <SPI.h>
#include  <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte  addresses [][6] = {"00001", "00002"};    //Setting the two addresses. One for  transmitting and one for receiving
struct Type1 
{
  int F;
  int B;
  int R;
  int L;
  int A;
};
Type1 Data1;


struct Type2 
{
  double yaw_angle; 
};
Type2 Data2;

void setup() {
  Serial.begin(9600);
  radio.begin();                            //Starting  the radio communication
  radio.openWritingPipe(addresses[0]);      //Setting  the address at which we will send the data
  radio.openReadingPipe(1, addresses[1]);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);            //You can set it as minimum or maximum depending on the distance between  the transmitter and receiver.
  Serial.println("Type Command (Forward, Backward, Left, Right, Stop)");
}

void loop() 
{
  delay(5);
 if(Serial.available()) {
  command = Serial.readStringUntil("\n");
  command.trim();
  if(command.equals("F"))
  {
    Data1.F = 1;
    Data1.B = 0;
    
    }
   else if (command.equals("B"))
   {
    Data1.F = 0;
    Data1.B = 1;
    
    }

   else if (command.equals("S"))
    {
      Data1.F = 0;
      Data1.B = 0;
      }

   else if (command.equals("R"))
    {
      Data1.R = 1;
      Data1.L = 0;  
      }

   else if(command.equals("L"))
     {
      Data1.L = 1;
      Data1.R = 0;
      } 

   else if (command.equals("C"))
   {
      Data1.L = 0;
      Data1.R = 0;
    }

   else if(command.equals("s"))
   {
    Data1.F = 0;
    Data1.B = 0;
    Data1.L = 0;
    Data1.R = 0;
    }
   else if(command.equals("A")){
        Data1.A = 1;
        Data1.L = 0;
        Data1.R = 0;
    }
 }    
  radio.startListening();                    //This sets the module as receiver
  if (radio.available())                     //Looking for incoming data
  {
    radio.read(&Data2,  sizeof(Type2));
  }
  delay(5);

  Serial.print("Command: ");
  Serial.print(command);
  Serial.print("\t");
  Serial.print("Yaw Angle: ");
  Serial.println(Data2.yaw_angle);
  
  radio.stopListening();                           //This sets the module  as transmitter
  radio.write(&Data1,  sizeof(Type1));   //Sending the data
}
