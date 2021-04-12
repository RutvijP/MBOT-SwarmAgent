#include <IRremote.h>


#define ir  8            
#define bittm   560//////// instead of 562 
long int transmit         =0b00000000000000000000000000000100;

int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;


void irsetup(void)
{
  pinMode(ir, OUTPUT);
  digitalWrite(ir, LOW);    
}

void ircarrier(unsigned int irtimemicro)
{
  for(int i=0; i < (irtimemicro / 26); i++)
    {
    digitalWrite(ir, HIGH);   
    delayMicroseconds(9);          
    digitalWrite(ir, LOW);    
    delayMicroseconds(9);          
    }
}
void irsendcode(unsigned long code)
{
  
  ircarrier(9000);            
  delayMicroseconds(4500);    
  
  for (int i=0; i<32; i++)            
    {
    ircarrier(bittm);               
    if (code & 0x80000000)            
      delayMicroseconds(3 * bittm);  ////// instead of 3
    else
      delayMicroseconds(bittm);     
     code<<=1;                        
    
    }
  ircarrier(bittm);               
  
}



//////////////////////////////////////////////////////////////////////////////////////////////////////


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

//////////////////////

 Serial.println("in setup loop 0");
  if (setupi1==0)
  { irsetup();
   Serial.println("in setup loop");
       
    for (txno=0;txno<1;txno++)
      { irsendcode(transmit);
       Serial.println(transmit,BIN); 
       delay(150);
       }
   setupi1=1;
 }  
   /////////////////// RECEIVE AND CHECK ACK /////////////////////////////////////////////////        

   while(recvno2==0)

  { if (recven==0)
    {
    irrecv.enableIRIn();
    Serial.println("recven");
    recven=1; 
    }
    
    //for(n=0;n<100;n++)
    while(recvno==0)
    {
   if ( irrecv.decode(&results) )
    {
     Serial.println(results.value,BIN);
     if(results.value==0b1000)
     {Serial.println("acknowledgement received");
      recvno=1;
      }
      else{Serial.println("acknowledgement not received");}
     irrecv.enableIRIn();
     }
     }
  recvno2=1;
  }
  if (recvno2==1)
  {
    while(1)

   {
    delay(4000);
    for(delayloop=0;delayloop<40;delayloop++)
     {Serial.println("motor on");
     digitalWrite(10,HIGH);
     digitalWrite(A1,HIGH);
       digitalWrite(A0,LOW);

     digitalWrite(9,HIGH);
     digitalWrite(A2,HIGH);
     digitalWrite(A3,LOW);
     delay(4000);
     }

     for(delayloop=0;delayloop<40;delayloop++)
     {
     Serial.println("motor off");
    
    digitalWrite(10,LOW);
     digitalWrite(9,LOW);
    delay(4000);
    //delay(2000);
     }
  }
  }



  }                                             //////// end of void loop

