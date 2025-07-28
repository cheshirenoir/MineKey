#include <Keyboard.h>

// constants won't change. They're used here to set pin numbers:
const int rowPin1 = 9;        // For row and column scan, row 1 pin
const int rowPin2 = 8;        // For row and column scan, row 2 pin
const int rowPin3 = 7;        // For row and column scan, row 3 pin
const int rowPin4 = 6;        // For row and column scan, row 4 pin

const int colPin1 = 13;       // For row and column scan, column 1 pin
const int colPin2 = 12;       // For row and column scan, column 2 pin
const int colPin3 = 11;       // For row and column scan, column 3 pin
const int colPin4 = 10;       // For row and column scan, column 4 pin

const int buttonPinRL = 18;   // the number of the pushbutton pin
const int buttonPinRR = 21;   // the number of the pushbutton pin
const int buttonPin17 = 4;    // the number of the pushbutton pin
const int buttonPin18 = 2;    // the number of the pushbutton pin

//MICHAEL: Comment out the two lines above and uncmment the two lines below.
//const int buttonPin17 = 1;    // the number of the pushbutton pin
//const int buttonPin18 = 0;    // the number of the pushbutton pin

//Mapping into an array of all 20 keys so they can be swapped out easily
//Order is SW1-SW16, RSwitch1, RSwitch2
char keycharmap[4][18] = {
  {'7','8','9','/','4','5','6','*','1','2','3','-','#','0','.','+',KEY_RETURN,KEY_BACKSPACE},
  {'1','2','3','4','Q','W','E','R','A','S','D','F','Z','X','C','V',KEY_RETURN,KEY_BACKSPACE},
  {'5','6','7','8','T','Y','U','I','G','H','J','K','B','N','M',',',KEY_RETURN,KEY_BACKSPACE},
  {KEY_KP_7,KEY_KP_8,KEY_KP_9,KEY_KP_SLASH,KEY_KP_4,KEY_KP_5,KEY_KP_6,KEY_KP_ASTERISK,KEY_KP_1,KEY_KP_2,KEY_KP_3,KEY_KP_MINUS,KEY_KP_0,KEY_KP_0,KEY_KP_DOT,KEY_KP_PLUS,KEY_RETURN,KEY_BACKSPACE}
};

// Variables will change:
int buttonState1;				      // the current reading from the input pin
int lastButtonState1 = LOW;		// the previous reading from the input pin
int buttonState2;				      // the current reading from the input pin
int lastButtonState2 = LOW;		// the previous reading from the input pin
int buttonState3;				      // the current reading from the input pin
int lastButtonState3 = LOW;		// the previous reading from the input pin
int buttonState4;				      // the current reading from the input pin
int lastButtonState4 = LOW;		// the previous reading from the input pin
int buttonState5;				      // the current reading from the input pin
int lastButtonState5 = LOW;		// the previous reading from the input pin
int buttonState6;				      // the current reading from the input pin
int lastButtonState6 = LOW;		// the previous reading from the input pin
int buttonState7;				      // the current reading from the input pin
int lastButtonState7 = LOW;		// the previous reading from the input pin
int buttonState8;				      // the current reading from the input pin
int lastButtonState8 = LOW;		// the previous reading from the input pin
int buttonState9;				      // the current reading from the input pin
int lastButtonState9 = LOW;		// the previous reading from the input pin
int buttonState10;				    // the current reading from the input pin
int lastButtonState10 = LOW;	// the previous reading from the input pin
int buttonState11;				    // the current reading from the input pin
int lastButtonState11 = LOW;	// the previous reading from the input pin
int buttonState12;			    	// the current reading from the input pin
int lastButtonState12 = LOW;	// the previous reading from the input pin
int buttonState13;				    // the current reading from the input pin
int lastButtonState13 = LOW;	// the previous reading from the input pin
int buttonState14;	    			// the current reading from the input pin
int lastButtonState14 = LOW;	// the previous reading from the input pin
int buttonState15;		    		// the current reading from the input pin
int lastButtonState15 = LOW;	// the previous reading from the input pin
int buttonState16;	    			// the current reading from the input pin
int lastButtonState16 = LOW;	// the previous reading from the input pin
int buttonStateRL;            // the current reading from the input pin
int lastButtonStateRL = LOW;  // the previous reading from the input pin
int buttonStateRR;            // the current reading from the input pin
int lastButtonStateRR = LOW;  // the previous reading from the input pin
int buttonState17;            // the current reading from the input pin
int lastButtonState17 = LOW;  // the previous reading from the input pin
int buttonState18;            // the current reading from the input pin
int lastButtonState18 = LOW;  // the previous reading from the input pin

