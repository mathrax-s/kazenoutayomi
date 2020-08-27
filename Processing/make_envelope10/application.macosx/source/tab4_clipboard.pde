import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.StringSelection;
import java.awt.Toolkit;

void CopyToClipboard(String s)
{
  Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
  StringSelection data = new StringSelection(s);
  clipboard.setContents(data, data);
  
  selectOutput("Select a file to write to:", "fileSelected");
}

void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    saveStrings(selection.getAbsolutePath() , outputlines);
  }
}
