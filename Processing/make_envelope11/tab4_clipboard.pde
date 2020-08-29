import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.StringSelection;
import java.awt.Toolkit;

void CopyToClipboard(String s)
{
  Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
  StringSelection data = new StringSelection(s);
  clipboard.setContents(data, data);

  if (save_as_file==true) {
    selectOutput("Select a file to write to:", "fileSelected");
  }
}

String[] exportfile = {""};

void fileSelected(File selection) {
  if (selection == null) {
    println("Window was closed or the user hit cancel.");
  } else {
    println("User selected " + selection.getAbsolutePath());
    exportfile[0] = copy;
    saveStrings(selection.getAbsolutePath(), exportfile);
  }
}
