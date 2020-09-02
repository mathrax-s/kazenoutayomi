class EqTriangle { // equilateral triangle
  PImage img1;
  float x, y;
  public EqTriangle(String filename, int x, int y) {
    this.x = x;
    this.y = y;
    img1 = loadImage(filename);
  }

  public void drawImg(color col1) {

    pushMatrix();
    imageMode(CORNER);
    translate(this.x, this.y);
    tint(col1,200);
    image(img1, 0, 0);
    popMatrix();
  }
}
