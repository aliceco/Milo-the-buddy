import ddf.minim.*;
import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port

Minim minim;
AudioPlayer welcome;
AudioPlayer cheers;
AudioPlayer portal;
AudioPlayer letGo;
AudioPlayer thankyou;
AudioPlayer hiThere;


AudioPlayer[] optionsQuestion1;
AudioPlayer[] optionsQuestion2;

int lastStage = 0;
int stage = 0;
int question_numb;


void setup() {

  //String portName = "/dev/cu.usbmodem1301"; // explicitly pick Arduino port

  String portName = Serial.list()[2]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  println (Serial.list());
  
  size(200,200);
  minim = new Minim(this);
  
  welcome = minim.loadFile("Welcome.wav");
  portal = minim.loadFile("Portal.wav");  
  cheers = minim.loadFile("Cheers.wav");
  letGo = minim.loadFile("letGo-slowed3.wav");
  hiThere = minim.loadFile("Hi-there.mp3");
  
  optionsQuestion1 = new AudioPlayer[4];
  optionsQuestion1[0] = minim.loadFile("part1-q1.mp3");
  optionsQuestion1[0] = minim.loadFile("part1-q2.mp3");
  optionsQuestion1[0] = minim.loadFile("part1-q3.mp3");
  optionsQuestion1[0] = minim.loadFile("part1-q4.mp3");

  
  optionsQuestion2 = new AudioPlayer[4];
  optionsQuestion2[0] = minim.loadFile("part2-q1.mp3");
  optionsQuestion2[0] = minim.loadFile("part2-q2.mp3");
  optionsQuestion2[0] = minim.loadFile("part2-q3.mp3");
  optionsQuestion2[0] = minim.loadFile("part2-q4.mp3");
  
}

void draw() {
  while (myPort.available() > 0) {
    val = myPort.readStringUntil('\n');
    if (val != null) {
      val = val.trim();
      println("Received: " + val);

      // Only act if it's numeric
      if (val.matches("\\d+")) {
        int stage = Integer.parseInt(val);
        
        // Avoid retriggering the same stage
        if (stage != lastStage) {
          lastStage = stage;
          
          switch(stage) {
            case 1:
              println("Stage 1: Welcome / Question 1");
              welcome.play();
              delay(500);
              
              question_numb = (int)random(0, 4);
              delay(1000);
              println(question_numb);
              optionsQuestion1[question_numb].play();
              question_numb = 0;
              break;
            case 2:
              println("Stage 2: Swoosh");
              letGo.play();

              break;
            case 3:
              println("Stage 2.5: Cheers");
              cheers.play();
              delay(600);
              question_numb = (int)random(0, 4);
              println(question_numb);
              optionsQuestion2[question_numb].play();
              question_numb = 0;
              break;
            
            case 4:
              println("Stage 2.5: Portal");
              println("thank you for your thoughts");
              portal.play();
              delay(1500);
              thankyou.play();
              break;
          }
        }
      }
    }
  }
}
