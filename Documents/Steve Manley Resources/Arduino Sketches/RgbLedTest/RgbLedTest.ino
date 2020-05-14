int button      = 7;
int red         = 3;
int grn         = 5;
int blu         = 6;
int delayPeriod = 1200;
int i;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as an output.
  pinMode(red,    OUTPUT);     
  pinMode(grn,    OUTPUT);     
  pinMode(blu,    OUTPUT);
  pinMode(button,  INPUT);  
}

// the loop routine runs over and over again forever:
void loop() {

// test full brightness
// -------------------------------------

  while (digitalRead(button)) {}
  // turn on red led and wait a short time
    digitalWrite(red, HIGH);   
    digitalWrite(grn, LOW);   
    digitalWrite(blu, LOW);   
    delay(delayPeriod);
  
  // turn on green led and wait a short time
    digitalWrite(red, LOW);   
    digitalWrite(grn, HIGH);   
    digitalWrite(blu, LOW);   
    delay(delayPeriod);
  
  // turn on blue led and wait a short time
    digitalWrite(red, LOW);   
    digitalWrite(grn, LOW);   
    digitalWrite(blu, HIGH);   
    delay(delayPeriod);
  
  // turn on red, green & blue leds to make white and wait a short time
    digitalWrite(red, HIGH);   
    digitalWrite(grn, HIGH);   
    digitalWrite(blu, HIGH);   
    delay(delayPeriod);
    
  // turn off all leds  
    digitalWrite(red, LOW);   
    digitalWrite(grn, LOW);   
    digitalWrite(blu, LOW);  


// use PCM to sweep led brightnes range up and down
// -------------------------------------

//// set all leds to off
//  digitalWrite(red, LOW);   
//  digitalWrite(grn, LOW);   
//  digitalWrite(blu, LOW);  
//  delay(delayPeriod / 4);
//
//// ramp red up then down with short delay
//  for (i =   0; i < 256; i++){ analogWrite(red, i); delay(5);}
//  delay(delayPeriod);
//  for (i = 255; i >  -1; i--){ analogWrite(red, i); delay(5);}
//  delay(delayPeriod / 4);
//
//// ramp green up then down with short delay
//  for (i =   0; i < 256; i++){ analogWrite(grn, i); delay(5);}
//  delay(delayPeriod);
//  for (i = 255; i >  -1; i--){ analogWrite(grn, i); delay(5);}
//  delay(delayPeriod / 4);
//
//// ramp blue up then down with short delay
//  for (i =   0; i < 256; i++){ analogWrite(blu, i); delay(5);}
//  delay(delayPeriod);
//  for (i = 255; i >  -1; i--){ analogWrite(blu, i); delay(5);}
//  delay(delayPeriod / 4);
//
//// ramp white up then down with short delay
//  for (int i =   0; i < 256; i++){ analogWrite(red, i); analogWrite(grn, i); analogWrite(blu, i); delay(5); }
//  delay(delayPeriod);
//  for (int i = 255; i >  -1; i--){ analogWrite(red, i); analogWrite(grn, i); analogWrite(blu, i); delay(5); }
//  delay(delayPeriod / 4);
}
