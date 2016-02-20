#include <Wire.h>

//machine variables
int lamp[] = {
  10, 9, 8, 7, 6, 5, 4, 3, 2
};
int lanode[] = {
  11, 12, 13
};


char firstRow[] = {
  'P', 'Y', 'X', 'C', 'V', 'B', 'N', 'M', 'L'
};
char secondRow[] = {
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K'
};
char thirdRow[] = {
  'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O'
};

char lastPressed = '?';

boolean stepThirdNextTurn = false;


//encoding variables
char rotorOneDefault[] = {
  'L', 'P', 'G', 'S', 'Z', 'M', 'H', 'A', 'E', 'O', 'Q', 'K', 'V', 'X', 'R', 'F', 'Y', 'B', 'U', 'T', 'N', 'I', 'C', 'J', 'D', 'W'
};
char rotorTwoDefault[] = {
  'S', 'L', 'V', 'G', 'B', 'T', 'F', 'X', 'J', 'Q', 'O', 'H', 'E', 'W', 'I', 'R', 'Z', 'Y', 'A', 'M', 'K', 'P', 'C', 'N', 'D', 'U'
};
char rotorThreeDefault[] = {
  'C', 'J', 'G', 'D', 'P', 'S', 'H', 'K', 'T', 'U', 'R', 'A', 'W', 'Z', 'X', 'F', 'M', 'Y', 'N', 'Q', 'O', 'B', 'V', 'L', 'I', 'E'
};

char rotorOne[] = {
  'L', 'P', 'G', 'S', 'Z', 'M', 'H', 'A', 'E', 'O', 'Q', 'K', 'V', 'X', 'R', 'F', 'Y', 'B', 'U', 'T', 'N', 'I', 'C', 'J', 'D', 'W'
};
char rotorTwo[] = {
  'S', 'L', 'V', 'G', 'B', 'T', 'F', 'X', 'J', 'Q', 'O', 'H', 'E', 'W', 'I', 'R', 'Z', 'Y', 'A', 'M', 'K', 'P', 'C', 'N', 'D', 'U'
};
char rotorThree[] = {
  'C', 'J', 'G', 'D', 'P', 'S', 'H', 'K', 'T', 'U', 'R', 'A', 'W', 'Z', 'X', 'F', 'M', 'Y', 'N', 'Q', 'O', 'B', 'V', 'L', 'I', 'E'
};
char reflector[] = {
  'I', 'M', 'E', 'T', 'C', 'G', 'F', 'R', 'A', 'Y', 'S', 'Q', 'B', 'Z', 'X', 'W', 'L', 'H', 'K', 'D', 'V', 'U', 'P', 'O', 'J', 'N'
};

char entryWheel[] = {
  'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'P', 'Y', 'X', 'C', 'V', 'B', 'N', 'M', 'L'
};

