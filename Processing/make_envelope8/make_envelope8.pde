import controlP5.*;
ControlP5 cp5;

String[] preferences_saved;
String[] preferences;
String atk_file;
String sus_file;
String env_file;


void save_preferences() {
  preferences_saved[0] = atk_file;
  preferences_saved[1] = sus_file;
  preferences_saved[2] = env_file;
  preferences_saved[3] = str(sliderTicks1);
  preferences_saved[4] = str(div2);
  saveStrings("data/preferences.txt", preferences_saved);
}

void load_preferences() {
  atk_file = preferences_saved[0];
  sus_file = preferences_saved[1];
  env_file = preferences_saved[2];
  sliderTicks1 = float(preferences_saved[3]);
  div2 = float(preferences_saved[4]);
}



void setup() {
  size(700, 700);

  preferences_saved = loadStrings("data/preferences.txt");
  if (preferences_saved.length<5) {
    atk_file = "data/atk.raw";
    sus_file = "data/sus.raw";
    env_file = "data/env.raw";
    sliderTicks1 = 20;
    div2 = 1.0;
  } else {
    load_preferences();
  }

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
    .setRange(0, 100)
    //.setNumberOfTickMarks(100)
    ;

  cp5.addSlider("div2")
    .setPosition(width/6*5, height/3*2+75)
    .setSize(20, 100)
    .setRange(0, 2)
    //.setNumberOfTickMarks(1000)
    ;
}


void dispose() {
  save_preferences();
  println("save preferences");
}


void draw() {
  background(255);
  draw_wave() ;
  make_waveform(width, 0);
}
