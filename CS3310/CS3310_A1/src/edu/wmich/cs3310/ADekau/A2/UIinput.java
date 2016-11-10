package edu.wmich.cs3310.ADekau.A2;

import java.io.BufferedReader;
import java.io.IOException;
/* A2
 * UIinput.java
 * Alex Dekau
 * Last Modified: 09/28/2015
 */
public class UIinput {
	private BufferedReader reader;
	private String line;
	private UIoutput logWriter;
	//-------------------------------------------------------------------------------------
	public UIinput(BufferedReader reader, UIoutput logWriter) throws IOException {
		this.reader = reader;
		this.logWriter = logWriter;
		logWriter.displayThis("OPENED TransData file.");
	}
	//-------------------------------------------------------------------------------------
	public boolean caninput1Trans() throws IOException {
		line = reader.readLine();
		return line != null;
	}
	//-------------------------------------------------------------------------------------
	public String input1Trans() throws IOException {
		return line;
	}
	//-------------------------------------------------------------------------------------
	public String[] handleSingleTransaction(String line) throws IOException {
		char firstCharOfLine = line.charAt(0);
		line = line.length() >= 3 ? line.substring(2) : "";
		String[] data = {String.valueOf(firstCharOfLine), line};
		return data;
	}
	//-------------------------------------------------------------------------------------
	public void finishUp() throws IOException {
		logWriter.displayThis("CLOSED TransData file.");
		reader.close();
	}
}
