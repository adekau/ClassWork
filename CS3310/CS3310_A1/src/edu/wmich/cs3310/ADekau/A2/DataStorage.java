package edu.wmich.cs3310.ADekau.A2;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;
/* A2
 * DataStorage.java
 * Alex Dekau
 * Last Modified: 10/12/2015
 */
public class DataStorage {
	// Constants 
	private final int SIZE_OF_RECORD 	= 0x00000056; // 86
	private final int CODE_OFFSET 		= 0x00000002; // 2
	private final int NAME_OFFSET 		= 0x00000008; // 8
	private final int CONTINENT_OFFSET 	= 0x0000002C; // 44
	private final int AREA_OFFSET 		= 0x00000046; // 70 
	private final int POPULATION_OFFSET = 0x0000004A; // 74
	private final int LIFE_OFFSET 		= 0x00000052; // 82
	private final int REASONABLE_ID		= 0x0000003C;

	// Private class scope variables
	private String filename;
	private RandomAccessFile data;
	private UIoutput logWriter;
	public int n = 0, maxn = 0;
	// ---------------------------------------------------------------------------------------
	public DataStorage(String filename, UIoutput logWriter) throws IOException {
		this.filename = filename;
		this.logWriter = logWriter;
		BufferedWriter writer = new BufferedWriter(new FileWriter(this.filename));
		writer.close();
		this.data = new RandomAccessFile(new File(this.filename), "rw");
	}

	// ---------------------------------------------------------------------------------------
	public void init() throws IOException {
		data.seek(0);
		data.writeShort(n);
		data.seek(2);
		data.writeShort(maxn);
	}

	// ---------------------------------------------------------------------------------------
	// Insert function:
	// Must check if field already exists
	// Must truncate/pad data if it's too long
	public boolean insert(CountryData cData, boolean fromSetup) throws IOException {
		// Truncation
		String code 		= padTruncate(cData.getCode(), 3);
		String name 		= padTruncate(cData.getName(), 18);
		String continent	= padTruncate(cData.getContinent(), 13); 
		//Location to go to
		int loc = getLocation(cData.getId());
		// If it can find it, then produce an error message saying it can't insert
		// because of duplicate.
		if (find(cData.getId())) {
			if(fromSetup) {
				String disp = String.format("ERROR: DUPLICATE ID %d when inserting %s, %s has id %d",
						cData.getId(), cData.getName(), getName(cData.getId()).trim(), cData.getId());
				logWriter.displayThis(disp);
				return false;
			}else{
				return false;
			}
		} else if(cData.getId() == 0 || cData.getId() > REASONABLE_ID) {
			
			return false;
			
		}else{ // else insert a new record.
			if(loc > 0) {
				data.seek(loc);
				data.writeShort(cData.getId());
				data.seek(loc + CODE_OFFSET);
				data.writeChars(code);
				data.seek(loc + NAME_OFFSET);
				data.writeChars(name);
				data.seek(loc + CONTINENT_OFFSET);
				data.writeChars(continent);
				data.seek(loc + AREA_OFFSET);
				data.writeInt(cData.getArea());
				data.seek(loc + POPULATION_OFFSET);
				data.writeLong(cData.getPopulation());
				data.seek(loc + LIFE_OFFSET);
				data.writeFloat(cData.getLifeExpectancy());
				if(maxn == n) {maxn++;}
				n++;
				return true;
			}else{
				return false;
			}
		}
	}

	// ---------------------------------------------------------------------------------------
	// Find function:
	//
	public boolean find(int id) throws IOException {
		int loc = getLocation(id);
		if(!(loc >= data.length()) && loc > 0){ // prevent EOF
			data.seek(loc);
			return id == data.readShort();
		}else{
			return false; // would produce EOF, so record must not exist.
		}
	}
	// ---------------------------------------------------------------------------------------
	// Select function:
	public CountryData select(short id) throws IOException {
		if(find(id)){
			CountryData selection = new CountryData(id, getCode(id), getName(id), getContinent(id),
					getArea(id), getPopulation(id), getLifeExpectancy(id));
			return selection;
		}else{
			return null;
		}
	}
	
