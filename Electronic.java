/*Author: Erich MacLean
CIS2430-0209
Title: Assignment 3
Project Folder: 
	Main and Classes:
		Assignment3.java
		EStoreSearch.java
		Product.java
		Book.java 
		Electronic.java

	JUnit: 
		a3Test.java

	Sample Data:
		data.txt
Due: November 9th, 2020, 11:59pm
Submitted: November 8th, 2020, 1:15pm*/
package eStoreSearch;//assignmnet 3 package

/**electronic class extends from product class
Fields:
String maker contains the electornic maker*/
class Electronic extends Product{//create an electronic product
	private String maker;//electronic specific field

	/**electronic constructor method extends product class. initializes all fields
	@param idIn integer product id to add
	@param descIn string product description
	@param priceIn double product price
	@param yearIn integer product year
	@param maker string electronic maker field
	@return nothing*/
	public Electronic(String typeIn, int idIn, String descIn, double priceIn, int yearIn,String makerIn){//constructor class extends the product class. Sets all the related fields
		super(typeIn,idIn,descIn,priceIn,yearIn);
		this.maker = makerIn;
	}

	/**converts product data including electronic specific fieldss to a single string. Adds summary line based on boolean
	@param toFile boolean signals destination of string
	@return string of concatenated data*/
	@Override
	public String toString(boolean toFile){//to string takes all the fields and compiles it into a single string (multiple lines)
		String details = super.toString(toFile);//overrides the product toString function
		details += "Maker: <" + this.maker + ">\n\n";
		if(toFile){//if the string is for a file, print a product summary line (used for reading in)
			details += "Summary#/#" + super.type + "#/#" + super.productID + "#/#" + super.description + "#/#" + super.price + "#/#" + super.year + "#/#" + this.maker + " #/#\n\n";
		}
		return details;//return new string 
	}
}
