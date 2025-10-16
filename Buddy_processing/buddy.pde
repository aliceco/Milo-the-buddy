import ddf.minim.*;
import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port

Minim minim;
AudioPlayer player;

void setup() {
  println(Serial.list());
  //String portName = "/dev/cu.usbmodem1301"; // explicitly pick Arduino port

  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  
  size(200,200);
  //minim = new Minim(this);
  //player = minim.loadFile("Cheers.wav");

}

void draw() {
  while (myPort.available() > 0) { //<>//
    val = myPort.readStringUntil('\n');
    if (val != null) {
      val = val.trim();
      println(val);
    }
  }
  
  
}



/*
void keyPressed() {
  if (!player.isPlaying()) {
    player.play();
  }
}
*/
