String[] data;
String[] export;
PrintWriter output;

void setup() {
  size(200, 200);
  data = loadStrings("data/log_curve.txt");
  output = createWriter("envelope.txt");
}

void draw() {
}

void mousePressed() {

  int[] b = new int[data.length];

  for (int i=0; i<data.length; i++) {
    int a=int(data[i]);
    b[i]=a;
    print(a);
    print(",");
    if (i!=0 && i%10==0)println();
    
    output.print(a);
    output.print(",");
    if (i!=0 && i%10==0)output.println();
  }
  
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
}
