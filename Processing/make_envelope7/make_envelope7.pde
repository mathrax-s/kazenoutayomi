import controlP5.*;
ControlP5 cp5;


void setup() {
  size(700, 768);
  minim = new Minim(this);
  player = minim.loadSample("test.wav", 512);

  background(255);
  noStroke();
  fill(255, 0, 0, 100);


  cp5 = new ControlP5(this);
  cp5.addButton("ATTAK")
    .setValue(0)
    .setPosition(width/6*1-50, 200)
    .setSize(100, 30)
    ;
  cp5.addButton("SUSTAIN")
    .setValue(0)
    .setPosition(width/6*3-50, 200)
    .setSize(100, 30)
    ;
  cp5.addButton("ENVELOPE")
    .setValue(0)
    .setPosition(width/6*5-50, 200)
    .setSize(100, 30)
    ;
  cp5.addButton("EXPORT")
    .setValue(0)
    .setPosition(width/6*3-50, height-60)
    .setSize(100, 30)
    ;
  cp5.addButton("PREVIEW")
    .setValue(0)
    .setPosition(width/6*5-50, height-60)
    .setSize(100, 30)
    ;

  cp5.addSlider("sliderTicks1")
    .setPosition(width/6*5, height/2-50)
    .setSize(20, 100)
    .setRange(20, 100)
    .setNumberOfTickMarks(5)
    ;
}

void draw() {
  background(255);
  draw_wave() ;
  make_waveform(width, 0);
}
