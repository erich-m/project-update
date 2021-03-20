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
package eStoreSearch;//assignment 3 package

/**Book Product class
Fields (extends from the product class):
String authors contains the book authors
String publisher contains the book publisher*/
class Book extends Product{//create a book product
	private String authors;//create book specific fields
	private String publisher;

	/**constructor method for book class. Initializes product fields and book specific fields
	@param idIn integer product id to add
	@param descIn string product description
	@param priceIn double product price
	@param yearIn integer product year
	@param auhtorIn string is the book author field
	@param publishIn string is the book publisher field
	@return nothing*/
	public Book (String typeIn,int idIn, String descIn, double priceIn, int yearIn, String authorIn, String publishIn){//constructor class extends the product class. Sets all related fields
		super(typeIn,idIn,descIn,priceIn,yearIn);
		this.authors = authorIn;
		this.publisher = publishIn;
	}

	/**converts product data including book specific fieldss to a single string. Adds summary line based on boolean
	@param toFile boolean signals destination of string
	@return string of concatenated data*/
	@Override
	public String toString(boolean toFile){//override of the products tostring
		String details = super.toString(toFile);
		details += "Authors: <" + this.authors + ">\n";//append the related fields to the end of the string
		details += "Publisher: <" + this.publisher + ">\n\n";
		if(toFile){//if printing to a file, add summary line
			details += "Summary#/#" + super.type + "#/#" + super.productID + "#/#" + super.description + "#/#" + super.price + "#/#" + super.year + "#/#" + this.authors + " #/#" + this.publisher + " #/#\n\n";
		}
		return details;//return product details as a single string (multiple lines);
	}
}
