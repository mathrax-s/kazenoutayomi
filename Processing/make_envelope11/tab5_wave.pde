byte[] wavedata;
float[] wavedata_f;
float env_ave;
float[] envelope_buf2;

void make_waveform(float wd, int export) {
  float w = wd;

  float make_wave = make_atk + make_sus*sliderTicks1;
  int d = (int)((float)(make_wave) / w);
  int env_d = (int)((float)(make_env) / w);

  float index_f=0;
  int index = 0;
  float env_index_f=0;
  int env_index=0;
  int wave_status=0;
  envelope_buf = new float[int(wd)];
  envelope_buf2 = new float[int(wd)];
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
    env_ave = env_ave*(1.0-div)+output*div;
    env_ave = env_ave*div2;
    if (env_ave>127)env_ave=127;

    if (index <= (make_wave-1)) {
      index_f += d;
      index = (int)index_f;
    }

    if (env_index <= (make_env-env_d-1)) {
      env_index_f+=env_d;
      env_index =(int)env_index_f;
    }


    int a=0;
    float b=0;
    int c=0;

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
      rect(x, 640, 1, map( r*env_ave/127.0, 0, 127, 0, 255));

      rectMode(CENTER);
      stroke(0, 100, 200, 10);
      strokeWeight(4);
      point(x, 640-(env_ave/2));

      stroke(200, 0, 100, 80);
      strokeWeight(2);
      point(x+(sliderTicks2*w), 640-(env_ave/2));
      envelope_buf[int(x)] = env_ave;

       a = int(sliderTicks2*w) ;
       b =0 ;
       c=0;
      if (a<=0) {
        c = int(x)+abs(a);
        if (c <= envelope_buf.length-1) {
          b=env_ave;
        } else {
          b=0;
        }
      } else {
        c= int(x)-a;
        if (c<0) {
          b=0;
        } else {
          b=env_ave;
        }
      }
      envelope_buf2[int(x)] = b;

      break;


    case 1:     
      int bwave = int(map( r*env_ave/127.0, -128, 127, -128, 127));
      wavedata[int(x)] = byte(bwave);

      envelope_buf[int(x)] = env_ave;
      a = int(sliderTicks2*w) ;
      b =0 ;
      c=0;
      if (a<=0) {
        c = int(x)+abs(a);
        if (c <= envelope_buf.length-1) {
          b=env_ave;
        } else {
          b=0;
        }
      } else {
        c= int(x)-a;
        if (c<0) {
          b=0;
        } else {
          b=env_ave;
        }
      }
      //envelope_buf2[int(x)] = b;
      
      wavedata_f[int(x)] = (r*b /127.0);  //for PREVIEW sound live
      break;
    }
  }

  int a = int(sliderTicks2*w) ;
  float b =0 ;
  int c=0;
  for (int i=0; i<envelope_buf.length; i++) {
    if (a<=0) {
      c = i+abs(a);
      if (c <= envelope_buf.length-1) {
        b=envelope_buf[c];
      } else {
        b=0;
      }
    } else {
      c= i-a;
      if (c<0) {
        b=0;
      } else {
        b=envelope_buf[c];
      }
    }
    envelope_buf2[i] = b;
  }

  emax = max(envelope_buf2);
  emin = min(envelope_buf2);
  fill(0);
  text(emin, 100, 500);
  text(emax, 100, 550);
  //text(a, 100, 580);
}
