//PROGRAM: PrettyPrint
//AUTHOR: J.G.
//DESCRIPTION:This program is a developer's utility which reads/prints the Backup file,
//		showing it (nicely) in the Log file. NOTE: It does NOT display the internal BST, per se!
//		The program has no idea that the data in the Backup file is actually a BST - the program
//		just thinks it's a series of data records.
//		The program just opens, reads/writes and closes Backup.csv and Log.txt files itself
//		since it's PP not OOP.


package edu.wmich.cs3310.ADekau.A2;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.File;
import java.text.NumberFormat;
import java.io.RandomAccessFile;


public class PrettyPrint {
    private static File logFile;
    private static BufferedWriter log;
    private static RandomAccessFile file;
    private static final int SIZE_OF_SHORT=2;
    private static final int SIZE_OF_INT=4;
    private static final int SIZE_OF_LONG=8;
    private static final int SIZE_OF_CHAR=2;
    private static final int SIZE_OF_FLOAT=4;
    private static final int LENGTH_OF_CODE = 3;
    private static final int LENGTH_OF_NAME = 18;
    private static final int LENGTH_OF_CONTINENT = 13;
    private static int SIZE_OF_CODE=LENGTH_OF_CODE*SIZE_OF_CHAR;
    private static int SIZE_OF_NAME=LENGTH_OF_NAME*SIZE_OF_CHAR;
    private static final int SIZE_OF_ID=SIZE_OF_SHORT;
    private static int SIZE_OF_CONTINENT=LENGTH_OF_CONTINENT*SIZE_OF_CHAR;
    private static final int SIZE_OF_POPULATION=SIZE_OF_LONG;
    private static final int SIZE_OF_AREA=SIZE_OF_INT;
    private static final int SIZE_OF_LE=SIZE_OF_FLOAT;
    private static final int SIZE_OF_HEADER=2*SIZE_OF_SHORT;
    private static int SIZE_OF_RECORD = -10;
    
    private static final boolean PRINT_EMPTY = true;        //Turning this off will make it attempt to print even if it finds the record empty
    private static final boolean DISPLAY_EMPTY = true;      //Turn this off to completly hide empty enteries, making it function as showAll().
    private static final boolean SINGLE_BYTE_CHARS = false; //Turn this on if you are using single-byte                 -- UNTESTED, though it should work.
    private static final boolean UTF_STRINGS = false;       //Turn this on if you used writeUTF() to write your strings -- UNTESTED! Please email me if this does not work!
    private static final boolean HIDE_HEX = false;          //Turn this on to hide the hexcode location printouts
    private static final boolean TURN_IN_MODE = true;      //Turn this on when you are running the run you will print out - it will remove the byte catagory, as well as forcing DISPLAY_EMPTY and PRINT_EMPTY to true
    
    public static void main (String [] args){
        //
        //IF YOU HAVE ANY QUESTIONS OR ISSUES, PLEASE CONTACT ME AT devlin.t.grasley@wmich.edu
        //
        if(SINGLE_BYTE_CHARS){
            SIZE_OF_CODE /=2;
            SIZE_OF_NAME /=2;
            SIZE_OF_CONTINENT /=2;
        }
        if(UTF_STRINGS){
            SIZE_OF_CODE++;
            SIZE_OF_NAME++;
            SIZE_OF_CONTINENT++;
        }
        SIZE_OF_RECORD = SIZE_OF_ID+SIZE_OF_CODE+SIZE_OF_NAME+SIZE_OF_CONTINENT+SIZE_OF_AREA+SIZE_OF_POPULATION+SIZE_OF_LE;
        File innerFile = new File("DataStorage.bin");
        logFile=new File("Log.txt");
        try{
                file = new RandomAccessFile(innerFile,"r");
                log = new BufferedWriter(new FileWriter (logFile,true));
                
                int location = 1;
                short id = 0;
                String code = "";
                String name = "";
                String continent = "";
                int area = 0;
                long population = 0;
                float life = 0.0f;
                int n = 0;
                int maxID = 0;
                int numberOfBlanks = 0;
                int numberOfRecords = 0;
                long startingPointer =0;
                int deletedStillHasData = 0; // Experimental, untested
                
                file.seek(0);
                n = file.readShort();
                maxID = file.readShort();
                    
                out(String.format("%n====================%n"));
                out(String.format("PRETTYPRINT STARTED!%n"));
                out(String.format("N is %d Max ID is %d%n%n",n,maxID));
                String b = "";
                if(!(TURN_IN_MODE||HIDE_HEX)){
                    b=String.format("%-4.4s|",rightPad("Byte",4,'-'));
                }
                out(String.format(b+"%-3.3s> %-3.3s %-3.3s %-18.18s %-13.13s %11.11s %13.13s %4.4s%n",rightPad("Loc",3,'-'),rightPad("CDE", 3,'-'),rightPad("ID", 3,'-'),rightPad("NAME", 18,'-'),rightPad("CONTINENT", 13,'-'),leftPad("AREA", 11, '-'),leftPad("POPULATION",13,'-'),leftPad("LIFE",4,'-')));
                while(file.length()>getLoc(location)){
                    
                    startingPointer = file.getFilePointer();
                    id=readShort();
                    code=readString(LENGTH_OF_CODE);
                    name=readString(LENGTH_OF_NAME);
                    continent=readString(LENGTH_OF_CONTINENT);
                    area=readInt();
                    population=readLong();
                    life=readFloat();
                    
                b = "";
                if(!(TURN_IN_MODE||HIDE_HEX)){
                    b=String.format("%-4.4s|",leftPad(getHex(startingPointer),4,'0'));
                }
                    if(id == 0 && ((PRINT_EMPTY&&DISPLAY_EMPTY)||TURN_IN_MODE)){
                        numberOfBlanks++;
                        out(b+String.format("%03d> %s %n",location, "EMPTY"));
                    }else if ((id!=0) || ((!PRINT_EMPTY && DISPLAY_EMPTY)||TURN_IN_MODE)){
                        numberOfRecords++;
                        out(String.format(b+"%03d> %-3.3s %03d %-18.18s %-13.13s ",location, code,id,name,continent)+String.format("%11.11s %13.13s %4.4s %n",NumberFormat.getIntegerInstance().format(area),NumberFormat.getIntegerInstance().format(population),life));
                    }
                    if(id == 0 && population!=0){
                        deletedStillHasData++;
                    }
                    location++;
                }
                if(!TURN_IN_MODE){
                    out(String.format("Number of deleted files still containing data: %d%nNumber of records:       %d%nNumber of blank records: %d%nN correct:               %b%nMax ID correct:          %b%n",deletedStillHasData,numberOfRecords,numberOfBlanks,n==numberOfRecords,(numberOfRecords+numberOfBlanks)==maxID));
                }
                out(String.format("====================%n%n"));
                file.close();
                log.close();
        }catch (Exception e){
            System.out.println("[ERROR] Dude, something went wrong!\n"+e);
            e.printStackTrace();
        }
    }
    public static String getHex (long input){
        if(input >= 16){
            int output = (int) input%16;
            return getHex((input-output)/16)+getHexDigit(output);
        }
        return ""+getHexDigit((int)input);
    }
    
