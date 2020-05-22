#!/bin/sh

if [ -z $ARDUINO_HOME ]; then
echo "Environment variable ARDUINO_HOME is empty or unset."
echo "Please set it in your shell's config file e.g.\n"
echo "- ~/.bashrc (bash) or"
echo "- ~/.config/fish/config.fish (fish)"
exit 1
fi

command -v arduino >/dev/null 2>&1 || {
  echo "Arduino IDE could not be found."
  echo "Please install it (https://www.arduino.cc/en/Main/Software)."
  exit 1;
}

command -v git >/dev/null 2>&1 || {
  echo "git is not installed."
  echo "Please install it using your package manager."
  exit 1;
}

arduino --install-library "Adafruit BusIO"
arduino --install-library "Adafruit GFX Library"
arduino --install-library "Adafruit SSD1306"
arduino --install-library "Adafruit Unified Sensor"
arduino --install-library "DHT sensor library"
arduino --install-library "HCSR04"
arduino --install-library "Keypad"

if [ ! -d "$ARDUINO_HOME"/libraries/BMP180 ]; then git clone https://github.com/sparkfun/BMP180_Breakout_Arduino_Library.git "$ARDUINO_HOME"/libraries/BMP180; fi
f [ ! -d "$ARDUINO_HOME"/libraries/BigNumber ]; then git clone https://github.com/leonardoInf/BigNumber.git "$ARDUINO_HOME"/libraries/BigNumber; fi
