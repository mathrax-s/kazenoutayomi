import controlP5.*;
ControlP5 cp5;
RadioButton radio1;
int[] radio1_array={64, 128, 256, 512, 1024};


int dataNum = 10;
String[] preferences_saved;
String[] preferences;
String atk_file;
String sus_file;
String env_file;
boolean save_as_file=false;
float sliderTicks1_buf;
float sliderTicks2_buf;
int env_resolution = 0;
int POT = 8;
int ENVPOT = 8;


void save_preferences() {
  preferences_saved[0] = atk_file;
  preferences_saved[1] = sus_file;
  preferences_saved[2] = env_file;
  preferences_saved[3] = str(sliderTicks1);
  preferences_saved[4] = str(div2);
  preferences_saved[5] = str(sliderTicks2);
  preferences_saved[6] = str(save_as_file);
  preferences_saved[7] = str(env_resolution);
  preferences_saved[8] = str(POT);
  preferences_saved[9] = str(ENVPOT);
  saveStrings(dataPath("preferences.txt"), preferences_saved);
}

void load_preferences() {
  atk_file = preferences_saved[0];
  File f1 = new File(atk_file);
  if (!f1.exists()) {
    atk_file = dataPath("atk.raw");
  }
  sus_file = preferences_saved[1];
  File f2 = new File(sus_file);
  if (!f2.exists()) {
    sus_file =  dataPath("sus.raw");
  }    
  env_file = preferences_saved[2];
  File f3 = new File(env_file);
  if (!f3.exists()) {
    env_file = dataPath("env.raw");
  }    

  sliderTicks1_buf = float(preferences_saved[3]);
  div2 = float(preferences_saved[4]);
  sliderTicks2_buf = float(preferences_saved[5]);
  save_as_file = boolean(preferences_saved[6]);
  env_resolution = int(preferences_saved[7]);
  POT = int(preferences_saved[8]);
  ENVPOT = int(preferences_saved[9]);

}


void setup() {
  size(700, 768);

  String filename ="preferences.txt";
  File f = new File(dataPath(filename));
  if (f.exists()) {
    preferences_saved = loadStrings(dataPath("preferences.txt"));
    if (preferences_saved.length<dataNum) {
      preferences_saved = new String[dataNum];
      atk_file = dataPath("atk.raw");
      sus_file = dataPath("sus.raw");
      env_file = dataPath("env.raw");
      sliderTicks1 = 20;
      div2 = 1.0;
      sliderTicks2 = 0;
      save_as_file=false;
      env_resolution=1024;
      POT = 8;
      ENVPOT = 8;
    } else {
      load_preferences();
    }
  } else {
    preferences_saved = new String[dataNum];
    atk_file = dataPath("atk.raw");
    sus_file = dataPath("sus.raw");
    env_file = dataPath("env.raw");
    sliderTicks1 = 20;
    div2 = 1.0;
    sliderTicks2 = 0;
    save_as_file=false;
    env_resolution=1024;
    POT = 8;
    ENVPOT = 8;
    save_preferences();
  }


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
  cp5.addButton("EXPORT1")
    .setValue(0)
    .setPosition(width/6*2.5-50, height-60)
    .setSize(100, 30)
    ;
  cp5.addButton("EXPORT2")
    .setValue(0)
    .setPosition(width/6*3.5-50, height-60)
    .setSize(100, 30)
    ;
  cp5.addButton("PREVIEW")
    .setValue(0)
    .setPosition(width/6*5-50, height-60)
    .setSize(100, 30)
    ;
  cp5.addButton("SAVE_SET")
    .setValue(0)
    .setPosition(width/6*5+10, height/3*2+10)
    .setSize(80, 30)
    ;

  cp5.addButton("LOAD_SET")
    .setValue(0)
    .setPosition(width/6*5-90, height/3*2+10)
    .setSize(80, 30)
    ;

  cp5.addSlider("sliderTicks1")
    .setPosition(width/2-50, height/2+75)
    .setSize(100, 20)
    .setRange(0, 100)
    .setColorValue(0x444488ff)
    .setValue(sliderTicks1_buf);
  ;

  cp5.addSlider("div2")
    .setPosition(width/6*5-10, height/3*2+75)
    .setSize(20, 100)
    .setRange(1.0, 1.1)
    .setColorValue(0xffff88ff)
    ;

  cp5.addSlider("sliderTicks2")
    .setPosition(width/12, height-55)
    .setSize(100, 20)
    .setRange(-1, 1)
    .setColorValue(0xffff88ff)
    .setValue(sliderTicks2_buf);
  ;

  //println(save_as_file);
  cp5.addToggle("SAVE")
    .setPosition(width/2-25, height-height/8)
    .setSize(50, 20)
    .setValue(save_as_file)
    .setMode(ControlP5.SWITCH)
    .setColorLabel(0x444488ff)
    ;
  cp5.getController("SAVE").getCaptionLabel().align(ControlP5.CENTER, ControlP5.BOTTOM_OUTSIDE).setPaddingX(0);

  radio1 = cp5.addRadioButton("radioButton")
    .setPosition(width/2-60, height/3*2+40)
    .setSize(20, 20)
    .setColorForeground(color(120))
    .setColorActive(color(0, 200, 255))
    .setColorLabel(color(10, 10, 50))
    .setItemsPerRow(5)
    .setSpacingColumn(5)
    .addItem("64", 0)
    .addItem("128", 1)
    .addItem("256", 2)
    .addItem("512", 3)
    .addItem("1024", 4)
    ;

  for (Toggle t : radio1.getItems()) {
    t.getCaptionLabel().align(ControlP5.CENTER, ControlP5.BOTTOM_OUTSIDE);
    t.getCaptionLabel().setColorBackground(color(255, 80));
    t.getCaptionLabel().getStyle().moveMargin(-7, 0, 0, -3);
    t.getCaptionLabel().getStyle().movePadding(7, 0, 0, 3);
    t.getCaptionLabel().getStyle().backgroundWidth = 45;
    t.getCaptionLabel().getStyle().backgroundHeight = 13;
  }
  radio1.activate(env_resolution);

  cp5.addNumberbox("numberbox1")
    .setPosition(width/6-40, height/2+75)
    .setSize(20, 20)
    .setScrollSensitivity(1)
    .setValue(POT)
    .setMin(5)
    .setMax(15)
    .setColorLabel(color(10, 10, 50))
    .setLabel("POT")
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.BOTTOM_OUTSIDE);
  ;
  cp5.addNumberbox("numberbox2")
    .setPosition(width/6+40, height/2+75)
    .setSize(20, 20)
    .setScrollSensitivity(1)
    .setValue(ENVPOT)
    .setMin(5)
    .setMax(15)
    .setColorLabel(color(10, 10, 50))
    .setLabel("ENVPOT")
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.BOTTOM_OUTSIDE);
  ;
}

void controlEvent(ControlEvent theEvent) {
  if (theEvent.isFrom(radio1)) {
    env_resolution =  int(theEvent.getGroup().getValue());
    println(env_resolution);
  }
}

void numberbox1(int num) {
  POT = num;
}
void numberbox2(int num) {
  ENVPOT = num;
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
