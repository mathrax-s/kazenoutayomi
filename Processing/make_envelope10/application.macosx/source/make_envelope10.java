import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 
import java.awt.datatransfer.Clipboard; 
import java.awt.datatransfer.Transferable; 
import java.awt.datatransfer.StringSelection; 
import java.awt.Toolkit; 
import processing.sound.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class make_envelope10 extends PApplet {


ControlP5 cp5;

String[] preferences_saved;
String[] preferences;
String atk_file;
String sus_file;
String env_file;


public void save_preferences() {
  preferences_saved[0] = atk_file;
  preferences_saved[1] = sus_file;
  preferences_saved[2] = env_file;
  preferences_saved[3] = str(sliderTicks1);
  preferences_saved[4] = str(div2);
  preferences_saved[5] = str(sliderTicks2);
  saveStrings("data/preferences.txt", preferences_saved);
}

public void load_preferences() {
  atk_file = preferences_saved[0];
  sus_file = preferences_saved[1];
  env_file = preferences_saved[2];
  sliderTicks1 = PApplet.parseFloat(preferences_saved[3]);
  div2 = PApplet.parseFloat(preferences_saved[4]);
  sliderTicks2 = PApplet.parseFloat(preferences_saved[5]);
}


public void setup() {
  

  preferences_saved = loadStrings("data/preferences.txt");
  if (preferences_saved.length<6) {
    atk_file = "data/atk.raw";
    sus_file = "data/sus.raw";
    env_file = "data/env.raw";
    sliderTicks1 = 20;
    div2 = 1.0f;
    sliderTicks2 = 0;
  } else {
    load_preferences();
  }

  //minim = new Minim(this);  
 
 // out   = minim.getLineOut();
 // kick  = new Sampler( "test.wav", 4, minim );
 // kick.patch( out );
  

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
    .setPosition(width/6*2.5f-50, height-60)
    .setSize(100, 30)
    ;
  cp5.addButton("EXPORT2")
    .setValue(0)
    .setPosition(width/6*3.5f-50, height-60)
    .setSize(100, 30)
    ;
  cp5.addButton("PREVIEW")
    .setValue(0)
    .setPosition(width/6*5-50, height-60)
    .setSize(100, 30)
    ;

  cp5.addSlider("sliderTicks1")
    .setPosition(width/2-50, height/2+75)
    .setSize(100, 20)
    .setRange(0, 100)
    .setColorValue(0x444488ff)
    ;

  cp5.addSlider("div2")
    .setPosition(width/6*5, height/3*2+75)
    .setSize(20, 100)
    .setRange(1.0f, 1.1f)
    .setColorValue(0xffff88ff)
    ;

  //cp5.addSlider("sliderTicks2")
  //  .setPosition(width/12, height-55)
  //  .setSize(100, 20)
  //  .setRange(-1, 1)
  //  .setColorValue(0xffff88ff)
  //  ;
}


public void dispose() {

  save_preferences();
  println("save preferences");
}


public void draw() {
  background(255);
  draw_wave() ;
  make_waveform(width, 0);
  fill(0);
  text(emin,100,500);
  text(emax,100,550);
}
int bcnt=6;
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
int[] wave_text_color = {color(10, 0, 255, 200), color(50, 255, 1, 200), color(200, 0, 100, 200)};
int[] wave_color1 = {color(10, 0, 255, 40), color(50, 255, 1, 40), color(200, 0, 100, 20)};
int[] wave_color2 = {color(10, 0, 255, 80), color(50, 255, 1, 80), color(200, 0, 100, 40)};

float sliderTicks1 = 20;
float sliderTicks2 = 0;

  float emax = 0;
  float emin = 0;
  
public void ATTAK( ) {
  int ch=0;
  if (first[ch]==0) {
    first[ch]=1;
    raw[ch] = loadBytes(atk_file);
    make_atk = raw[0].length;
  } else {
    selectInput("Select Raw-Signed 8bit File:", "attak_selected");

    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;
  }
}

public void attak_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    int ch=0;
    atk_file = selection.getAbsolutePath();
    raw[ch] = loadBytes(atk_file);
    d[ch] = (raw[ch] .length/(float)width);
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

    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;
  }
}

public void sustain_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    int ch=1;
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

    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;
  }
}

public void envelope_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    int ch=2;
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
    //wave_export();
    //player = minim.loadSample("test.wav", 512);
    sound_preview();
  }
}


public void export() {
  int w;
  int h;

  //ATK
  h=0;
  w=804*5;
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
  int e_length = 1024;
  envelope = new float[e_length];
  //envelope_buf = new float[e_length];
  int env_index = 0;
  float env_d = raw[2].length / (float)e_length;


  for (int i=0; i<e_length; i++) {
    int e = raw[2][(int)env_index];
    env_index += env_d;
    inlet1 = e;
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

    envelope[i] = output*div2;
  }


  w = e_length;    //1024
  s[2][0]="";
  c[2] = envelope.length / (float)w;

   emax = max(envelope);
   emin = min(envelope);

  for (int i=0; i<w; i++) {
    int a = 0;
    int offset = (int)(i*c[2])+(int)(w*(-sliderTicks2));
    if ( offset >= w || offset <0) {
      a=0;
    } else {
      a = (int)map(envelope[offset], emin, emax, 0, 255);
    }
    if (i==0) {
      s[2][0]+="\t";
    } else if (i%16==0) {
      s[2][0]+="\r\n\t";
    }
    s[2][0]+=a+",";//\t";
  }
  s[2][0]+="\r\n";
}


