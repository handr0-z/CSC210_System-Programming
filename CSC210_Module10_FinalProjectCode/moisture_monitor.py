# Import any libraries needed for program to operate.
import sys
sys.path.append("/home/alejandr0/Documents/GitHub/CSC-210_System-Programming/CSC210_Module10_FinalProjectCode/lib/Adafruit_CircuitPython_ADS7830")

import time					# allows delays through time.sleep 
import board				# allows access to Raspberry Pi pins
import busio				# Creates I2C objects
import RPi.GPIO as GPIO		# Controls the Raspberry Pi GPIO pins

# Library for reading analog values form the ADS7830 ADC
from adafruit_ads7830.ads7830 import ADS7830

#--------------------------------------------------------------------------------------
# GPIO Setup RGB LED
#--------------------------------------------------------------------------------------

# Assign the pins on the Raspberry Pi to the RGB LED light pins correctly. 
R_PIN = 17
G_PIN = 27
B_PIN = 22

# BCM means we are using Broadcom pin numbering (Example: GPIO 17)
# Each pin is an output because LEDs need signals from the Raspberry Pi.
GPIO.setmode(GPIO.BCM)
GPIO.setup(R_PIN, GPIO.OUT)
GPIO.setup(G_PIN, GPIO.OUT)
GPIO.setup(B_PIN, GPIO.OUT)

R_pwm = GPIO.PWM(R_PIN, 1000) # 1 kHz
G_pwm = GPIO.PWM(G_PIN, 1000)
B_pwm = GPIO.PWM(B_PIN, 1000)

# Set starting value of RGB LED light
# Start OFF (common anode = 100%), ON is 0%
R_pwm.start(100)
G_pwm.start(100)
B_pwm.start(100)

"""
# Function used to set the color of the RGB LED light
def led_color(red, green, blue):
    # Common anode: LOW = ON, HIGH = OFF.
    GPIO.output(R_PIN, GPIO.LOW if red else GPIO.HIGH)
    GPIO.output(G_PIN, GPIO.LOW if green else GPIO.HIGH)
    GPIO.output(B_PIN, GPIO.LOW if blue else GPIO.HIGH)


# Function used to turn off the RGB LED light
def led_off():
    led_color(0, 0, 0)
"""

# Function used to set the color of RGB LED light
def pwm_color(r, g, b):
    # r, g, b = 0-255 brightness
    # convert to duty cycle (0% = full ON)
    R_pwm.ChangeDutyCycle(100 - (r / 255) * 100)
    G_pwm.ChangeDutyCycle(100 - (g / 255) * 100)
    B_pwm.ChangeDutyCycle(100 - (b / 255) * 100)

# Colors codes
COLOR_RED    = (255, 0, 0)
COLOR_ORANGE = (255, 80, 0)
COLOR_YELLOW = (255, 255, 0)
COLOR_GREEN  = (0, 255, 0)

# Function used to fade between colors smoothly.
def fade_to_color(start, end, steps=50, delay=0.02):
    sr, sg, sb = start
    er, eg, eb = end
    
    for i in range(steps):
        r = sr + (er - sr) * (i / steps)
        g = sg + (eg - sg) * (i / steps)
        b = sb + (eb - sb) * (i / steps)
        pwm_color(r,g,b)
        time.sleep(delay)

#--------------------------------------------------------------------------------------
# ADC Setup (ADS7830 over I2C)
#--------------------------------------------------------------------------------------

# Create an I2C Connection using the Raspberry Pi's SDA/ SCL pins
i2c = busio.I2C(board.SCL, board.SDA)

# Initialize the ADS7830 ADC Chip
ads = ADS7830(i2c)

# Create chan as an analog input on channel 0.
# chan = AnalogIn(ads, 0) # Channel 0 is where the moisture sensor is connected.

#--------------------------------------------------------------------------------------
# Moisture Logic
#--------------------------------------------------------------------------------------

# Function determine value of RGB LED based on value obtained from moisture sensor. 
def moisture_to_zone(value):
    # ADS7830 returns values from 0 to 255.
    # DRY = higher value
    # WET = lower value
    
    if value > 200:
        return 1 # very dry
    elif value > 150:
        return 2 # dry
    elif value > 100:
        return 3 # wet
    else:
        return 4 # very wet
    
# Remember last color for smooth transitions
current_color = COLOR_GREEN


# Function used to set the value of RGB LED light.
def apply_zone(zone):
    global current_color
    if zone == 1:   target = COLOR_RED     # Set RGB LED light color to red
    elif zone == 2: target = COLOR_ORANGE  # Set RGB LED light color to orange
    elif zone == 3: target = COLOR_YELLOW  # Set RGB LED light color to yellow
    else:           target = COLOR_GREEN  # Set RGB LED light color to green
    
    fade_to_color(current_color, target)
    current_color = target

#--------------------------------------------------------------------------------------
# Main loop
#--------------------------------------------------------------------------------------

try:
    while True: # Loop to check for moisture level.
        raw = ads.read(0) >> 8# Convert 0-65535 back to 0-225 range
        zone = moisture_to_zone(raw) # Determine zone based on sensor value.
        
        print(f"Moisture Value: {raw} | Zone: {zone}") # Dispaly information obtained.
        apply_zone(zone) # change the value of the RGB LED light.
        
        time.sleep(1) # Wait before repeating loop again.
        
except KeyboardInterrupt:
    pwm_color(0,0,0)
    R_pwm.stop()
    G_pwm.stop()
    B_pwm.stop()
    GPIO.cleanup()
