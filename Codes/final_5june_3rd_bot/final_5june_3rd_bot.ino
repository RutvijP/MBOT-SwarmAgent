

void setup()
{
 Serial.begin(9600); 
  pinMode(A0, OUTPUT);
 pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(A3, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////


int n,txno=0, setupi1=0,recvno=0,recven=0,recvno1=0,recvno2=0,delayloop=0; 
void loop()
{  ////////////////////////////////////////SEND TX BIT////////////////////////////

  while(1)

   {
    //delay(4000);
    //for(delayloop=0;delayloop<40;delayloop++)
     {Serial.println("motor on");
     digitalWrite(10,HIGH);
     digitalWrite(A1,HIGH);
       digitalWrite(A0,LOW);

     digitalWrite(9,HIGH);
     digitalWrite(A2,HIGH);
     digitalWrite(A3,LOW);
     delay(2000);
     }

     //for(delayloop=0;delayloop<40;delayloop++)
     {
     Serial.println("motor off");
    
    digitalWrite(10,LOW);
     digitalWrite(9,LOW);
    delay(2000);
    //delay(2000);
     }
  }
  }                                             //////// end of void loop

