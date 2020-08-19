int bcnt=5;
byte[][] raw = new byte[bcnt][0];
int[] envelope = new int[0];

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

public void ATTAK( ) {
  int ch=0;
  if (first[ch]==0) {
    first[ch]=1;
    raw[ch] = loadBytes("aogera-atk-sin8.raw");
  } else {
    selectInput("Select Raw-Signed 8bit File:", "attak_selected");

    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;
  }
}

void attak_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    int ch=0;
    raw[ch] = loadBytes(selection.getAbsolutePath());
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
    raw[ch] = loadBytes("aogera-sus-sin8.raw");
  } else {
    selectInput("Select Raw-Signed 8bit File:", "sustain_selected");

    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;
  }
}

void sustain_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    int ch=1;
    raw[ch] = loadBytes(selection.getAbsolutePath());
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
    raw[ch] = loadBytes("aogera-env-sin8.raw");
  } else {
    selectInput("Select Raw-Signed 8bit File:", "envelope_selected");

    for (int i=0; i<raw[ch].length; i++) {
      shorten(raw[ch]);
    }
    load_done[ch]=0;
  }
}

void envelope_selected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    int ch=2;
    raw[ch] = loadBytes(selection.getAbsolutePath());
    d[ch] = (raw[ch] .length/(float)width);
    load_done[ch]=1;
    index[ch]=0;
  }
}


public void EXPORT( ) {
  int ch=3;
  if (first[ch]==0) {
    first[ch]=1;
  } else {
    //export();
    //loadTemplate();
    //wavedata = new byte[40000];
    //make_waveform(10000, 1);
    //wave_export();
    //player = minim.loadSample("test.wav", 512);
  }
}

public void PREVIEW( ) {
  int ch=4;
  if (first[ch]==0) {
    first[ch]=1;
  } else {
    player.stop();
    player=null;
    wavedata = new byte[40000];
    make_waveform(10000, 1);
    wave_export();
    player = minim.loadSample("test.wav", 512);
    sound_preview();
  }
}


void export() {
  int w = 804;
  for (int h=0; h<2; h++) {
    //int h=0;
    s[h][0]="";
    c[h] = raw[h].length / w;
    for (int i=0; i<w; i++) {
      int a = raw[h][(int)(i*c[h])] ; 
      if (i==0) {
        s[h][0]+="\t";
      } else if (i%16==0) {
        s[h][0]+="\r\n\t";
      }
      s[h][0]+=a+",";//\t";
    }
    s[h][0]+="\r\n";
  }

  int e_length = 804;
  envelope = new int[e_length];
  int env_index = 0;
  float env_d = raw[2].length / e_length;
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
    ave = ave*(9.0/10.0)+output/10.0;
    envelope[i] = (int) ave;
  }
  w = e_length;
  s[2][0]="";
  c[2] = envelope.length  / w ;
  for (int i=0; i<w; i++) {
    int a = envelope[(int)(i*c[2])] ; 
    if (i==0) {
      s[2][0]+="\t";
    } else if (i%16==0) {
      s[2][0]+="\r\n\t";
    }
    s[2][0]+=a+",";//\t";
  }
  s[2][0]+="\r\n";
}

float div = 0.1;
float div2 = 1;

void draw_wave() {
  if (keyPressed) {
    if (key=='a') {
      div-=0.01;
      if (div<0.05)div=0.05;
    } else if (key=='s') {
      div+=0.01;
      if (div>1)div=1;
    }else if (key=='1') {
      div2-=0.01;
      if (div2<1)div2=1;
    } else if (key=='2') {
      div2+=0.01;
      if (div2>1.1)div2=1.1;
    }
  }
  for (int i=0; i<3; i++) {

    index[i]=0;

    d[i] = (raw[i] .length/((float)width));

    pushMatrix();
    translate(width/3*i, 0);
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

        average[i] = r;
        rectMode(CENTER);
        fill(wave_color1[i]);
        rect(x/3, 128, 1, (average[i]));
      }
    }
    popMatrix();
  }    

  for (int i=0; i<3; i++) {
    pushMatrix();
    translate(width/3*i, 0);
    fill(wave_text_color[i]);
    textAlign(CENTER, CENTER);
    text(wave_name[i], width/6, 20);
    popMatrix();
  }
  stroke(100);
  strokeWeight(1);
  line(0, 256, width, 256);
  line(0, 256*2, width, 256*2);

  pushMatrix();
  translate(width/2, 256+20);
  fill(50, 50, 100, 200);
  textAlign(CENTER, CENTER);
  text("WAVE1 : (Attack + Sustain + Sustain + Sustain .....)", 0, 0);
  popMatrix();

  pushMatrix();
  translate(width/2, 512+20);
  fill(50, 50, 100, 200);
  textAlign(CENTER, CENTER);
  text("WAVE2 : (WAVE1 * Envelope)", 0, 0);
  popMatrix();
}
