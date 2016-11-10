package edu.wmich.cs3310.ADekau.A2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
/* A2
 * Setup.java
 * Alex Dekau
 * Last Modified: 10/12/2015
 */
public class Setup {
	public static void main(String[] args) throws IOException {
		UIoutput logWriter = new UIoutput("Log.txt", true);
		logWriter.displayThis("SETUP started");
		logWriter.displayThis("OPENED DataStorage file");
		DataStorage theData = new DataStorage("DataStorage.bin", logWriter);
		//Insert Countries into BST.
		BufferedReader reader = new BufferedReader(new FileReader("RawData2.csv"));
		RawData dataHandler = new RawData(reader);
		String line = "";
		while(dataHandler.canRead1Line()) {
			line = dataHandler.read1Line();
			CountryData dataToInsert = dataHandler.getImportantValues(line);
			theData.insert(dataToInsert, true);
		}
		logWriter.displayThis("SETUP finished inserted " + theData.n + " countries into DataStorage.");
		//End of Inserting Countries into BST
		theData.init();
		PrettyPrint.main(null);
		UserApp.main("TransData2a.txt", logWriter, theData);
		UserApp.main("TransData2b.txt", logWriter, theData);
		theData.init();
		theData.finishUp();
		logWriter.displayThis("CLOSED DataStorage file");
		
		logWriter.finishUp();
		PrettyPrint.main(null);
		
	}
}
