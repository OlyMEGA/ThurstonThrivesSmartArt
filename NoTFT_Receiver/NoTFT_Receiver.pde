import processing.serial.*;

Serial serial; 

void setup()
{
    serial = new Serial(this, "/dev/tty.usbmodem1421", 38400);
    size(320, 240);
    clear();
}

void draw()
{
  Update();  
}

void Update()
{
  if (serial.available() > 0)
  {
     String myString = serial.readStringUntil('\n');
     
    Command cmd = null;
    if (myString != null)
    {
      println("got string: " + myString.trim());      
      myString = myString.trim();
      cmd = new Command(myString);
      
      if (cmd != null)
      {
        cmd.execute();
      }
        
      println(cmd);
      println();
   }} 
    
}



