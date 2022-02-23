#First semester final project for the Embedded Systems course in C++ and creating a simple protocol for communication betweeen Arduino and C# GUI app 

**How it works**
  - An arduino UNO R3 simulates physical buttons and instruments of a car and it is connected to a GUI application,written on C#, that plays role of a visual dashboard.

 **Arduino:** 
  - captures temp and displays it every 15 seconds in blackbox logger
  - buttons for left- and right-turn signals,hazard mode
  - performes measurement of the light level and decides whether to turn on headlights if dark enough and it doesn't flucutate
  - code can run simultaneously in the loop at every time as it does not block in if statements
  
  **C# GUI**
  - communicates with the arduino thanks to the Arduino IDE
  - plays a role of a dashboard
  - logs temp and what is activated in the car
  
  
  
  
