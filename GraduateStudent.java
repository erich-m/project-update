/*Author: Erich MacLean
CIS2430*0209
Lab Exercise 5
file: Lab5.java
GUI designed to implement all previous functions*/
package Lab5;

class GraduateStudent extends Student{
	private String supervisor;
	private boolean isPhD;
	private String undergraduateSchool;

	public GraduateStudent (String program, int yearIn,String lName,double averageIn,String supervisorIn,int phd,String school) throws Exception{//throw any exceptions in the method and catch them in the main
		super(program,yearIn,lName,averageIn);//call the student constructor to create a graduate student intance
		this.supervisor = supervisorIn;
		if(phd == 0){//set phd status to false if int is 0, and status to true if int is 1
			this.isPhD = false;
		}else if(phd == 1){
			this.isPhD = true;
		}else{//throw an error if neither 1 or 0
			throw new Exception("ERROR: PhD should be either 1 (PhD) or 0 (Masters)");
		}
		this.undergraduateSchool = school;
	}

	@Override
	public String toString (int printText){//print text signals the desitination of the concatenatedd string
		String printOut = "";

		if(printText != 2){
			printOut = super.program + " " + super.year + " " + super.average;
			
			if(printText == 1 && this.isPhD){//print the text version of the phd status
				printOut += " " + this.supervisor + " PhD " + this.undergraduateSchool;
			}else if(printText == 1 && !this.isPhD){
				printOut += " " + this.supervisor + " Masters " + this.undergraduateSchool;
			}

			if(printText == 0 && this.isPhD){//print the number version of the phd status
				printOut += " " + this.supervisor + " 1 " + this.undergraduateSchool;
			}else if(printText == 0 && !this.isPhD){
				printOut += " " + this.supervisor + " 0 " + this.undergraduateSchool;
			}

			printOut += " " + this.lastName;
		}else{
			printOut = super.toString(printText);//if the printText is equal to 2, concat only the program name, year, and last name
		}
		return printOut;
	}
}