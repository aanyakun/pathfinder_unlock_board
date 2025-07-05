//I customized my firmware by adding a secret 3 2 1 unlock sequence. How it works is if you press buttons 3, then 2, then 1 in order in 5 seconds, LED2 lights up!!

int BUT1 = D0;
int BUT2 = D1;
int BUT3 = D2;

int LED1 = D3;
int LED2 = D4;
int LED3 = D5;

long but1time;
long but2time;
long but3time = 0;

int unlockState = 0;
int unlockStart = 0;

void setup() {
  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
  pinMode(BUT3, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  long startTime = millis();
}

void loop() {
  // Button 3!
  if (digitalRead(BUT3) == HIGH) {
    if (unlockState == 0) {
      unlockState = 1;
      unlockStart = millis();
    }
    but3time++;
  } else {
    but3time = 0;
  }

  // Button 2!
  if (digitalRead(BUT2) == HIGH) {
    but2time = millis();
    if (unlockState == 1 && millis() - unlockStart <= 5000) {
      unlockState = 2;
    } else {
      unlockState = 0;
    }
  }

  // Button 1!
  if (digitalRead(BUT1) == HIGH) {
    but1time = millis();
    digitalWrite(LED1, HIGH);

    if (unlockState == 2 && millis() - unlockStart <= 5000) {
      unlockState = 3;
    } else {
      unlockState = 0;
    }
  } else {
    digitalWrite(LED1, LOW);
  }

  
  if (abs(but2time - but1time) <= 2000 && unlockState == 3) {
    digitalWrite(LED2, HIGH);
  } else {
    digitalWrite(LED2, LOW);
  }

  if (but3time >= 800) {
    digitalWrite(LED3, HIGH);
  } else {
    digitalWrite(LED3, LOW);
  }
}

