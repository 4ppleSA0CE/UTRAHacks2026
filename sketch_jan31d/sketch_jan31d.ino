//defining color sensor pins to arduino pins
const int s0 = 0;
const int s1 =1;
const int s2 =3;
const int s3 =2;
const int out =4;
const int BLACK_THRESHOLD = 60;

void  setup() 
{
   //for colour sensor
   pinMode(s0,OUTPUT);
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   //motor
  //  pinMode(PIN_LEFT_SPEED, OUTPUT);
  //  pinMode(PIN_LEFT_DIR, OUTPUT);
  //  pinMode(PIN_RIGHT_SPEED, OUTPUT);
  //  pinMode(PIN_RIGHT_DIR, OUTPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
}

void loop(){
  int a = colourSense();
  delay(1000);
  Serial.println(a);
}

int colour = 0; //store the value of the colour here

int colourSense()
{
   digitalWrite(s0,HIGH);  //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100%  (recommended)
   digitalWrite(s1,HIGH);

   int red; //values from 0-255 representing frequency. the lower the frequency, the more present the colour is
   int blue;
   int green;
   int black;
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

   if(red>= BLACK_THRESHOLD, blue>=BLACK_THRESHOLD, green >=BLACK_THRESHOLD){
      colour = 3; //corresponds to black 
      Serial.println("Black");
   }

   else if(red <=blue && red<=green){ //if red is the lowest value, then the colour underneath is red 
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
int GetData(){
   int value = pulseIn(out, LOW);
   delay(20);
   return value;
}