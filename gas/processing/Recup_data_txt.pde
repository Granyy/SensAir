import processing.serial.*;

Serial mySerial;

PrintWriter output;
String nameFile; 

void setup() {
  
  size(200,200);
  rect(10,10,180,180);
  fill(0);
  text("Press any key to stop", 30, 100);
  
  nameFile = str(day()) + "_" + str(month()) + "_" + str(year()) + "__" + str(hour()) + "_" + str(minute()) + "__data.txt"; 
  
   mySerial = new Serial( this, Serial.list()[0], 9600 );
   output = createWriter( nameFile );
}

void draw() {
  
    if (mySerial.available() > 0 ) {
         String value = mySerial.readString();
         if ( value != null ) {  
             output.print( value );
             print(value);
         }
    }
}

void keyPressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    println("Fichier créé");
    exit();  // Stops the program
}