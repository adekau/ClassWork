package edu.wmich.cs3310.ADekau.A2;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
/* A2
 * UIoutput.java
 * Alex Dekau
 * Last Modified: 09/28/2015
 */
public class UIoutput {
	// For Setup & UserApp programs
	private String outputFileName;
	BufferedWriter writer;
	//-------------------------------------------------------------------------------------
	public UIoutput(String outputFileName, boolean truncateMode) throws IOException {
		this.outputFileName = outputFileName;
		if(truncateMode) {
			writer = new BufferedWriter(new FileWriter(this.outputFileName));
			if(outputFileName.contains("Log")) {
				writer.write("OPENED Log file");
				writer.newLine();
			}
		}
	}
	//-------------------------------------------------------------------------------------
	public void displayThis(String text) throws IOException {
		writer.write(text);
		writer.newLine();
	}
	//-------------------------------------------------------------------------------------
	@Deprecated
	public void writeBackupHeader(int rootPtr, int n, int nextPtr) throws IOException {
		String formatted = String.format("%d,%d,%d", rootPtr, n, nextPtr);
		writer.write(formatted);
		writer.newLine();
	}
	//-------------------------------------------------------------------------------------
	public void finishUp() throws IOException {
		if(outputFileName.contains("Log")) {
			writer.write("CLOSED Log file");
			writer.newLine();
		}
		writer.close();
	}
}
