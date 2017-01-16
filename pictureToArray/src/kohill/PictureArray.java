package kohill;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JProgressBar;

public class PictureArray implements Runnable {
	File file;
	File toFile;
	JProgressBar progressBar;
	boolean isend =false;
	int pictureToArray[][];
	PictureArray(File file,JProgressBar progressBar,File tofile){
		this.file = file;
		this.progressBar = progressBar;
		this.isend = false;
		this.toFile= tofile;
	}
	
	public static int[][] pictureToArray(File file, JProgressBar progressBar)
			throws IOException {
		BufferedImage bufferedImage = ImageIO.read(file);
		int width = bufferedImage.getWidth();
		int height = bufferedImage.getHeight();
		int minx = bufferedImage.getMinX();
		int miny = bufferedImage.getMinY();
		int pictureArray[][] = new int[height + (height % 8)][width];
		for (int i = minx; i < height; i++) {
			for (int j = miny; j < width; j++) {
				int rgb = bufferedImage.getRGB(j, i);
				int r = (rgb & 0xff0000) >> 16;
				int g = (rgb & 0xff00) >> 8;
				int b = (rgb & 0xff);
				if ((r + g + b) / 3 > 128) {
					pictureArray[i][j] = 0;
				} else {
					pictureArray[i][j] = 1;
				}
			}
		}

		height += (height % 8);
		int pictureToArray[][] = new int[height / 8][width];
		for (int k = 0; k < height / 8; k++) {
			for (int j = 0; j < width - 1; j++) {
				pictureToArray[k][j] = 0;
				for (int i = 0; i < 8; i++) {
					pictureToArray[k][j] += ((int) Math.pow(2, i))
							* pictureArray[i + 8 * k][j];
				}

			}
		}
		return pictureToArray;
	}

	public void run() {
		try {
			pictureToArray = pictureToArray(file, progressBar);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		WriteArray writeArrayThread = new WriteArray(pictureToArray, toFile,progressBar);
		writeArrayThread.run();		
		isend = true;		
	}
	int[][] getpictureToArray(){
		return pictureToArray;
	};
	boolean hasBeenEnd(){
		return isend;
	}
}
