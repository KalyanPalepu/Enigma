char[] rotorOne = {'D', 'M', 'T', 'W', 'S', 'I', 'L', 'R', 'U', 'Y', 'Q', 'N', 'K', 'F', 'E', 'J', 'C', 'A', 'Z', 'B', 'P', 'G', 'X', 'O', 'H', 'V'};
char[] rotorTwo = {'H', 'Q', 'Z', 'G', 'P', 'J', 'T', 'M', 'O', 'B', 'L', 'N', 'C', 'I', 'F', 'D', 'Y', 'A', 'W', 'V', 'E', 'U', 'S', 'R', 'K', 'X'};
char[] rotorThree = {'U', 'Q', 'N', 'T', 'L', 'S', 'Z', 'F', 'M', 'R', 'E', 'H', 'D', 'P', 'X', 'K', 'I', 'B', 'V', 'Y', 'G', 'J', 'C', 'W', 'O', 'A'};

char[] alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(readKey());
}

char readKey() {
  int reading = analogRead(A1);
  if (reading >= 80 && reading <= 104) {}
  else if (reading <= 54) return 'p';
  else if (reading <= 108) return 'l';
  else if (reading <= 118) return 'm';
  else if (reading <= 132) return 'n';
  else if (reading <= 151) return 'b';
  else if (reading <= 176) return 'v';
  else if (reading <= 211) return 'c';
  else if (reading <= 265) return 'x';
  else if (reading <= 355) return 'y';

  reading = analogRead(A2);
  if (reading >= 90 && reading <= 115) {}
  else if (reading <= 60) return 'a';
  else if (reading <= 120) return 'k';
  else if (reading <= 133) return 'j';
  else if (reading <= 151) return 'h';
  else if (reading <= 179) return 'g';
  else if (reading <= 220) return 'f';
  else if (reading <= 270) return 'd';
  else if (reading <= 400) return 's';

  reading = analogRead(A3);
  if (reading >= 80 && reading <= 103) {}
  else if (reading <= 54) return 'q';
  else if (reading <= 108) return 'o';
  else if (reading <= 118) return 'i';
  else if (reading <= 132) return 'u';
  else if (reading <= 151) return 'z';
  else if (reading <= 176) return 't';
  else if (reading <= 211) return 'r';
  else if (reading <= 265) return 'e';
  else if (reading <= 400) return 'w';

  return '\0';
}



char rotorEncode(char rotor[26], char key) {
  for(int i = 0; i < 26; i++){
    if(alphabet[i] = key){
      return rotor[i]
    }
  }
  return '!';
}

char rotorEncodeAll(char key){
  return rotorEncode(rotorOne, rotorEncode(rotorTwo
}
