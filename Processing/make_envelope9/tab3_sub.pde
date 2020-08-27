String[] outputlines={""};
String[] lines;
String copy;
String[] pot1 = {"#define POT1\t"};
String[] envpot1 = {"#define ENVPOT1\t"};
String[] pot2 = {"#define POT2\t"};
String[] envpot2 = {"#define ENVPOT2\t"};

void loadTemplate(int num) {
  outputlines=new String[0];
  switch(num) {
  default:
  case 1:
    lines = loadStrings("template1.txt");
    for (int i=0; i<lines.length; i++) {

      if (match(lines[i], "//pot1")!=null) {      
        int p = (int)(map(sliderTicks1, 20, 100, 12, 5));
        String[] p1 ={str(p)+"\r\n"};
        outputlines = concat(outputlines, concat(pot1, p1));
      } else if (match(lines[i], "//envpot1")!=null) {
        int ep = 8;//(int)(map(sliderTicks1, 20,100, 12,5));
        String[] ep1 ={str(ep)+"\r\n"};
        outputlines = concat(outputlines, concat(envpot1, ep1));
      } else if (match(lines[i], "//wt")!=null) {
        outputlines = concat(outputlines, s[0]);
      } else  if (match(lines[i], "//sus")!=null) {
        outputlines = concat(outputlines, s[1]);
      } else if (match(lines[i], "//env")!=null) {
        outputlines = concat(outputlines, s[2]);
      } else {
        outputlines = append(outputlines, lines[i]+"\r\n");
      }
    }
    break;

  case 2:
    lines = loadStrings("template2.txt");
    for (int i=0; i<lines.length; i++) {

      if (match(lines[i], "//pot2")!=null) {      
        int p = (int)(map(sliderTicks1, 20, 100, 12, 5));
        String[] p2 ={str(p)+"\r\n"};
        outputlines = concat(outputlines, concat(pot2, p2));
      } else if (match(lines[i], "//envpot2")!=null) {
        int ep = 8;//(int)(map(sliderTicks1, 20,100, 12,5));
        String[] ep2 ={str(ep)+"\r\n"};
        outputlines = concat(outputlines, concat(envpot2, ep2));
      } else if (match(lines[i], "//wt")!=null) {
        outputlines = concat(outputlines, s[0]);
      } else  if (match(lines[i], "//sus")!=null) {
        outputlines = concat(outputlines, s[1]);
      } else if (match(lines[i], "//env")!=null) {
        outputlines = concat(outputlines, s[2]);
      } else {
        outputlines = append(outputlines, lines[i]+"\r\n");
      }
    }
    break;
  }


  copy="";
  for (int i=0; i<outputlines.length; i++) {
    //println(outputlines[i]);
    copy += outputlines[i];
  }
  println(copy);
  CopyToClipboard(copy);
}
