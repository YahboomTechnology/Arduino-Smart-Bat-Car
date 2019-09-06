//============================================================================
//  Infrared Remote contorl Experiment
//=============================================================================
#include "./IRremote.h"

//==============================
//Infrared Remote Control
//==============================
int RECV_PIN = 2; // Set Infrared Remote port
IRrecv irrecv(RECV_PIN);
decode_results results; // Store infrared remote decode data
unsigned long last = millis();
int on = 0;//Infrared Received flag

long run_car = 0x00FF18E7;//key 2
long back_car = 0x00FF4AB5;//key 8
long left_car = 0x00FF10EF;//key 4
long right_car = 0x00FF5AA5;//key 6
long stop_car = 0x00FF38C7;//key 5
long left_turn = 0x00ff30CF;//key 1
long right_turn = 0x00FF7A85;//key 3

//==============================
//Set motor port
//============================== 
int Left_motor_back = 9; 
int Left_motor_go = 5; 
int Right_motor_go = 6; 
int Right_motor_back = 10; 
int Right_motor_en = 8; 
int Left_motor_en = 7; 

void setup()
{
  //Initialize motor drive for output mode
  pinMode(Left_motor_go,OUTPUT); 
  pinMode(Left_motor_back,OUTPUT); 
  pinMode(Right_motor_go,OUTPUT);
  pinMode(Right_motor_back,OUTPUT);
  
  pinMode(13, OUTPUT);//Show Infrared Remote Control Received Signal
  irrecv.enableIRIn(); // Start the receiver
}

void run()
{
  digitalWrite(Right_motor_go,HIGH);// right motor go ahead
  digitalWrite(Right_motor_back,LOW);     
  digitalWrite(Left_motor_go,HIGH);// set left motor go ahead
  digitalWrite(Left_motor_back,LOW);
}

void brake() //stop
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
}

void left()//turn left
{
  digitalWrite(Right_motor_go,HIGH);	// right motor go ahead
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);    // left motor stop
  digitalWrite(Left_motor_back,LOW);
}

void spin_left()         //Left rotation
{
  digitalWrite(Right_motor_go,HIGH);	// right motor go ahead
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);    // left motor back off
  digitalWrite(Left_motor_back,HIGH);
}

void right() //turn right
{
  digitalWrite(Right_motor_go,LOW);    // right motor stop
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,HIGH);// left motor go ahead
  digitalWrite(Left_motor_back,LOW);
}

void spin_right()        //Right rotation
{
  digitalWrite(Right_motor_go,LOW);   // right motor back off
  digitalWrite(Right_motor_back,HIGH);
  digitalWrite(Left_motor_go,HIGH);// left motor go ahead
  digitalWrite(Left_motor_back,LOW);
}

void back()  //back off 
{
  digitalWrite(Right_motor_go,LOW);  //right motor back off
  digitalWrite(Right_motor_back,HIGH);
  digitalWrite(Left_motor_go,LOW);  //left motor back off
  digitalWrite(Left_motor_back,HIGH);
}
//==========================================================

void dump(decode_results *results)//Decode Infrared Remote Control Received Signal
{
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) 
  {
    brake();
  } 
}

void loop()
{
  if (irrecv.decode(&results)) //receive infrared signal
  {
    if (millis() - last > 250) //make sure receive signal
    {
      on = !on;//Sign position reversal
      digitalWrite(13, on ? HIGH : LOW);//LED blink
      dump(&results);//decode
    }
    if (results.value == run_car )//key "2"
      run();//go ahead 
    if (results.value == back_car )//key "8"
      back();//back off
    if (results.value == left_car )//key "4"
      left();//turn left
    if (results.value == right_car )//key "6"
      right();//turn right
    if (results.value == stop_car )//key "5"
      brake();//stop
    if (results.value == left_turn )//key "1"
      spin_left();//Left rotation
    if (results.value == right_turn )//key "2"
      spin_right();//Right rotation
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}



