const byte SEGMENT_PINS[8] = {9, 8, 7, 6, 2, 3, 4, 5};
const byte POWER_PINS[4] = {10, 11, 12, 13};
const byte SEGMENT_LENGTH = sizeof(SEGMENT_PINS) / sizeof(byte);
const byte POWER_LENGTH = sizeof(POWER_PINS) / sizeof(byte);
const unsigned int SEGMENTS[8] = {
    // middle
    1 << 0,
    // top left
    1 << 1,
    // top
    1 << 2,
    // top right
    1 << 3,
    // dot
    1 << 4,
    // bottom right
    1 << 5,
    // bottom
    1 << 6,
    // bottom left
    1 << 7
};
const unsigned int DIGITS[10] = {
    // 0
    (SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]),
    // 1
    (SEGMENTS[3] | SEGMENTS[5]),
    // 2
    (SEGMENTS[0] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[6] | SEGMENTS[7]),
    // 3
    (SEGMENTS[0] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6]),
    // 4
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[3] | SEGMENTS[5]),
    // 5
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[5] | SEGMENTS[6]),
    // 6
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]),
    // 7
    (SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5]),
    // 8
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]),
    // 9
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6])
};
unsigned int x = 0;
 
void setup() {
    byte length;
    for (byte i = 0; i < POWER_LENGTH; i++) {
        pinMode(POWER_PINS[i], OUTPUT);
        digitalWrite(POWER_PINS[i], LOW);
    }
    for (byte i = 0; i < SEGMENT_LENGTH; i++) {
        pinMode(SEGMENT_PINS[i], OUTPUT);
        digitalWrite(SEGMENT_PINS[i], HIGH);
    }
}
 
void loop() {
    x %= 10000;
    // loop 4 digits for assigning the dot
    for (byte k = 0; k < POWER_LENGTH; k++) {
        for (byte j = 0; j < (100 / POWER_LENGTH); j++) {
            // loop 4 digits
            unsigned int y = 1;
            for (byte i = 0; i < POWER_LENGTH; i++) {
                y *= 10;
                // set segments to the digit
                // assign the dot to the digit each 250ms
                setLED(POWER_PINS[i], DIGITS[(x / (y / 10)) % 10] | ((k == i) ? SEGMENTS[4] : 0));
            }
            // total delay 8ms 4 digits
            // delay extra 2ms to be 10ms in a period
            delay(2);
        }
    }
    x++;
}
 
void setLED(byte powerPin, unsigned int segmentValue, bool enabled) {
    digitalWrite(powerPin, enabled ? HIGH : LOW);
    for (byte i = 0; i < SEGMENT_LENGTH; i++) {
        if ((segmentValue & SEGMENTS[i]) > 0) {
            digitalWrite(SEGMENT_PINS[i], enabled ? LOW : HIGH);
        }
    }
    delay(1);
}
 
void setLED(byte powerPin, unsigned int segmentValue) {
    setLED(powerPin, segmentValue, true);
    setLED(powerPin, segmentValue, false);
}
