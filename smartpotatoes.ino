//  PARAMETER
const int precess = 1;
const float nbE = 160;
const int proximityDetection = 146;
const int oneFingerDetection = 89;
const int twoFingerDetection = 88;
const int handDetection = 85;
// END PARAMETER
const float freq = 16000000 / nbE;       //Diférentes constantes et variables
const float maxFreq = 16000000; 
const int outPin = 9; 
const int D2 = 2;
const int D3 = 3;
const int D4 = 4;
const int D5 = 5;
int  i,j, maxData;
int average;
int averageE;
float val = 0;
void setFrequency(float frequency)            //Fonction pour modifier la fréquence
{
  if(frequency >=0 || frequency <=16000000){  
    TCCR1A=0b10000010;
    unsigned int v=0;
    int indscale=0;
    float prescale[] = {1.0,8.0,64.0,256.0,1024.0};
    float period=1/frequency;
    while(v==0){
      float curfreq=maxFreq/prescale[indscale];
      float tickperiod=1/curfreq;
      float nbtick=period/tickperiod;
      if(nbtick>65535) {indscale=indscale+1;}
      else {v=nbtick;}}
    int c=prescale[indscale];
     switch (c) {
         case 1: TCCR1B=0b00011001; break;
         case 8: TCCR1B=0b00011010; break;
         case 64: TCCR1B=0b00011011; break;
         case 256: TCCR1B=0b00011100; break;
         case 1024: TCCR1B=0b00011101; break;
         default: TCCR1B=0b00011000;}
    ICR1=v; 
    OCR1A=v/2; 
  }}
void setup() {              //Fonction setup pour initialiser les ports et le fréquence de baud
  Serial.begin(115200);
  pinMode(outPin,OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(D2, OUTPUT);
    digitalWrite(D2, HIGH);
}
void loop() {              // Void loop pour faire une boucle
  average = 0;
  averageE =0;
  for(j=0;j<precess;j++){     // précision sur plusisuers valeur pour éviter les parasites
   for(i=1;i<nbE+1;i++){
      //setFrequency(freq*i);   //Changement de la fréquence sur nbE échelons
      setFrequency(350000);
      val = analogRead(A0);
      if(val > -1){
        averageE = averageE + val;}}
        averageE = averageE / nbE;
    average = average + averageE;}   
  average = average / precess;   // Calcule de la moyenne de plusieurs moyennes d'échantillons
  Serial.println(average); 
   

  if(average <= proximityDetection){
    digitalWrite(D2,HIGH);
  }else{
    digitalWrite(D2,LOW);
  }
  if(average > oneFingerDetection){
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);}
  if((average<= oneFingerDetection )&&(average >twoFingerDetection)){
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);}
  if((average<=twoFingerDetection)&&(average>handDetection)){
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
    digitalWrite(D5, LOW);}
  if(average <= handDetection){
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D5, HIGH);}

  }