int metasuper = 0; // Used to record whether the META and SUPER keys are pressed. For META add 1 for SUPER add 2. This becomes the index fo which keyset

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime3 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime4 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime5 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime6 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime7 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime8 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime9 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime10 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime11 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime12 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime13 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime14 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime15 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime16 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeRL = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeRR = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime17 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime18 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 30;    // the debounce time; increase if the output flickers

// Which column are we currently working on? This cycles 1-4 on a pass through the main loop
int currentCol = 1;

void setup() {
  // setup the fixed buttons
  pinMode(buttonPinRL, INPUT_PULLDOWN);
  pinMode(buttonPinRR, INPUT_PULLDOWN);
  pinMode(buttonPin17, INPUT_PULLDOWN);
  pinMode(buttonPin18, INPUT_PULLDOWN);

  // setup the rows and columns.
  pinMode(rowPin1, INPUT_PULLDOWN);
  pinMode(rowPin2, INPUT_PULLDOWN);
  pinMode(rowPin3, INPUT_PULLDOWN);
  pinMode(rowPin4, INPUT_PULLDOWN);
  pinMode(colPin1, OUTPUT);
  pinMode(colPin2, OUTPUT);
  pinMode(colPin3, OUTPUT);
  pinMode(colPin4, OUTPUT);
  
  // setup the keyboard output.
  Keyboard.begin();

  // set all the columns to low so nothing gets read.
  digitalWrite(colPin1, LOW);
  digitalWrite(colPin2, LOW);
  digitalWrite(colPin3, LOW);
  digitalWrite(colPin4, LOW);
}

