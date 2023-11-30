# Arduino-Bot

This is an line following, object avoiding, lane shifting bot that I built for the FCC Scicon 1 Dynamic Model competetion. 
It uses a sonar for obstacle detection and 2 ir sensors to detect the track lines. It follows the line initialy and upon detection of an obstacle it uses the servo to rotate its head(where the sonar is mounted) and determines which direction has more room to move, then it moves in that direction untill a new line is detected which it then follows.
