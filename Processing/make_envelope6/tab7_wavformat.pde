import javax.sound.sampled.*;
import java.io.*;
 
void wave_export() {
  //byte[] pcm_data = new byte[wd];
 
  
  //for (int i=0; i<pcm_data.length; i++) {
  //  //pcm_data[i] = (byte)(55*Math.sin((i/L1)*Math.PI*2));
  //}

  AudioFormat frmt = new AudioFormat(44100, 8, 1, true, true);
  AudioInputStream ais = new AudioInputStream(
    new ByteArrayInputStream(wavedata), frmt, 
    wavedata.length / frmt.getFrameSize()
    );

  try {
    AudioSystem.write(ais, AudioFileFormat.Type.WAVE, new File(sketchPath()+"/data/test.wav"));
  } 
  catch(Exception e) {
    e.printStackTrace();
  }
}
