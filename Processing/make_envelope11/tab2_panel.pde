int bcnt=8;
byte[][] raw = new byte[bcnt][0];
float[] envelope = new float[0];
float[] envelope_buf = new float[0];
int[] attack = new int[0];
int[] sustain = new int[0];

int[] first = new int[bcnt];
float[]  d = new float[bcnt];
int[] load_done= new int[bcnt];
float[] index= new float[bcnt];

String[][] s = new String[bcnt][1];
float[] c = new float[bcnt];

float inlet1;
float inlet2;
float output;
int mode = 0;
float ave;
float[]average = new float[bcnt];

int make_atk;
int make_sus;
int make_env;

String make_s = null ;
String make_c ;
String[] wave_name = {"Attack", "Sustain", "Envelope"};
color[] wave_text_color = {color(10, 0, 255, 200), color(50, 255, 1, 200), color(200, 0, 100, 200)};
color[] wave_color1 = {color(10, 0, 255, 40), color(50, 255, 1, 40), color(200, 0, 100, 20)};
color[] wave_color2 = {color(10, 0, 255, 80), color(50, 255, 1, 80), color(200, 0, 100, 40)};

float sliderTicks1 = 20;
float sliderTicks2 = 0;

float emax = 0;
float emin = 0;

float div = 0.1;
float div2 = 1;


public void ATTAK( ) {
  int ch=0;
  if (first[ch]==0) {
    first[ch]=1;
    raw[ch] = loadBytes(atk_file);
    make_atk = raw[0].length;
  } else {
    selectInput("Select Raw-Signed 8bit File:", "attak_selected");
  }
}

void attak_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());

    int ch=0;

    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;

    atk_file = selection.getAbsolutePath();
    raw[ch] = loadBytes(atk_file);
    d[ch] = (raw[ch] .length/float(width));
    load_done[ch]=1;
    index[ch]=0;
    make_atk = raw[ch].length;
  }
}

public void SUSTAIN( ) {
  int ch=1;
  if (first[ch]==0) {
    first[ch]=1;
    raw[ch] = loadBytes(sus_file);
    make_sus = raw[1].length;
  } else {
    selectInput("Select Raw-Signed 8bit File:", "sustain_selected");
  }
}

void sustain_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    int ch=1;
    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;

    sus_file = selection.getAbsolutePath();
    raw[ch] = loadBytes(sus_file);
    d[ch] = (raw[ch] .length/(float)width);
    load_done[ch]=1;
    index[ch]=0;
    make_sus = raw[ch].length;
  }
}


public void ENVELOPE( ) {
  int ch=2;
  if (first[ch]==0) {
    first[ch]=1;
    raw[ch] = null;
    raw[ch] = loadBytes(env_file);
    make_env = raw[2].length;
  } else {
    selectInput("Select Raw-Signed 8bit File:", "envelope_selected");
  }
}

void envelope_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    int ch=2;

    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;

    env_file = selection.getAbsolutePath();
    raw[ch] = loadBytes(env_file);
    d[ch] = (raw[ch] .length/(float)width);
    load_done[ch]=1;
    index[ch]=0;
    make_env = raw[2].length;
  }
}


public void EXPORT1( ) {
  int ch=3;
  if (first[ch]==0) {
    first[ch]=1;
  } else {
    export();
    loadTemplate(1);
  }
}

public void EXPORT2( ) {
  int ch=4;
  if (first[ch]==0) {
    first[ch]=1;
  } else {
    export();
    loadTemplate(2);
  }
}

public void PREVIEW( ) {
  int ch=5;
  if (first[ch]==0) {
    first[ch]=1;
  } else {
    wavedata = new byte[4410];
    wavedata_f = new float[4410];
    make_waveform(4410, 1);
    sound_preview();
  }
}

public void SAVE_SET( ) {
  int ch=6;
  if (first[ch]==0) {
    first[ch]=1;
  } else {
    selectOutput("Select a file to write to:", "savesetSelected");
  }
}

void savesetSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
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
    saveStrings(selection.getAbsolutePath(), preferences_saved);
  }
}

public void LOAD_SET( ) {
  int ch=7;
  if (first[ch]==0) {
    first[ch]=1;
  } else {
    selectInput("Select a file to write to:", "loadsetSelected");
  }
}
void loadsetSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    preferences_saved = loadStrings(selection.getAbsolutePath());


    if (preferences_saved.length!=dataNum) {
    } else {
      load_preferences();


      for (int ch=0; ch<2; ch++) {
        for (int i=0; i<raw[ch].length; i++) {
          shorten(raw[ch]);
        }
        load_done[ch]=0;
        if (ch==0) {
        } else if (ch==1) {
        } else if (ch==2) {
        }

        raw[ch] = loadBytes(atk_file);
        d[ch] = (raw[ch] .length/float(width));
        load_done[ch]=1;
        index[ch]=0;
        make_atk = raw[ch].length;
      }
    }
    //println(atk_file);
    //println(sus_file);
    //println(env_file);
    cp5.getController("sliderTicks1").setValue(sliderTicks1_buf);
    cp5.getController("sliderTicks2").setValue(sliderTicks2_buf);
    cp5.getController("div2").setValue(div2);
    radio1.activate(env_resolution);
  }
}


