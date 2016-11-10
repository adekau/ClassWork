//##!! IMPORTANT:
// This class needs to be adjusted to meet the specifications:
//----------------------------------------------------------------------------------
/*record split into individual fields by private cleanup and setter methods
 *individual field data available to Setup by public getter methods
 *only a SINGLE record (and a single set of fields) is needed within the class since
 *a NEW record can over-write the
----------------------------------------------------------------------------------*/

package edu.wmich.cs3310.ADekau.A2;

import java.io.BufferedReader;
import java.io.IOException;
/* A2
 * RawData.java
 * Alex Dekau
 * Last Modified: 10/12/2015
 */
public class RawData {
	private BufferedReader reader;
	private String line;
	// -------------------------------------------------------------------------------------
	public RawData(BufferedReader reader) throws IOException {
		this.reader = reader;
	}

	// -------------------------------------------------------------------------------------
	public boolean canRead1Line() throws IOException {
		line = reader.readLine();
		return  line != null;
	}
	// -------------------------------------------------------------------------------------
	public String read1Line() throws IOException {
		return line;
	}
	// -------------------------------------------------------------------------------------
	public CountryData getImportantValues(String line) throws IOException {
		String newLine;
		String[] lineCsv;
		lineCsv = line.split(",");
		newLine = lineCsv[0] + "," + lineCsv[1] + "," + lineCsv[2] + "," + lineCsv[3] + "," + lineCsv[5] + ","
				+ lineCsv[7] + "," + lineCsv[8];
		CountryData country = new CountryData(newLine);
		return country;
	}
	// -------------------------------------------------------------------------------------
	public void finishUp() throws IOException {
		reader.close();
	}
}