float div = 0.1f;
float div2 = 1;

public void draw_wave() {
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
        ave = ave*(1.0f-div)+output*div;

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
String[] outputlines={""};
String[] lines;
String copy;
String[] pot1 = {"#define POT1\t"};
String[] envpot1 = {"#define ENVPOT1\t"};
String[] pot2 = {"#define POT2\t"};
String[] envpot2 = {"#define ENVPOT2\t"};

public void loadTemplate(int num) {
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





public void CopyToClipboard(String s)
{
  Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
  StringSelection data = new StringSelection(s);
  clipboard.setContents(data, data);
  
  selectOutput("Select a file to write to:", "fileSelected");
}

public void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    saveStrings(selection.getAbsolutePath() , outputlines);
  }
}
byte[] wavedata;
float[] wavedata_f;
float wave_ave;

public void make_waveform(float wd, int export) {
  float w = wd;

  ////全体の波形
  //make_atk = raw[0].length;
  //make_sus = raw[1].length;
  //make_env = raw[2].length;

  float make_wave = make_atk + make_sus*sliderTicks1;
  int d = (int)((float)(make_wave) / w);
  int env_d = (int)((float)(make_env) / w);

  float index_f=0;
  int index = 0;
  float env_index_f=0;
  int env_index=0;
  int wave_status=0;

  for (long x=0; x<w; x++) {

    float r=0;
    float env_r=0;

    //ATAK & SUSTAIN
    if (0 <= index && index <= make_atk-1) {
      r  = raw[0][index];
      wave_status=0;  //ATAK
    } else if (make_atk-1 < index && index <= make_wave) {
      r = raw[1][(index-(make_atk-1)) % make_sus];
      wave_status=1;  //SUSTAIN
    }

    //ENVELOPE
    if (env_index >= make_env) {
      env_index =  make_env-1;
    }
    //println(make_env, env_index, raw[2].length);
    env_r =abs(raw[2][env_index]);
    inlet1 = env_r;
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
    wave_ave = wave_ave*(1.0f-div)+output*div;
    wave_ave = wave_ave*div2;
    if (wave_ave>128)wave_ave=128;



    if (index <= (make_wave-1)) {
      index_f += d;
      index = (int)index_f;
    }

    if (env_index <= (make_env-env_d-1)) {
      env_index_f+=env_d;
      env_index =(int)env_index_f;
    }



    switch (export) {
      //画面表示
    case 0:
      //WAVE1
      rectMode(CENTER);
      noStroke();
      fill(wave_color2[wave_status]);
      rect(x, 384, 1, r);

      //WAVE2  
      rectMode(CENTER);
      noStroke();
      fill(wave_color2[wave_status]);
      rect(x, 640, 1, map( r*wave_ave/128.0f, 0, 127, 0, 255));

      rectMode(CENTER);
      stroke(200, 0, 100, 50);
      strokeWeight(4);
      point(x, 640-(wave_ave/2));

      stroke(0, 100, 200, 80);
      strokeWeight(2);
      point(x+(sliderTicks2*w), 640-(wave_ave/2));

      //strokeWeight(2);
      //stroke(0, 100, 200, 10);
      //if (w+(sliderTicks2*w)<w) {
      //    line(w+(sliderTicks2*w)+2, 640, w, 640);
      //} else if (w+(sliderTicks2*w)>0) {
      //    line(0, 640, (sliderTicks2*w), 640);
      //}
      break;



    case 1:     
      int bwave = (int)map( r*wave_ave/128.0f, -128, 127, -128, 127);
      wavedata[(int)x] = PApplet.parseByte(bwave);
      wavedata_f[(int)x] = (r*wave_ave/128.0f);

      break;
    }
  }
}
//import javax.sound.sampled.*;
//import java.io.*;
//AudioInputStream ais ;


//void wave_export() {
//  AudioFormat frmt = new AudioFormat(44100, 8, 1, true, true);
//  ais = new AudioInputStream(new ByteArrayInputStream(wavedata), frmt, wavedata.length / frmt.getFrameSize() );

//  try { 
//    AudioSystem.write(ais, AudioFileFormat.Type.WAVE, new File(sketchPath()+"/data/test.wav"));
//  } 
//  catch(Exception e) {
//    e.printStackTrace();
//  }
//}


AudioSample sample;

public void sound_preview() {
  
  int resolution = 4410;
  float[] sinewave = new float[resolution];
  for (int i = 0; i < wavedata_f.length; i++) {
    sinewave[i] = wavedata_f[i]*0.1f;
  }
  sample = new AudioSample(this, sinewave, 8000);

  sample.amp(0.1f);
  sample.play();
}
  public void settings() {  size(700, 768); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "make_envelope10" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
