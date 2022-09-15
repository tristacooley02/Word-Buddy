// Functions for Button Control

int charDelay = 10; // UPDATE THIS CODE -- Amount of time between keypresses to avoid key buffer overflows
int numButtons = 9;
// initButtons loops through the array of Bounce2 buttons and attaches them as inputs.
// It also sets an interval of 25ms for responsiveness
void initButtons(){

  for(int i = 0; i < numButtons; i++){
    buttons[i].attach(buttonPins[i], INPUT);
    buttons[i].interval(25);
    
  }
 
}

// readButtons loops through the array of Bounce2 buttons and updates each of them.
// It then checks to see if any button has risen and calls sendKey() if it has.
void readButtons(){

  for(int i = 0; i < numButtons; i++){
    buttons[i].update();
    if(buttons[i].rose()){
      sendKey(i);
    }
  }

}

// sendKey takes one argument (int k) and uses a switch/case structure to either call the
// sendShortcut(), sendCompount(), or sendMacro() functions. You can also create your own custom functions if needed.
void sendKey(int k){
  
  switch(k){
    
    //save
    case 0: sendShortcut('s'); break;
    //copy
    case 1: sendShortcut('n'); break;
    //paste
    case 2: sendCompound('l'); break;
    //new
    case 3: sendShortcut('c'); break;
    //bold
    case 4: sendShortcut('v'); break;
    //undo
    case 5: sendShortcut('z'); break;
    //decrease text
    case 6: sendShortcut('>'); break;
    //increase text
    case 7: sendShortcut('<'); break;
    //download
    case 8: sendShortcut('b'); break;

  }

}

// sendShortcut takes one argument (char c) and combines it with a modifier (CRTL, CMD, ALT, SHIFT, etc.)
// Remember to delay between each press, and release each key. Call releaseAll before ending this function.
void sendShortcut(char c){
  
  bleKeyboard.press(KEY_LEFT_GUI);  delay(charDelay);
  bleKeyboard.press(c);  delay(charDelay);
  bleKeyboard.release(c);  delay(charDelay);
  bleKeyboard.release(KEY_LEFT_GUI);  delay(charDelay);
  bleKeyboard.releaseAll();


}

// sendCompound takes one argument (char c) and combines it with multiple modifiers (CRTL, CMD, ALT, SHIFT, etc.)
// Remember to delay between each press, and release each key. Call releaseAll before ending this function.
void sendCompound(char c){
  
  bleKeyboard.press(KEY_LEFT_GUI);  delay(charDelay);
  bleKeyboard.press(KEY_LEFT_SHIFT);  delay(charDelay);
  bleKeyboard.press(c);  delay(charDelay);
  bleKeyboard.release(c);  delay(charDelay);
  bleKeyboard.release(KEY_LEFT_SHIFT);  delay(charDelay);
  bleKeyboard.release(KEY_LEFT_GUI);  delay(charDelay);
  bleKeyboard.releaseAll();

}

// sendMacro takes one argument (String s) and sends the string one character at a time.
void sendMacro(String s, int d){
  int l = s.length() + 1;           // Determine length of string
  char c[l];                        // Create array for characters
  s.toCharArray(c, l);              // Copy characters to array
  for (int i = 0; i < l - 1; i++){  // Loop through character array
    char p = c[i];                  // Get the current character
    bleKeyboard.press(p); delay(d); // Press/Release the key w/ delay
    bleKeyboard.release(p); delay(d);
  }
  bleKeyboard.releaseAll();
}
