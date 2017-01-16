package kohill;

import java.awt.Container;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStream;
import java.io.Writer;

import javax.imageio.IIOException;
import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;

import java.awt.Color;
import javax.swing.JProgressBar;
import javax.swing.JPanel;
import java.awt.Cursor;
import java.awt.Rectangle;
import java.awt.ComponentOrientation;
import java.awt.Font;

public class Jfr implements ActionListener {
	File file;
	File toFile;

	JFrame frame = new JFrame("图片代码生成 正式版By kohillyang");
	JTabbedPane tabPane = new JTabbedPane();
	Container con = new Container();
	JLabel label2 = new JLabel("选择文件");
	JTextField text2 = new JTextField();
	JButton button2 = new JButton("...");
	JFileChooser jfc = new JFileChooser();
	JButton button3 = new JButton("\u751F\u6210\u4EE3\u7801");
	private JTextField textField;
	private JTextField textField_1;
	private JProgressBar progressBar;

	Jfr() {
		jfc.setCurrentDirectory(new File("C://Users/kohill/Desktop"));
		double lx = Toolkit.getDefaultToolkit().getScreenSize().getWidth();
		double ly = Toolkit.getDefaultToolkit().getScreenSize().getHeight();
		frame.setIconImage(Toolkit.getDefaultToolkit().getImage(Jfr.class.getResource("/com/sun/javafx/scene/control/skin/caspian/images/capslock-icon.png")));
		frame.setBounds(new Rectangle(10, 10, 10, 10));
		frame.setTitle("\u56FE\u7247\u4EE3\u7801\u751F\u6210\u5668 By kohillyang");
		frame.setLocation(new Point((int) (lx / 2) - 150, (int) (ly / 2) - 150));
		frame.setSize(471, 371);// 设定窗口大小
		tabPane.setBackground(new Color(0, 128, 0));
		frame.setContentPane(tabPane);
		label2.setBounds(12, 12, 70, 20);
		text2.setBounds(70, 12, 264, 20);
		button2.setBounds(346, 12, 76, 20);
		button3.setBounds(67, 65, 114, 57);
		button2.addActionListener(this); // 添加事件处理
		button3.addActionListener(this);
		con.setFont(new Font("仿宋", Font.PLAIN, 15));
		con.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
		con.setForeground(Color.YELLOW);
		con.setBackground(Color.DARK_GRAY);
		con.add(label2);
		con.add(text2);
		con.add(button2);
		con.add(button3);
		frame.setVisible(true);// 窗口可见
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 使能关闭窗口，结束程序
		tabPane.add("主页", con);// 添加布局1
		textField = new JTextField();
		textField.setCursor(Cursor.getPredefinedCursor(Cursor.TEXT_CURSOR));
		textField.setBounds(10, 145, 412, 146);
		con.add(textField);
		textField.setColumns(10);

		textField_1 = new JTextField();
		textField_1.setBounds(70, 33, 264, 20);
		con.add(textField_1);

		JLabel label = new JLabel("\u4FDD\u5B58\u4F4D\u7F6E");
		label.setBounds(12, 34, 70, 20);
		con.add(label);

		JButton button = new JButton("...");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {

				jfc.setFileSelectionMode(0);
				int state = jfc.showOpenDialog(null);
				if (state == 1) {
					return;
				} else {
					toFile = jfc.getSelectedFile();
					textField_1.setText(toFile.getAbsolutePath());
				}
			}
		});
		button.setBounds(346, 33, 76, 20);
		con.add(button);
		
		progressBar = new JProgressBar();
		progressBar.setStringPainted(true);
		progressBar.setBounds(225, 77, 164, 32);
		con.add(progressBar);
	}

	public void actionPerformed(ActionEvent e) {
		if (e.getSource().equals(button2)) {
			jfc.setFileSelectionMode(0);
			int state = jfc.showOpenDialog(null);
			if (state == 1) {
				return;
			} else {
				file = jfc.getSelectedFile();
				text2.setText(file.getAbsolutePath());
			}
		}

		if (e.getSource().equals(button3)) {
			progressBar.setValue(0);
			if (file != null)
				System.out.println(file.getAbsolutePath());
			try {
				BufferedImage bufferedImage = ImageIO.read(file);
				if ((bufferedImage.getWidth() % 8 != 0)
						| (bufferedImage.getWidth() > 128)
						|| (bufferedImage.getHeight() > 64))
					JOptionPane.showMessageDialog(null,
							"图片宽高" + bufferedImage.getWidth() + "*"
									+ bufferedImage.getHeight(), "提示", 2);
				int[][] array = PictureArray.pictureToArray(file, null);
				WriteArray.write(array, toFile,progressBar);
			} catch (IIOException e1) {
				JOptionPane.showMessageDialog(null, "文件未找到", "提示", 2);
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (Exception e2) {
				e2.printStackTrace();
				JOptionPane.showMessageDialog(null, "文件格式錯誤", "提示", 2);
			}
		}
	}

	public static void main(String[] args) {
		new Jfr();
	}
	public JProgressBar getProgressBar() {
		return progressBar;
	}
}
