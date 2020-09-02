PImage[] image = new PImage[5];
PImage backgroundImage;
PImage tori_light1;
int cellSize=1;
EqTriangle[] tri = new EqTriangle[4];

int myX, myY;
int tWidth=58;

int[] now_r = new int[120];
int[] now_g = new int[120];
int[] now_b = new int[120];

int[] next_r = new int[120];
int[] next_g = new int[120];
int[] next_b = new int[120];

int[] diff_r = new int[120];
int[] diff_g = new int[120];
int[] diff_b = new int[120];

int[] set_r = new int[120];
int[] set_g = new int[120];
int[] set_b = new int[120];

int[] pixelColor = new int[120];


int count=0;
int nextCount = count+1;
int framePreScale;
float maxPreScale=30;
float lineCount;

int sendCount=-1;

void setup() {
  size(800, 680); 
  colorMode(RGB);
  backgroundImage = loadImage("back_black.png");
  //image[0] = loadImage("tsutaL_30x4.png");
  image[0] = loadImage("hane_L_120x4.png");
  tori_light1 = loadImage("tori_light1.png");

  noSmooth();
  frameRate(60);

  myX = width/2;
  myY = 350;//height/4*2;

  tri[0] = new EqTriangle("light1.png", 79, 0);
  tri[1] = new EqTriangle("light2.png", 268, 0);
  tri[2] = new EqTriangle("light3.png", 358, 0);
  tri[3] = new EqTriangle("light4.png", 462, 0);


  noStroke();

  image[0].loadPixels();
  for (int i=0; i<image[0].height; i++) {
    pixelColor[i] = image[0].pixels[i*image[0].width+count];

    now_r[i]=(pixelColor[i]>>16)&0xFF;
    now_g[i]=(pixelColor[i]>>8)&0xFF;
    now_b[i]=(pixelColor[i])&0xFF;

    pixelColor[i] = image[0].pixels[i*image[0].width+nextCount];
    next_r[i]=(pixelColor[i]>>16)&0xFF;
    next_g[i]=(pixelColor[i]>>8)&0xFF;
    next_b[i]=(pixelColor[i])&0xFF;


    if (now_r[i]>=255)now_r[i]=254;
    if (now_g[i]>=255)now_g[i]=254;
    if (now_b[i]>=255)now_b[i]=254;

    if (next_r[i]>=255)next_r[i]=254;
    if (next_g[i]>=255)next_g[i]=254;
    if (next_b[i]>=255)next_b[i]=254;
  }
}



void draw() {

  background(10);
  imageMode(CORNER);
  tint(200, 200, 255, 20);
  image(  backgroundImage, 0, 0);
  framePreScale++;

  if (framePreScale>maxPreScale) {
    framePreScale=0;

    image[0].loadPixels();

    count++;

    if (count<(image[0].width-1)) {
      nextCount = count+1;
    } else if (count>(image[0].width-1)) {
      count=0;
      nextCount = count+1;
    } else if (count==(image[0].width-1)) {
      nextCount = 0;
    }


    for (int i=0; i<image[0].height; i++) {
      pixelColor[i] = image[0].pixels[i*image[0].width+count];

      now_r[i]=(pixelColor[i]>>16)&0xFF;
      now_g[i]=(pixelColor[i]>>8)&0xFF;
      now_b[i]=(pixelColor[i])&0xFF;

      pixelColor[i] = image[0].pixels[i*image[0].width+nextCount];
      next_r[i]=(pixelColor[i]>>16)&0xFF;
      next_g[i]=(pixelColor[i]>>8)&0xFF;
      next_b[i]=(pixelColor[i])&0xFF;


      if (now_r[i]>=255)now_r[i]=255;
      if (now_g[i]>=255)now_g[i]=255;
      if (now_b[i]>=255)now_b[i]=255;

      if (next_r[i]>=255)next_r[i]=255;
      if (next_g[i]>=255)next_g[i]=255;
      if (next_b[i]>=255)next_b[i]=255;
    }
  }
  tint(220, 210, 100, 50);
  image(tori_light1, 104, 114);

  imageMode(CORNER);
  tint(255);
  image(image[0], 0, 600, 800, 80);


  lineCount = framePreScale*((nextCount*(640/image[0].width)-count*(640/image[0].width))/maxPreScale);
  stroke(255, 0, 0);
  line(count*(width/image[0].width)+lineCount, 600, count*(width/image[0].width)+lineCount, 680);

  for (int i=0; i<image[0].height; i++) {
    diff_r[i] = next_r[i] - now_r[i];
    diff_g[i] = next_g[i] - now_g[i];
    diff_b[i] = next_b[i] - now_b[i];

    set_r[i] = (int)(now_r[i] + framePreScale*(diff_r[i]/maxPreScale));
    set_g[i] = (int)(now_g[i] + framePreScale*(diff_g[i]/maxPreScale));
    set_b[i] = (int)(now_b[i] + framePreScale*(diff_b[i]/maxPreScale));
  }

  colorPreview();

}

void mousePressed() {
  saveData();
}


void colorPreview() {
  for (int i=0; i<4; i++) {
    tri[i].drawImg(color(set_r[i], set_g[i], set_b[i]));
  }
}

void saveData() {
  String[] lines = new String[image[0].height];

  int r;
  int g;
  int b;
  color pcolor;

  for (int j=0; j<image[0].width; j++) {
    for (int i=0; i<image[0].height; i++) {
      pcolor = image[0].pixels[i*image[0].width+j];

      r=(pcolor>>16)&0xFF;
      g=(pcolor>>8)&0xFF;
      b=(pcolor)&0xFF;

      if (r>=255)r=255;
      if (g>=255)g=255;
      if (b>=255)b=255;

      if (j==0) {
        lines[i] = (r<<16) + (g<<8) + b + ",";
      } else {
        lines[i] += (r<<16) + (g<<8) + b + ",";
      }
    }
  }

  saveStrings("data/points.txt", lines);
  ;
}
