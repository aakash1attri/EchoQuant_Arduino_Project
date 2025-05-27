int count = 0;
int echoPin = 3;
int trigPin = 4;
int echoPin2 = 6;
int trigPin2 = 7;

void setup(){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
  pinMode(12,OUTPUT);
}
  
void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long dis = duration * 0.034 / 2;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  long duration2 = pulseIn(echoPin2, HIGH);
  long dis2 = duration2 * 0.034 / 2;

    
  
  if (dis < 10){
    count += 1;
    if (count <= 0){
    digitalWrite(12,LOW);
    }  
    else {
    digitalWrite(12,HIGH);
    }
    delay(2000);
  }  
  if ( dis2 < 10){
    count = count - 1 ;
    if (count <= 0){
    digitalWrite(12,LOW);
    }  
    else {
    digitalWrite(12,HIGH);
    }
    delay(2000);  
  }

}