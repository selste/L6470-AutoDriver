#include <SPI.h>
#include "SparkFunAutoDriver.h"

int AutoDriver::_numBoards;

// Constructors
AutoDriver::AutoDriver(int position, int CSPin, int resetPin, int busyPin) {
  _CSPin = CSPin;
  _position = position;
  _resetPin = resetPin;
  _busyPin = busyPin;
  _numBoards++;
  _SPI = &SPI;

  _clock = 4000000;
  _bitOrder = MSBFIRST;
  _dataMode = SPI_MODE3;
}

AutoDriver::AutoDriver(int position, int CSPin, int resetPin) {
  _CSPin = CSPin;
  _position = position;
  _resetPin = resetPin;
  _busyPin = -1;
  _numBoards++;
  _SPI = &SPI;

  _clock = 4000000;
  _bitOrder = MSBFIRST;
  _dataMode = SPI_MODE3;
}

void AutoDriver::SPIPortConnect(SPIClass *SPIPort) {
  _SPI = SPIPort;
}

void AutoDriver::overrideSPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
    _clock = clock;
    _bitOrder = bitOrder;
    _dataMode = dataMode;
}

int AutoDriver::busyCheck(void) {
  if (_busyPin == -1) {
    if (getParam(STATUS) & 0x0002) return 0;
    else                           return 1;
  } else {
    if (digitalRead(_busyPin) == HIGH) return 0;
    else                               return 1;
  }
}