	// ---------------------------------------------------------------------------------------
	// Delete function:
	// Dynamic Delete. Records are ACTUALLY deleted..
	public boolean delete(int id) throws IOException {
		if(find(id)) {
			int loc = getLocation(id);
			for(int i = 0; i < SIZE_OF_RECORD; i++) {
				data.seek(loc + i);
				data.write(0x00);
			}
			--n;
			return true;
		}else{
			return false;
		}
	}

	// ---------------------------------------------------------------------------------------
	// getAll function:
	public void getAll() throws IOException {
		short id;
		String code = "", name = "", continent = "";
		int area = 0;
		long population = 0;
		float lifeExpectancy = 0;
		int i = 1;
		int loc = getLocation(i);
		
		while(loc < data.length()){
			data.seek(loc);
			id = data.readShort();
			if(id != 0){
				for(int z = 0; z < 3; z++) {
					code += data.readChar();
				}
				for(int z = 0; z < 18; z++) {
					name += data.readChar();
				}
				for(int z = 0; z < 13; z++) {
					continent += data.readChar();
				}
				area = data.readInt();
				population = data.readLong();
				lifeExpectancy = data.readFloat();
			
				String formattedString = String.format("%-3s %-3d %-18s %-13s %,10d %,13d %-4.1f",
						code, id, name, continent, area, population, lifeExpectancy);
				logWriter.displayThis(formattedString);
			}
			i++;
			code = "";
			name = "";
			continent = "";
			loc = getLocation(i);
		}
	}
	// ---------------------------------------------------------------------------------------
	public String padTruncate(String str, int length) {
		String paddedTruncatedString = str;
		
		if(str.length() < length){
			for(int i = 0; i < 18 - str.length(); i++) {
				paddedTruncatedString += " ";
			}
		}else if(str.length() > length) {
			paddedTruncatedString = paddedTruncatedString.substring(0, length);
		}
		return paddedTruncatedString;
	}
	
	// ---------------------------------------------------------------------------------------
	// finishUp function:
	public void finishUp() throws IOException {
		data.close();
	}
	// ---------------------------------------------------------------------------------------
	private int getLocation(int id) {
		return 4 + (SIZE_OF_RECORD * (id - 1));
	}
	// ---------------------------------------------------------------------------------------
	public String getCode(int id) throws IOException {
		int loc = getLocation(id) + CODE_OFFSET;
		data.seek(loc);
		String ret = "";
		for(int i = 0; i < 3; i ++) {
			ret += data.readChar();
		}
		return ret;
	}
	// ---------------------------------------------------------------------------------------
	public String getName(int id) throws IOException{
		int loc = getLocation(id) + NAME_OFFSET;
		data.seek(loc);
		String ret = "";
		for(int i = 0; i < 18; i++) {
			ret += data.readChar();
		}
		return ret;
	}
	// ---------------------------------------------------------------------------------------
	public String getContinent(int id) throws IOException{
		int loc = getLocation(id) + CONTINENT_OFFSET;
		data.seek(loc);
		String ret = "";
		for(int i = 0; i < 13; i++) {
			ret += data.readChar();
		}
		return ret;
	}
	// ---------------------------------------------------------------------------------------
	public int getArea(int id) throws IOException{
		int loc = getLocation(id) + AREA_OFFSET;
		data.seek(loc);
		int ret = data.readInt();
		return ret;
	}
	// ---------------------------------------------------------------------------------------
	public long getPopulation(int id) throws IOException{
		int loc = getLocation(id) + POPULATION_OFFSET;
		data.seek(loc);
		long ret = data.readLong();
		return ret;
	}
	// ---------------------------------------------------------------------------------------
	public float getLifeExpectancy(int id) throws IOException{
		int loc = getLocation(id) + LIFE_OFFSET;
		data.seek(loc);
		float ret = data.readFloat();
		return ret;
	}
}