void loop() {
  // read the state of the Rotary Left switch into a local variable:
  int reading = digitalRead(buttonPinRL);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonStateRL) {
    // reset the debouncing timer
    lastDebounceTimeRL = millis();
  }

  if ((millis() - lastDebounceTimeRL) > debounceDelay) 
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonStateRL) 
    {
      buttonStateRL = reading;

      // only output the character if the new button state is HIGH, else release the key.
      if (buttonStateRL == HIGH) 
      {
        Keyboard.press(keycharmap[metasuper][16]);
      }
      else
      {
	      Keyboard.release(keycharmap[metasuper][16]);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonStateRL = reading;

  // Now Rotary Right
  reading = digitalRead(buttonPinRR);

  if (reading != lastButtonStateRR) 
  {
    lastDebounceTimeRR = millis();
  }

  if ((millis() - lastDebounceTimeRR) > debounceDelay) 
  {
    if (reading != buttonStateRR) 
    {
      buttonStateRR = reading;
      if (buttonStateRR == HIGH) 
      {
        Keyboard.press(keycharmap[metasuper][17]);
      }
      else
      {
	      Keyboard.release(keycharmap[metasuper][17]);
      }
    }
  }

  lastButtonStateRR = reading;

  // Now the META key
  reading = digitalRead(buttonPin17);

  if (reading != lastButtonState17) 
  {
    lastDebounceTime17 = millis();
  }

  if ((millis() - lastDebounceTime17) > debounceDelay) 
  {
    if (reading != buttonState17) 
    {
      buttonState17 = reading;
      if (buttonState17 == HIGH) 
      {
        metasuper=metasuper+1;
      }
      else
      {
	      metasuper=metasuper-1;
      }
    }
  }

  lastButtonState17 = reading;

  // Now the SUPER key
  reading = digitalRead(buttonPin18);

  if (reading != lastButtonState18) 
  {
    lastDebounceTime18 = millis();
  }

  if ((millis() - lastDebounceTime18) > debounceDelay) 
  {
    if (reading != buttonState18) 
    {
      buttonState18 = reading;
      if (buttonState18 == HIGH) 
      {
        metasuper=metasuper+2;
      }
      else
      {
        metasuper=metasuper-2;
      }
    }
  }

  lastButtonState18 = reading;

  // Time to strobe the current column and deal with what pops out
  switch(currentCol)
  {
  case 1:
    // This is the first column. Pull the column pin high to activate it.
    digitalWrite(colPin1, HIGH);
    reading = digitalRead(rowPin1);
    if (reading != lastButtonState1) 
    {
      lastDebounceTime1 = millis();
    }
    if ((millis() - lastDebounceTime1) > debounceDelay) 
    {
      if (reading != buttonState1) 
      {
        buttonState1 = reading;
        if (buttonState1 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][0]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][0]);
        }
      }
    }
    lastButtonState1 = reading;

    reading = digitalRead(rowPin2);
    if (reading != lastButtonState5) 
    {
      lastDebounceTime5 = millis();
    }
    if ((millis() - lastDebounceTime5) > debounceDelay) 
    {
      if (reading != buttonState5) 
      {
        buttonState5 = reading;
        if (buttonState5 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][4]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][4]);
        }
      }
    } 
    lastButtonState5 = reading;

    reading = digitalRead(rowPin3);
    if (reading != lastButtonState9) 
    {
      lastDebounceTime9= millis();
    }
    if ((millis() - lastDebounceTime9) > debounceDelay) 
    {
      if (reading != buttonState9) 
      {
        buttonState9 = reading;
        if (buttonState9 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][8]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][8]);
        }
      }
    }
    lastButtonState9 = reading;
    
    reading = digitalRead(rowPin4);
    if (reading != lastButtonState13) 
    {
      lastDebounceTime13 = millis();
    }
    if ((millis() - lastDebounceTime13) > debounceDelay) 
    {
      if (reading != buttonState13) 
      {
        buttonState13 = reading;
        if (buttonState13 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][12]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][12]);
        }
      }
    }
    lastButtonState13 = reading;

    // now pull the pin back dwon.
    digitalWrite(colPin1, LOW);

  case 2:
    // this is column 2
    digitalWrite(colPin2, HIGH);
    reading = digitalRead(rowPin1);
    if (reading != lastButtonState2) 
    {
      lastDebounceTime2 = millis();
    }
    if ((millis() - lastDebounceTime2) > debounceDelay) 
    {
      if (reading != buttonState2) 
      {
        buttonState2 = reading;
        if (buttonState2 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][1]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][1]);
        }
      }
    }
    lastButtonState2 = reading;

    reading = digitalRead(rowPin2);
    if (reading != lastButtonState6) 
    {
      lastDebounceTime6 = millis();
    }
    if ((millis() - lastDebounceTime6) > debounceDelay) 
    {
      if (reading != buttonState6) 
      {
        buttonState6 = reading;
        if (buttonState6 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][5]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][5]);
        }
      }
    } 
    lastButtonState6 = reading;

    reading = digitalRead(rowPin3);
    if (reading != lastButtonState10) 
    {
      lastDebounceTime10 = millis();
    }
    if ((millis() - lastDebounceTime10) > debounceDelay) 
    {
      if (reading != buttonState10) 
      {
        buttonState10 = reading;
        if (buttonState10 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][9]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][9]);
        }
      }
    }
    lastButtonState10 = reading;

    reading = digitalRead(rowPin4);
    if (reading != lastButtonState14) 
    {
      lastDebounceTime8 = millis();
    }
    if ((millis() - lastDebounceTime14) > debounceDelay) 
    {
      if (reading != buttonState14) 
      {
        buttonState14 = reading;
        if (buttonState14 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][13]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][13]);
        }
      }
    }
    lastButtonState14 = reading;

    digitalWrite(colPin2, LOW);

  case 3:
    // The third column
    digitalWrite(colPin3, HIGH);
    reading = digitalRead(rowPin1);
    if (reading != lastButtonState3) 
    {
      lastDebounceTime3 = millis();
    }
    if ((millis() - lastDebounceTime3) > debounceDelay) 
    {
      if (reading != buttonState3) 
      {
        buttonState3 = reading;
        if (buttonState3 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][2]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][2]);
        }
      }
    }
    lastButtonState3 = reading;

    reading = digitalRead(rowPin2);
    if (reading != lastButtonState7) 
    {
      lastDebounceTime7 = millis();
    }
    if ((millis() - lastDebounceTime7) > debounceDelay) 
    {
      if (reading != buttonState7) 
      {
        buttonState7 = reading;
        if (buttonState7 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][6]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][6]);
        }
      }
    } 
    lastButtonState7 = reading;

    reading = digitalRead(rowPin3);
    if (reading != lastButtonState11) 
    {
      lastDebounceTime11 = millis();
    }
    if ((millis() - lastDebounceTime11) > debounceDelay) 
    {
      if (reading != buttonState11) 
      {
        buttonState11 = reading;
        if (buttonState11 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][10]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][10]);
        }
      }
    }
    lastButtonState11 = reading;

    reading = digitalRead(rowPin4);
    if (reading != lastButtonState15) 
    {

      lastDebounceTime15 = millis();
    }
    if ((millis() - lastDebounceTime15) > debounceDelay) 
    {
      if (reading != buttonState15) 
      {
        buttonState15 = reading;
        if (buttonState15 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][14]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][14]);
        }
      }
    }
    lastButtonState15 = reading;

    digitalWrite(colPin3, LOW);

  case 4:
    // The final column
    digitalWrite(colPin4, HIGH);
    reading = digitalRead(rowPin1);
    if (reading != lastButtonState4) 
    {
      lastDebounceTime4 = millis();
    }
    if ((millis() - lastDebounceTime4) > debounceDelay) 
    {
      if (reading != buttonState4) 
      {
        buttonState4 = reading;
        if (buttonState4 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][3]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][3]);
        }
      }
    }
    lastButtonState4 = reading;

    reading = digitalRead(rowPin2);
    if (reading != lastButtonState8) 
    {
      lastDebounceTime8 = millis();
    }
    if ((millis() - lastDebounceTime8) > debounceDelay) 
    {
      if (reading != buttonState8) 
      {
        buttonState8 = reading;
        if (buttonState8 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][7]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][7]);
        }
      }
    } 
    lastButtonState8 = reading;

    reading = digitalRead(rowPin3);
    if (reading != lastButtonState12) 
    {
      lastDebounceTime12 = millis();
    }
    if ((millis() - lastDebounceTime12) > debounceDelay) 
    {
      if (reading != buttonState12) 
      {
        buttonState12 = reading;
        if (buttonState12 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][11]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][11]);
        }
      }
    }
    lastButtonState12 = reading;

    reading = digitalRead(rowPin4);
    if (reading != lastButtonState16) 
    {
      lastDebounceTime16 = millis();
    }
    if ((millis() - lastDebounceTime16) > debounceDelay) 
    {
      if (reading != buttonState16) 
      {
        buttonState16 = reading;
        if (buttonState16 == HIGH) 
        {
          Keyboard.press(keycharmap[metasuper][15]);
        }
	else
        {
	        Keyboard.release(keycharmap[metasuper][15]);
        }
      }
    }
    lastButtonState16 = reading;

    digitalWrite(colPin4, LOW);
  }

  // Increment the current column number. roll it over if needed
  currentCol++;
  if (currentCol==5)
  {
    currentCol=1;
  }
}