package edu.wmich.cs3310.ADekau.A2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
/* A2
 * UserApp.java
 * Alex Dekau
 * Last Modified: 10/12/2015
 */
public class UserApp {
	public static void main(String fileName, UIoutput logWriter, DataStorage data) throws IOException {
		logWriter.displayThis("USERAPP started");
		BufferedReader reader = new BufferedReader(new FileReader(fileName));
		UIinput transactionHandler = new UIinput(reader, logWriter);
		String line = "";
		while (transactionHandler.caninput1Trans()) {
			line = transactionHandler.input1Trans();
			String[] transData = transactionHandler.handleSingleTransaction(line);
			switch (transData[0].charAt(0)) {
			case '%':
				break;
			case 'A':
				// Get all
				getAll(data, logWriter);
				break;
			case 'S':
				// Get 1
				getOne(transData[1], data, logWriter);
				break;
			case 'D':
				// delete
				deleteOne(transData[1], data, logWriter);
				break;
			case 'I':
				// insert
				insertOne(transData[1], data, logWriter);
			}
		}
		transactionHandler.finishUp();
		logWriter.displayThis("USERAPP finished");

	}
	// -------------------------------------------------------------------------------------
	private static void getAll(DataStorage data, UIoutput logWriter) throws IOException {
		logWriter.displayThis("A");
		String formattedString = "CDE ID- NAME-------------- CONTINENT---- ------AREA ---POPULATION LIFE";
		logWriter.displayThis(formattedString);
		data.getAll();
		logWriter.displayThis("===========================");
	}
	// -------------------------------------------------------------------------------------
	private static void getOne(String line, DataStorage data, UIoutput logWriter) throws IOException {
		CountryData selection = data.select(Short.parseShort(line));
		String formattedString = "";
		if(selection != null){
			logWriter.displayThis("S " + selection.getId() + " >>");
			formattedString = "CDE ID- NAME-------------- CONTINENT---- ------AREA ---POPULATION LIFE";
			logWriter.displayThis(formattedString);
			formattedString = String.format("%-3s %-3d %-18s %-13s %,10d %,13d %-4.1f",
					selection.getCode(), selection.getId(),
					selection.getName(), selection.getContinent(), selection.getArea(),
					selection.getPopulation(), selection.getLifeExpectancy());
			logWriter.displayThis(formattedString);
		}else{
			logWriter.displayThis("S " + Short.parseShort(line) + " >> invalid country id");
		}
	}
	// -------------------------------------------------------------------------------------
	private static void deleteOne(String line, DataStorage data, UIoutput logWriter) throws IOException {
		short id = Short.parseShort(line);
		String name = data.find(id) ? data.getName(id).trim() : "";
		if(data.delete(id)) {
			logWriter.displayThis("D " + id + " >> OK, " + name + " deleted");
		}else{
			logWriter.displayThis("D " + id + " >> invalid country id");
		}
	}
	// -------------------------------------------------------------------------------------
	private static void insertOne(String line, DataStorage data, UIoutput logWriter) throws IOException {
		short id = Short.parseShort(line.split(",")[1]);
		String[] splitData = line.split(",");
		CountryData newCountry = new CountryData(Short.parseShort(splitData[1]),
				splitData[0], splitData[2],
				splitData[3], Integer.parseInt(splitData[4]),
				Long.parseLong(splitData[5]), Float.parseFloat(splitData[6]));
		
		logWriter.displayThis("I " + id + " " + line );
		if(data.insert(newCountry, false)) {
			logWriter.displayThis(">> OK, " + data.padTruncate(line.split(",")[2], 18).trim() + " inserted");
		}else{
			logWriter.displayThis(">> invalid (duplicate) country id");
		}
	}

}