public void SAVE(boolean theFlag) {
  if (theFlag==true) {
    save_as_file=true;
    cp5.getController("SAVE").setLabel("SAVE");
  } else {
    save_as_file=false;
    cp5.getController("SAVE").setLabel("NOT SAVE");
  }
  //println(save_as_file);
}


void export() {
  int w;
  int h;

  //ATK
  h=0;
  w=804*7;
  if (w>10000)w=10000;
  s[h][0]="";
  c[h] = raw[h].length / (float)w;
  attack = new int[w];
  for (int i=0; i<w; i++) {
    int a = raw[h][(int)(i*c[h])] ; 
    attack[i]=a;
  }
  int amin=min(attack);
  int amax=max(attack);
  for (int i=0; i<w; i++) {
    int a = (int)map(attack[i], amin, amax, -127, 127); 
    if (i==0) {
      s[h][0]+="\t";
    } else if (i%16==0) {
      s[h][0]+="\r\n\t";
    }
    s[h][0]+=a+",";//\t";
  }
  s[h][0]+="\r\n";

  //SUS
  h=1;
  w = 804;  //fix
  s[h][0]="";
  c[h] = raw[h].length / (float)w;
  sustain = new int[w];
  for (int i=0; i<w; i++) {
    int a = raw[h][(int)(i*c[h])] ; 
    sustain[i]=a;
  }
  int smin=min(sustain);
  int smax=max(sustain);
  for (int i=0; i<w; i++) {
    int a = (int)map(sustain[i], smin, smax, -127, 127); 
    if (i==0) {
      s[h][0]+="\t";
    } else if (i%16==0) {
      s[h][0]+="\r\n\t";
    }
    s[h][0]+=a+",";//\t";
  }
  s[h][0]+="\r\n";



  //ENV
  int e_length = radio1_array[env_resolution];
  envelope = new float[e_length];
  float env_index = 0;
  float env_d=0;
  //if (envelope_buf2.length<e_length) {
  //env_d = envelope_buf2.length / float(e_length);
  //} else {
  //env_d = float(e_length) / envelope_buf2.length;
  env_d = envelope_buf2.length / float(e_length);
  //}
  for (int i=0; i<e_length; i++) {
    int e = int(envelope_buf2[int(env_index)]);
    env_index += env_d;
    envelope[i] = e;
  }

  s[2][0]="";
  c[2] = envelope.length / float(w);

  emax = max(envelope);
  emin = min(envelope);

  for (int i=0; i<e_length; i++) {
    int a = 0;

    a = (int)map(envelope[i], emin, emax, 0, 255);

    if (i==0) {
      s[2][0]+="\t";
    } else if (i%16==0) {
      s[2][0]+="\r\n\t";
    }
    s[2][0]+=a+",";//\t";
  }
  s[2][0]+="\r\n";
}








void draw_wave() {
  for (int i=0; i<3; i++) {

    //WAVE NAME
    pushMatrix();
    translate(width/3*i, 0);
    fill(wave_text_color[i]);
    textAlign(CENTER, CENTER);
    text(wave_name[i], width/6, 20);
    popMatrix();

    pushMatrix();
    translate(width/3*i, 0);
    index[i]=0;
    d[i] = (raw[i] .length/((float)width));

    for (int x=0; x<width; x++) {
      int r = raw[i] [(int)index[i]];

      index[i] +=d[i];

      //envelope
      if (i==2) {
        inlet1 = r;
        //サンプルホールド（現在値が以前より大きくなったとき）
        if (inlet1 >= inlet2) {
          mode = 1;    //上昇
        } else {
          if (mode==1) {
            mode = -1;  //下降
            output = (inlet2);
            if (output<0) {
              output=0;
            }
          }
        }

        inlet2 = inlet1;
        ave = ave*(1.0-div)+output*div;

        //読み込んだ波形
        rectMode(CENTER);
        fill(200, 0, 100, 100);
        rect(x/3, 128, 1, (ave));
      } else {
        //ATAK , SUSTAIN
        average[i] = r;
        rectMode(CENTER);
        noStroke();
        fill(wave_color1[i]);
        rect(x/3, 128, 1, (average[i]));
      }
    }
    popMatrix();
  }    


  stroke(100);
  strokeWeight(1);
  line(0, 256, width, 256);

  pushMatrix();
  translate(width/2, 256+20);
  fill(50, 50, 100, 200);
  textAlign(CENTER, CENTER);
  text("WAVE1 : (Attack + Sustain + Sustain + Sustain .....)", 0, 0);
  popMatrix();

  stroke(100);
  strokeWeight(1);  
  line(0, 256*2, width, 256*2);

  pushMatrix();
  translate(width/2, 512+20);
  fill(50, 50, 100, 200);
  textAlign(CENTER, CENTER);
  text("WAVE2 : (WAVE1 * Envelope)", 0, 0);
  popMatrix();
}
