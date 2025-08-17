// Pin definitions
const int trigPin = 2;
const int echoPin = 3;
const int buzzerPin = 12;

// Distance thresholds (in cm)
const int fastBeepDistance = 15;
const int mediumBeepDistance = 25;
const int slowBeepDistance = 40;

// Beep intervals (in milliseconds)
const int fastBeepInterval = 200;
const int mediumBeepInterval = 500;
const int slowBeepInterval = 1000;

unsigned long previousMillis = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long distance = measureDistance();
  int beepInterval = 0;

  if (distance < fastBeepDistance) {
    beepInterval = fastBeepInterval;
  } else if (distance < mediumBeepDistance) {
    beepInterval = mediumBeepInterval;
  } else if (distance < slowBeepDistance) {
    beepInterval = slowBeepInterval;
  } else {
    beepInterval = 0;
  }

  if (beepInterval > 0) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= beepInterval) {
      previousMillis = currentMillis;
      tone(buzzerPin, 1000); // 1kHz tone
      delay(100);
      noTone(buzzerPin);
    }
  }
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}
