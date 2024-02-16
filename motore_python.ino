String msg;
int sensor;
char ch;
const byte MOT_SX = 9;
const byte MOT_DX = 10;
const byte MOT_SX2 = 3;
const byte MOT_DX2 = 5;
int pinSensoreLinea = 2;


void setup() {
   Serial.begin(115200);
    pinMode(MOT_SX,OUTPUT);
    pinMode(MOT_DX,OUTPUT);
    pinMode(MOT_SX2,OUTPUT);
    pinMode(MOT_DX2,OUTPUT);
    pinMode(pinSensoreLinea, INPUT);
}

void loop() {
  msg="";
  msg = Serial.readStringUntil('\n'); // Leggi il comando fino al carattere di nuova linea
  int statoSensore = digitalRead(pinSensoreLinea);
  Serial.println(statoSensore);
  if(msg.length() > 0) 
  {
    Serial.println("messaggio " +msg);
    if (msg[2] == '1')
        {sensor = 1;}
    else
      {sensor = 0;}
    Serial.println(sensor);
    if ((sensor == 1 and statoSensore == 0) or (msg[1] == '0'))
    {
        digitalWrite(MOT_SX,LOW);
        digitalWrite(MOT_DX,LOW);
        digitalWrite(MOT_SX2,LOW);
        digitalWrite(MOT_DX2,LOW);
        Serial.println("motori spenti");
    }

    else   //si deve muovere
    {   
        int potenza = 0;
        if (msg[1] == '1')
            {potenza = 100;}
        else if (msg[1] == '2')
           { potenza = 150;}
        else if (msg[1] == '3')
          {potenza = 200;}
        else if (msg[1] == '4')
            {potenza = 220;}
        else
            {potenza = 255;}
        if (msg[0] == '1')  //si muove in avanti
        {
              analogWrite(MOT_SX,potenza);
              analogWrite(MOT_DX,0);
              analogWrite(MOT_SX2,potenza);
              analogWrite(MOT_DX2,0);
              Serial.println("motori avanti");
              
        }
        else  //si muove indietro
        {
            analogWrite(MOT_SX,0);
            analogWrite(MOT_DX,potenza);
            analogWrite(MOT_SX2,0);
            analogWrite(MOT_DX2,potenza);
            Serial.println("motori indietro");
        }
    }

  }
  else
  {
        digitalWrite(MOT_SX,LOW);
        digitalWrite(MOT_DX,LOW);
        digitalWrite(MOT_SX2,LOW);
        digitalWrite(MOT_DX2,LOW);
        Serial.println("motori spenti");
 
  }

 
  

  
}
