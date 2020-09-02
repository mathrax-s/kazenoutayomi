byte[] wavedata;
float[] wavedata_f;
float wave_ave;

void make_waveform(float wd, int export) {
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
    wave_ave = wave_ave*(1.0-div)+output*div;
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
      rect(x, 640, 1, map( r*wave_ave/128.0, 0, 127, 0, 255));

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
      int bwave = (int)map( r*wave_ave/128.0, -128, 127, -128, 127);
      wavedata[(int)x] = byte(bwave);
      wavedata_f[(int)x] = (r*wave_ave/128.0);

      break;
    }
  }
}
