//============================================================================
//  Go ahead Experiment
//=============================================================================

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
}

void run(int time) // go ahead 
{

  digitalWrite(Left_motor_en,HIGH);  // set left motor enable
  digitalWrite(Right_motor_en,HIGH);  // set right motor enable
  digitalWrite(Right_motor_go,HIGH);  // right motor go ahead
  digitalWrite(Right_motor_back,LOW); 
  analogWrite(Right_motor_go,200);//PWM--Pulse Width Modulation(0~255). It can be adjusted to control speed.
  digitalWrite(Left_motor_go,HIGH);  // set left motor go ahead
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,200);//PWM--Pulse Width Modulation(0~255).It can be adjusted to control speed.
  delay(time * 100);   //Running time can be adjusted  
}

void loop()
{
    delay(2000); //delay 2s
    run(10);   //Run for 1s
}


