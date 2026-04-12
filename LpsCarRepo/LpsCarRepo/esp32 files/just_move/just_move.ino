const int L_FOR = 26;
const int L_BACK = 27;
const int R_FOR = 14;
const int R_BACK = 12;

// Lowering these from 255. 
// If it's too slow to move the Roomba, bump them up by 10 at a time.
int leftSpeed = 230;  
int rightSpeed = 200; 

void setup() {
  pinMode(L_FOR, OUTPUT);
  pinMode(L_BACK, OUTPUT);
  pinMode(R_FOR, OUTPUT);
  pinMode(R_BACK, OUTPUT);
  
  // Quick 1-second delay so you have time to set it down 
  // after plugging in the FTC battery.
  delay(1000); 
}

void loop() {
  // Drive Forward
  analogWrite(L_FOR, leftSpeed);
  digitalWrite(L_BACK, LOW);
  
  analogWrite(R_FOR, rightSpeed);
  digitalWrite(R_BACK, LOW);
  
  // If it starts "turtling" again, LOWER these speeds even more.
  // It sounds counter-intuitive, but slower = less heat = more consistency.
}