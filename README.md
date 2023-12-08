# ESPHome component adding support for the Maxbotix MB7851 TankSensor

This MAY work out of the box with all MB785x sensors, but it has only been tested with MB7851.

The sensors use the following format:

# MB7850
R### T###\r
“R” followed 3 ASCII numerical digits representing the range in centimeters. This will
be followed by a space, then “T” followed by 3 ASCII numerical digits representing the
teach confidence. Concluding with a carriage return.

# MB7851
R#### T###\r
“R” followed 4 ASCII numerical digits representing the range in millimeters. This will
be followed by a space, then “T” followed by 3 ASCII numerical digits representing the
teach confidence. Concluding with a carriage return.

# MB7853 and MB7854
R##### T###\r
“R” followed 5 ASCII numerical digits representing the range in millimeters. This will
be followed by a space, then “T” followed by 3 ASCII numerical digits representing the
teach confidence. Concluding with a carriage return.
