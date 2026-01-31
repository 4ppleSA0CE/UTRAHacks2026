//defining color sensor pins to arduino pins
const int s0 = 0;      
const int s1 =1;
const int s2 =3;
const int s3 =2;
const int out =4;

//defining motor pins to arduino pins
const int PIN_LEFT_SPEED = 5;
const int PIN_LEFT_DIR   = 6;
const int PIN_RIGHT_SPEED = 9;
const int PIN_RIGHT_DIR   = 10;



void  setup() 
{
   //for colour sensor
   pinMode(s0,OUTPUT);    
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   //motor
   pinMode(PIN_LEFT_SPEED, OUTPUT);
   pinMode(PIN_LEFT_DIR, OUTPUT);
   pinMode(PIN_RIGHT_SPEED, OUTPUT);
   pinMode(PIN_RIGHT_DIR, OUTPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH);  //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100%  (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and  LOW/HIGH is  2%
   
}

int colourSense()                 
{
   digitalWrite(s0,HIGH);  //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100%  (recommended)
   digitalWrite(s1,HIGH);

   int red; //values from 0-255 representing frequency. the lower the frequency, the more present the colour is
   int blue;
   int green;
   int colour;

   digitalWrite(s2,LOW);        //S2/S3  levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH  is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   red = GetData();                   //Executing GetData function to  get the value

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   blue = GetData();

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   green = GetData();

   if (red <=blue && red<=green){ //if red is the lowest value, then the colour underneath is red 
      colour = 0; //corresponds to red
   }
   else if(green<=blue && green <= red){
      colour = 1; //corresponds to green
   }
   else{
      colour = 2; //corresponds to blue, the least freq is from blue
   }
   return colour;
}

//what the program shold do if it encounters a blue box 
void pickUpBox(){
   //move arm around and stuff to pick up box
   
}
void Green(){
   //follow green line
}

int GetData(){
   int value = pulseIn(out, LOW);  // measure pulse duration
   delay(20);
   return value;                   // send it back
}


