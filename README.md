# GroveRFIDReader
125KHz RFID Reader Library for Arduino + Grove shield

[Link to the tested grove module](http://wiki.seeed.cc/Grove-125KHz_RFID_Reader/)

## Example
```c++
#include <GroveRFIDReader.h>

GroveRFIDReader tagReader(GROVE_D2);

void setup() {
    tagReader.initialize();
    Serial.begin(9600);
}
 
void loop() {
  if(tagReader.isTagAvailable()) {
    Serial.println(tagReader.read());
  }
  delay(50);
}
```

## Documentation
###`GroveRFIDReader(GrovePin pins, unsigned char tabBufferSize = 64, unsigned char charBufferSize = 16)`
Parameters:
- `pins`: Must be a digital socket (GROVE_D2 to GROVE_D8)
- `tabBufferSize`: The size of the tag buffer (number of tag id store before read)
- `charBufferSize`: The size of the char buffer (must be >= 14)

###`void initialize()`
Initialize the sensor before using it.

###`boolean isTagAvailable()`
Return `true` if a valid RFID tag is read

###`unsigned long read()`
Return the identifier of the RFID tag (0 if no tag is detected)