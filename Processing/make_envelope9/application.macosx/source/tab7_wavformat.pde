import javax.sound.sampled.*;
import java.io.*;

import java.io.File;

int wavefile_num=0;

void wave_export() {
  AudioFormat frmt = new AudioFormat(44100, 8, 1, true, true);
  AudioInputStream ais = new AudioInputStream(
    new ByteArrayInputStream(wavedata), frmt, 
    wavedata.length / frmt.getFrameSize()
    );


  try { 
    //String fileName = dataPath("test.wav");
    //File f = new File(fileName);

    //if (f.exists()) {
    //  f.delete();
    //  println(fileName);
    //}

    wavefile_num++;
    if (wavefile_num>1) {
      wavefile_num=0;
    }
    AudioSystem.write(ais, AudioFileFormat.Type.WAVE, new File(sketchPath()+"/data/test.wav"));
  } 
  catch(Exception e) {
    e.printStackTrace();
  }
}
