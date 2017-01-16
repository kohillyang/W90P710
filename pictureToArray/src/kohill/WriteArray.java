package kohill;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JPopupMenu;
import javax.swing.JProgressBar;

public class WriteArray implements Runnable {
	WriteArray(int [][]array,File file,JProgressBar progressBar){
	}
	
	static int write(int [][]array,File toFile,JProgressBar progressBar){
		String temp = "";
		for (int j = 0; j < array.length; j++) {
			temp = temp + "{";
			for (int i = 0; i < array[0].length; i++) {
				temp = temp + array[j][i];
				if (i < array[0].length - 1)
					temp +=',';
			}
			temp = temp + "}\n";
		}
		FileWriter fw = null;

		try {
			if (!toFile.exists()) {
				toFile.createNewFile();
			}
			fw = new FileWriter(toFile);
			BufferedWriter out = new BufferedWriter(fw);
			progressBar.setValue(50);
			out.write(temp, 0, temp.length() - 1);
			out.close();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		return 0;
		
	}
	public void run() {

	}

}
