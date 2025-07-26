int latchPin = 4;
int clockPin = 7;
int dataPin = 8;
int buttonStartPin = A1;
int buttonPausePin = A2;
int buttonResetPin = A3;

int timeCount = 0;
bool running = false;

byte digits[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
byte digitsWithDot[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
byte pos[] = {0xF1, 0xF2, 0xF4, 0xF8};

unsigned long lastUpdateTime = 0;
unsigned long updateInterval = 10;

void setup()
{
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(buttonStartPin, INPUT_PULLUP);
    pinMode(buttonPausePin, INPUT_PULLUP);
    pinMode(buttonResetPin, INPUT_PULLUP);
}

void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdateTime >= updateInterval)
    {
        lastUpdateTime = currentMillis;

        if (digitalRead(buttonStartPin) == LOW)
        {
            running = true;
        }
        
        if (digitalRead(buttonPausePin) == LOW)
        {
            running = false;
        }

        if (digitalRead(buttonResetPin) == LOW)
        {
            timeCount = 0;
        }
        
        if (running)
        {
            timeCount = (timeCount + 1) % 10000;
        }
        
        display(timeCount);
    }
}

void display(int num)
{
    for (int i = 3; i >= 0; i--)
    {
        int value = i == 1 ? digitsWithDot[num % 10] : digits[num % 10];
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, value);
        shiftOut(dataPin, clockPin, MSBFIRST, pos[i]);
        digitalWrite(latchPin, HIGH);
        num /= 10;
        delay(2);
    }
}
