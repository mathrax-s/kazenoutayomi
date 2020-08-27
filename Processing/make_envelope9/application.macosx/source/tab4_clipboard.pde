import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.StringSelection;
import java.awt.Toolkit;

void CopyToClipboard(String s)
{
  Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
  StringSelection data = new StringSelection(s);
  clipboard.setContents(data, data);
}
