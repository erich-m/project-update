/*Author: Erich MacLean
CIS2430*0209
Lab Exercise 5
file: Lab5.java
GUI designed to implement all previous functions*/
package Lab5;

public class Student {
	//Declare all fields as protected
	protected String program;
	protected int year;
	protected String lastName;
	protected double average;

	public Student (String program, int yearIn,String lName,double averageIn) throws Exception{//throw the errors in the method and let the main method catch them
		this.program = program;//program name field
		this.lastName  = lName;//last name field
		if(yearIn < 0 || yearIn > 9999){//throw an error if the year is out of range
			throw new Exception("ERROR: The entered year is not in the correct range");
		}else{
			this.year = yearIn;
		}

		if(averageIn < 0 || averageIn > 100){//throw an error if the average is out of range
			throw new Exception("ERROR: The entered grade is not in the correct range");
		}else{
			this.average = averageIn;
		}
	}

	public String toString (int printText){//prints out the data for the student instance. Program name parameter allows to void the program name when printing
		String printOut = this.program + " " + this.year + " " + this.average + " " + this.lastName;
		if(printText == 2){
			printOut = (this.program).toLowerCase() + " " + this.year + " " + (this.lastName).toLowerCase();
		}
		return(printOut);

	}
	public double getaverage(){//accessor method for the average field
		return this.average;
	}
	public String getprogram(){//Accessor method for the program field
		return this.program;
	}
}