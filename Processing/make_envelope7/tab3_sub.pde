String[] outputlines={""};
String[] lines;
String copy;

void loadTemplate() {
  lines = loadStrings("template.txt");
  for (int i=0; i<lines.length; i++) {

    if (match(lines[i], "//wt")!=null) {
      outputlines = concat(outputlines, s[0]);
    } else  if (match(lines[i], "//sus")!=null) {
      outputlines = concat(outputlines, s[1]);
    } else if (match(lines[i], "//env")!=null) {
      outputlines = concat(outputlines, s[2]);
    } else {
      outputlines = append(outputlines, lines[i]+"\r\n");
    }
  }

  copy="";
  for (int i=0; i<outputlines.length; i++) {
    //println(outputlines[i]);
    copy += outputlines[i];
  }
  println(copy);
  CopyToClipboard(copy);
}