char alphabet[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

int ringOne = 1;
int ringTwo = 1;
int ringThree = 1;

char rotorOnePlace = 'A';
char rotorTwoPlace = 'A';
char rotorThreePlace = 'A';

char turnoverOne = 'Y';
char turnoverTwo = 'E';
char turnoverThree = 'N';

//main functions
void setup() {
  Serial.begin(9600);

  Wire.begin(8);
  for (int i = 1; i < ringOne; i++) {
    ringTurnRotor(rotorOne);
  }
  for (int i = 1; i < ringTwo; i++) {
    ringTurnRotor(rotorTwo);
  }
  for (int i = 1; i < ringThree; i++) {
    ringTurnRotor(rotorThree);
  }
  for (int index = 0 ; index <= 8; index++) {
    pinMode (lamp[index], OUTPUT);
    digitalWrite (lamp[index], 1);
  }
  openingSequence();
}

void loop() {
  char pressed = readKey();
  //char pressed = Serial.read();
  if (pressed == '?') {
    lampOff();
  }
  else if (pressed != lastPressed) {
    writeLamp(rotorEncodeAll(pressed));
    incrementRotors();

    Wire.beginTransmission(8);

    Wire.write(rotorThreePlace);
    Wire.write(rotorTwoPlace);
    Wire.write(rotorOnePlace);
    Wire.endTransmission();
  }
  lastPressed = pressed;
  Serial.println(pressed);
  delay(20);
  if (reset()) {
    rotorThreePlace = 'A';
    rotorTwoPlace = 'A';
    rotorOnePlace = 'A';
    Wire.beginTransmission(8);
    Wire.write(rotorThreePlace);
    Wire.write(rotorTwoPlace);
    Wire.write(rotorOnePlace);
    Wire.endTransmission();
    for(int i = 0; i < 26; i++){
      rotorOne[i] = rotorOneDefault[i];
    }
    for(int i = 0; i < 26; i++){
      rotorTwo[i] = rotorTwoDefault[i];
    }
    for(int i = 0; i < 26; i++){
      rotorThree[i] = rotorThreeDefault[i];
    }
    openingSequence();
  }
}

//util functions

void openingSequence() {
  for (int i = 0; i < 9; i++) {
    writeLamp(firstRow[i]);
    delay(100);
  }
  for (int i = 0; i < 8; i++) {
    writeLamp(secondRow[i]);
    delay(100);
  }
  for (int i = 0; i < 9; i++) {
    writeLamp(thirdRow[i]);
    delay(100);
  }
}
boolean arrayContains(char array[], char element, int length) {
  for (int i = 0; i < length; i++) {
    if (array[i] == element) {
      return true;
    }
  }
  return false;
}

//machine functions

void writeLamp(char key) {
  if (arrayContains(firstRow, key, 9)) {
    digitalWrite(lanode[0], 1);
    digitalWrite(lanode[1], 0);
    digitalWrite(lanode[2], 0);
    writeRow(firstRow, key, 9);
  }

  if (arrayContains(secondRow, key, 8)) {
    digitalWrite(lanode[0], 0);
    digitalWrite(lanode[1], 1);
    digitalWrite(lanode[2], 0);
    writeRow(secondRow, key, 8);
  }

  if (arrayContains(thirdRow, key, 9)) {
    digitalWrite(lanode[0], 0);
    digitalWrite(lanode[1], 0);
    digitalWrite(lanode[2], 1);
    writeRow(thirdRow, key, 9);
  }
  else {
    Serial.println("Error: Invalid Key");
  }
}

void writeRow(char row[], char key, int length) {
  digitalWrite(lamp[8], 1);
  for (int i = 0; i < (length); i++) {
    if (row[i] == key) {
      digitalWrite(lamp[i], 0);
    }
    else {
      digitalWrite(lamp[i], 1);
    }
  }
}

void lampOff() {
  digitalWrite(lanode[0], 0);
  digitalWrite(lanode[1], 0);
  digitalWrite(lanode[2], 0);
}

bool reset() {
  if (analogRead(A1) <= 54 && analogRead(A2) <= 60 && analogRead(A3) <= 54) {
    return true;
  }
  return false;
}

char readKey() {
  int reading = analogRead(A1);
  if (reading >= 80 && reading <= 104) {
  }
  else if (reading <= 54) return 'P';
  else if (reading <= 108) return 'L';
  else if (reading <= 118) return 'M';
  else if (reading <= 132) return 'N';
  else if (reading <= 151) return 'B';
  else if (reading <= 176) return 'V';
  else if (reading <= 211) return 'C';
  else if (reading <= 265) return 'X';
  else if (reading <= 355) return 'Y';

  reading = analogRead(A2);
  if (reading >= 90 && reading <= 115) {
  }
  else if (reading <= 60) return 'A';
  else if (reading <= 120) return 'K';
  else if (reading <= 133) return 'J';
  else if (reading <= 151) return 'H';
  else if (reading <= 179) return 'G';
  else if (reading <= 220) return 'F';
  else if (reading <= 270) return 'D';
  else if (reading <= 400) return 'S';

  reading = analogRead(A3);
  if (reading >= 80 && reading <= 103) {
  }
  else if (reading <= 54) return 'Q';
  else if (reading <= 108) return 'O';
  else if (reading <= 118) return 'I';
  else if (reading <= 132) return 'U';
  else if (reading <= 151) return 'Z';
  else if (reading <= 176) return 'T';
  else if (reading <= 211) return 'R';
  else if (reading <= 265) return 'E';
  else if (reading <= 400) return 'W';

  return '?';
}

//encoding functions
char rotorEncode(char standard[26], char rotor[26], char key) {
  for (int i = 0; i < 26; i++) {
    if (standard[i] == key) {
      return rotor[i];
    }
  }
  return '?';
}

char rotorEncodeAll(char key) {
  return rotorEncode(alphabet, entryWheel,
                     rotorEncode(rotorOne, alphabet,
                                 rotorEncode(rotorTwo, alphabet,
                                     rotorEncode(rotorThree, alphabet,
                                         rotorEncode(alphabet, reflector,
                                             rotorEncode(alphabet, rotorThree,
                                                 rotorEncode(alphabet, rotorTwo,
                                                     rotorEncode(alphabet, rotorOne,
                                                         rotorEncode(entryWheel, alphabet, key)))))))));
}

char incrementPlace(char place) {
  if (place == 'Z') {
    return 'A';
  }
  return place + 1;
}



void incrementRotors() {
  if (rotorOnePlace == turnoverOne ) {
    turnRotor(rotorTwo);
    rotorTwoPlace = incrementPlace(rotorTwoPlace);
  }
  turnRotor(rotorOne);
  rotorOnePlace = incrementPlace(rotorOnePlace);

  if (stepThirdNextTurn) {
    turnRotor(rotorTwo);
    rotorTwoPlace = incrementPlace(rotorTwoPlace);
    turnRotor(rotorThree);
    rotorThreePlace = incrementPlace(rotorThreePlace);
  }
  stepThirdNextTurn = rotorTwoPlace == turnoverTwo;
}

void turnRotor(char rotor[26]) { //counter-clockwise
  char last = rotor[0];
  for (int i = 0; i < 25; i++) {
    rotor[i] = rotor[i + 1];
  }
  rotor[25] = last;
}

void ringTurnRotor(char rotor[26]) { //clockwise
  char last = rotor[25];
  for (int i = 1; i < 26; i++) {
    rotor[i] = rotor[i - 1];
  }
  rotor[0] = last;
}
