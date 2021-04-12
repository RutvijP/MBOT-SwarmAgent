#include <IRremote.h>
#define ir  8           
#define bittm   562 
 long int ack           =0b00000000000000000000000000001000;

int RECV_PIN = 4;    //  dig pin 4 for rx1
                     //  dig pin 5 for rx4
                                        
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
      delayMicroseconds(3 * bittm); 
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

//////////////////////////////////////////////////// void loop///////////////////////////////////////////////

long int  setupi=0,setupi1=0,pvalue=0,ans, decision=0 ,delayloop=0,sendack=0,sendno=0,sendno1=0;

void loop() 
{ 
 //////////////////////////////////////////////////////////////////

 if ((setupi==0))
    {  irrecv.enableIRIn();          ///////////////// this part causes probem
       Serial.println("setup receiving");
       setupi=1; 
       delay(100);
          
    }  
        if ( irrecv.decode(&results) )
      {
         Serial.println(results.value,BIN);
         if (results.value==0b100)
         {ans=12;}
         else {ans=9;}
        irrecv.enableIRIn();
       }
  //delay(200);
 
  if (ans==12)
  //////////////////////////////////////////////////////
  { Serial.println("tx bit verified");
   cli();
    for(sendno=0;sendno<10;sendno++)
   { 
      if(sendno==0)
        { Serial.println("sending ack...");
         irsetup();
         sendno=1;
         }               
         irsendcode(ack);
         delay(200);
   cli();
   delay(200);
         Serial.println("ack sent");
        delay(20000); 
      }
      ans=2;        
         
  }
if (ans==2)
{delay(200);
  Serial.println("starting");
  delay(200);
   cli();
   delay(200);
  while(1)
{delay(4000);
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
//else Serial.println("if loopp is off");
}


/* digitalWrite(10,HIGH);
     digitalWrite(A1,HIGH);
       digitalWrite(A0,LOW);

     digitalWrite(9,HIGH);
     digitalWrite(A2,HIGH);
     digitalWrite(A3,LOW);
    */


     /*digitalWrite(10,LOW);
     digitalWrite(9,LOW);
 */
