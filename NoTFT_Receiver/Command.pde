class Command
{
  private String _cmdName;
  private ArrayList _args = new ArrayList();
  
  public String toString()
  {
    return _cmdName;
  }
  
  public Command(String input)
  {
    processString(input);
  }

  private void processString(String input)
  {
    println("INPUT: " + input);
      if (input == null) 
        return;
        
      String[] words = split(input, ' ');   
      
      if (words == null || words.length == 0) 
        return;
      
      _cmdName = words[0].toLowerCase();
  
      for (int wordIdx=1; wordIdx<words.length; wordIdx++)
      {
       String word = words[wordIdx];


       if (word != null && wordIdx != 0)
       {
         println("Adding word: " + word);
         _args.add(word);
       } 
        
      }
  }
  
  public void execute()
  {
    if (_cmdName == null)
      return;
      
    if (_cmdName.equals("bg"))
    {
        if (_args == null || _args.size() != 3)
          return;
       
        int red = int((String)_args.get(0));
        int green = int((String)_args.get(1));
        int blue = int((String)_args.get(2));        
        background(red, green, blue);
    } else if (_cmdName.equals("stroke")) {
      if (_args == null || _args.size() != 3)
        return;
      
      println("stroke!!!!!!!!!!!!!!!!!!");

      int red = int((String)_args.get(0));
      int green = int((String)_args.get(1));
      int blue = int((String)_args.get(2));        
      stroke(red,green,blue);

    } else if (_cmdName.equals("fillroundrect")) {
      if (_args == null || _args.size() != 5)
        return;
      println("filling round rect...");
     int x = int((String)_args.get(0));   
     int y = int((String)_args.get(1));   
     int h = int((String)_args.get(2));   
     int w = int((String)_args.get(3));   
     int r = int((String)_args.get(4));
     
     stroke(255,0,0);
     fill(255,0,0);
     rect(x,y,h,w,r);
        
        

      
    } else if (_cmdName.equals("rect")) {
      if (_args == null || _args.size() != 4)
        return;
               
      println("rect!!!!!!!!!!!!!!!!!!");
     int x = int((String)_args.get(0));   
     int y = int((String)_args.get(1));   
     int h = int((String)_args.get(2));   
     int w = int((String)_args.get(3));   
      
     rect(x,y,h,w);
        
        
    } else if (_cmdName.equals("clear")) {
      println("clear!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      clear();
    } else if (_cmdName.equals("fillscr")) {      
      if (_args == null || _args.size() != 3)
        return;

      int red = int((String)_args.get(0));
      int green = int((String)_args.get(1));
      int blue = int((String)_args.get(2));        
      background(red,green,blue);
      
    } else if (_cmdName.equals("setcolor")) {
      if (_args == null || _args.size() != 3) return;

      ArrayList<Integer> arr = getRGB();
      stroke(arr.get(0), arr.get(1), arr.get(2));
      fill(arr.get(0), arr.get(1), arr.get(2));
      
    } else if (_cmdName.equals("fillrect")) {
      if (_args == null || _args.size() != 4) return;
      
      ArrayList<Integer> arr = getXYWH();
      int fillColor = g.fillColor;
      int strokeColor = g.strokeColor;
      
      fill(strokeColor);
      rect(arr.get(0),arr.get(1),arr.get(2),arr.get(3));
      fill(fillColor);

    } else if (_cmdName.equals("setbackcolor")) {
      //textBackColor =     
      int currentFillColor = g.fillColor;
      
      ArrayList<Integer> arr = getRGB();
      fill(arr.get(0),arr.get(3),arr.get(2),arr.get(3));
      fontBackColor = g.fillColor;
      fill(currentFillColor);

    } else if (_cmdName.equals("setcolor")) {
      ArrayList<Integer> arr = getRGB();
      
      int currentFillColor = g.fillColor;
      fill(arr.get(0),arr.get(3),arr.get(2),arr.get(3));
      fontColor = g.fillColor;
      fill(currentFillColor);
    } else if (_cmdName.equals("print")) {
       String text = (String)_args.get(0);
       int x = int((String)_args.get(1));   
       int y = int((String)_args.get(2));   
       
       int fillColor = g.fillColor;
       int strokeColor = g.strokeColor;
            
       fill(fontColor);
       text(text, x, y, 0);
       fill(fillColor);
       println("hellloooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");  
    }
  }
 
 
 int fontBackColor = 0;
 int fontColor = 0;
 
 
 
 
  
  private ArrayList<Integer> getRGB()
  {
    int red = int((String)_args.get(0));
    int green = int((String)_args.get(1));
    int blue = int((String)_args.get(2));

    ArrayList<Integer> arr = new ArrayList<Integer>();
    arr.add(red);
    arr.add(green);
    arr.add(blue);
    return arr;
 }


 private ArrayList<Integer> getXYWH()
  {
     int x = int((String)_args.get(0));   
     int y = int((String)_args.get(1));   
     int h = int((String)_args.get(2));   
     int w = int((String)_args.get(3));   

    ArrayList<Integer> arr = new ArrayList<Integer>();
    arr.add(x);
    arr.add(y);
    arr.add(h);
    arr.add(w);
    return arr;
 }
}
