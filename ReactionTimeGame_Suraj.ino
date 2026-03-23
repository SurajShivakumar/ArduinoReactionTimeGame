
int buttonPin = 7;
int redPin = 11;
int yellowPin = 9;
int greenPin = 4;
int whitePin = 2;

int test = 0;
long pause = 0;
unsigned long timer;

int values[3];
int index = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(whitePin, OUTPUT);

  Serial.begin(115200);

  Serial.println("\nWelcome to the reaction time game! Please click the button 3 times to start.");
  delay(1000);
}

void playOnce() {
//Code for playing the game once
  digitalWrite(greenPin, LOW);
  digitalWrite (yellowPin, LOW);

  //Red LED Code
  digitalWrite(redPin, HIGH);
  unsigned long startTime = millis();

  // Check if the button is pressed during red
  while (millis() - startTime < 2000) {
    if (millis() - startTime > 100) {
      if (digitalRead(buttonPin) == HIGH) {
        Serial.println("You clicked too early! Wait until the green LED lights up.");
        delay(2000);
        return;
      }
    }
  }
  
  //Yellow LED code
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  startTime = millis();
  pause = random(3, 6) * 1000;

  // Check if the button is pressed during yellow
  while (millis() - startTime < pause) {
    if (digitalRead(buttonPin) == HIGH) {
      Serial.println("You clicked too early! Wait until the green LED lights up.");
      delay(2000);
      return;
    }
  }

  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  timer = millis();

  while (digitalRead(buttonPin) == LOW) {
    // Wait for button press during green
  }

  unsigned long reactionTime = millis() - timer;
  delay(100);
  Serial.println("Reaction Time: " + String(reactionTime) + " ms");

  if (index < 3) {
    values[index] = reactionTime;  // Store the reaction time
    index++;
    if (index == 1) {
      Serial.println("Play two more times for a more accurate value.");
    }
  }

  //Waits until I let go of the button before continuing
  while (digitalRead(buttonPin) == HIGH);

  // Turn off all LEDs
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
}

void loop() {
  //Serial.println(String(test));
  // put your main code here, to run repeatedly:
  if (digitalRead(buttonPin) == HIGH) { //This if block works as a test to make sure the LEDs and button are working.
    if (test == 0 || test == 1 || test == 2) {
      digitalWrite(whitePin, HIGH);
      test += 1;
      Serial.print(String(test) + "... ");
      while (digitalRead(buttonPin) == HIGH);
      digitalWrite(whitePin, LOW);
    }
  }
      
  if (test == 3) {
    test = -10000; //Just makes sure that test will never hit 0 again.
    digitalWrite(whitePin, LOW);

    Serial.println("When the green LED lights up, press the button as fast as you can!");
    delay(2000);

    while (index < 3) {
      playOnce();
    }

    int avg = (values[0] + values[1] + values[2]) / 3;
    Serial.println("Your average reaction time is " + String(avg) + " ms. ");

    if (avg < 150) {
      Serial.print("Elite reflexes! 🔥");
    } else if (avg < 200) {
      Serial.print("Excellent reaction! ⚡");
    } else if (avg < 250) {
      Serial.print("Solid average 👍");
    } else if (avg < 300) {
      Serial.print("A bit slow — try again 🐢");
    } else if (avg < 400) {
      Serial.print("Pretty slow 😴");
    } else {
      Serial.print("Were you even paying attention? 🪦");
    }
  }
}