    public static char getHexDigit(int i){
        switch (i){
            case(0):
                return '0';
            case(1):
                return '1';
            case(2):
                return '2';
            case(3):
                return '3';
            case(4):
                return '4';
            case(5):
                return '5';
            case(6):
                return '6';
            case(7):
                return '7';
            case(8):
                return '8';
            case(9):
                return '9';
            case(10):
                return 'A';
            case(11):
                return 'B';
            case(12):
                return 'C';
            case(13):
                return 'D';
            case(14):
                return 'E';
            case(15):
                return 'F';
            default:
                return '?';
        }
    }
    
    private static void out (String s){
        log(s);
        System.out.print(s);
    }
    
    private static void log (String s){
        try{
            log.write(s);
        }catch (Exception e){
            System.err.println("[ERROR] Dude, Something broke!\n"+e);
            e.printStackTrace();
        }
    }
    
    private static String rightPad (String s, int n, char c){
        if( s.length()<n){
            for(int i=s.length();i<n;i++){
                s+=c;
            }
        }
        return s;
    }
    private static String leftPad (String s, int n, char c){
        if( s.length()<n){
            for(int i=s.length();i<n;i++){
                s=c+s;
            }
        }
        return s;
    }
    
    
    private static int getLoc (int ID){
        //IDs start at 1
        return (SIZE_OF_RECORD*(ID-1))+SIZE_OF_HEADER;
    }
    
    public static short readShort(int location){
            try{
                if(location < file.length()){
                    file.seek(location);
                    return file.readShort();
                }else{
                    return -1;
                }
            }catch (Exception e){
                System.out.println(e);
                e.printStackTrace();
                return -2;
            }
    }    
    public static int readInt(){
            try{
                    return file.readInt();
            }catch (Exception e){
                System.out.println(e);
                e.printStackTrace();
                return -2;
            }
    }    
    public static float readFloat(){
            try{
                    return file.readFloat();
            }catch (Exception e){
                System.out.println(e);
                e.printStackTrace();
                return -2;
            }
    }    
    public static short readShort(){
            try{
                    return file.readShort();
            }catch (Exception e){
                System.out.println(e);
                e.printStackTrace();
                return -2;
            }
    }    
    public static long readLong(){
            try{
                    return file.readLong();
            }catch (Exception e){
                System.out.println(e);
                e.printStackTrace();
                return -2;
            }
    }   
    public static char readChar(){
        if(!SINGLE_BYTE_CHARS){
            try{
                char c =file.readChar();
                    return c;
            }catch (Exception e){
                System.out.println(e);
                e.printStackTrace();
                return ' ';
            }
        }else{
            try{
                char c =(char)file.read();
                    return c;
            }catch (Exception e){
                System.out.println(e);
                e.printStackTrace();
                return ' ';
            }
        }
        
    }   
    public static String readString (int length){
        if(UTF_STRINGS){
            try{
            return file.readUTF();
            }catch(Exception e){
                return "";
            }
        }
        String s="";
        try{
        }catch (Exception e){
        }
        for(int i = 0;i<length;i++){
            s+=readChar();
        }
        try{
        }catch (Exception e){
        }
        return s;
    }    

}
