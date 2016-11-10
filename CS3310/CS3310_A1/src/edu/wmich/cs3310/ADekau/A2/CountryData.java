package edu.wmich.cs3310.ADekau.A2;
/* A2
 * CountryData.java
 * Alex Dekau
 * Last Modified: 10/11/2015
 */
public class CountryData {
	private short id;
	private String code, name, continent;
	private int area;
	private long population;
	private float lifeExpectancy;
	//-------------------------------------------------------------------------------------
	public CountryData(short id, String code, String name, String continent, int area, 
			long population, float lifeExpectancy) {
		this.id = id;
		this.code = code;
		this.name = name;
		this.continent = continent;
		this.area = area;
		this.population = population;
		this.lifeExpectancy = lifeExpectancy;
	}
	//-------------------------------------------------------------------------------------
	public CountryData(String formattedString) {
		String[] data = formattedString.split(",");
		this.id = Short.parseShort(data[0]);
		this.code = data[1];
		this.name = data[2];
		this.continent = data[3];
		this.area = data[4].equalsIgnoreCase("NULL") ? 0 : Integer.parseInt(data[4]);
		this.population = data[5].equalsIgnoreCase("NULL") ? 0 : Long.parseLong(data[5]);
		this.lifeExpectancy = data[6].equalsIgnoreCase("NULL") ? 0 : Float.parseFloat(data[6]);
	}
	//---------------------------------GETTERS---------------------------------------------
	public short getId() {
		return this.id;
	}
	//-------------------------------------------------------------------------------------
	public String getCode() {
		return this.code;
	}
	//-------------------------------------------------------------------------------------
	public String getName() {
		return this.name;
	}
	//-------------------------------------------------------------------------------------
	public String getContinent() {
		return this.continent;
	}
	//-------------------------------------------------------------------------------------
	public int getArea() {
		return this.area;
	}
	//-------------------------------------------------------------------------------------
	public long getPopulation() {
		return this.population;
	}
	//-------------------------------------------------------------------------------------
	public float getLifeExpectancy() {
		return this.lifeExpectancy;
	}
	//---------------------------------SETTERS---------------------------------------------
	public void setId(short id) {
		this.id = id;
	}
	//-------------------------------------------------------------------------------------
	public void setName(String name) {
		this.name = name;
	}
	//-------------------------------------------------------------------------------------
	public void setCode(String code) {
		this.code = code;
	}
	//-------------------------------------------------------------------------------------
	public void setContinent(String continent) {
		this.continent = continent;
	}
	//-------------------------------------------------------------------------------------
	public void setArea(int area) {
		this.area = area;
	}
	//-------------------------------------------------------------------------------------
	public void setPopulation(long population) {
		this.population = population;
	}
	//-------------------------------------------------------------------------------------
	public void setLifeExpectancy(float lifeExpectancy) {
		this.lifeExpectancy = lifeExpectancy;
	}
	//-------------------------------------------------------------------------------------
	public String toString() {
		return String.format("ID: %2d  Code: %3s  Name: %-18s  Continent: %-13s Area: %10d  Population: %20d  LifeExpectancy: %10f", 
				getId(), getCode(), getName(), getContinent(), getArea(), getPopulation(),
				getLifeExpectancy());
	}
}