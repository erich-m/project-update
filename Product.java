/*Author: Erich MacLean
CIS2430-0209
Title: Assignment 3
Project Folder: emacle05_a3
	Main and Classes:
		Assignment2.java
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

/**Product class
Fields:
String type for the product type that the extended child is
int productId is the product id for the intance of the product
String description is the description of the product
double is the double value for the price of the product
int year contains the product instances year*/
class Product {//product class has two children classes: electronic and book
	protected String type;//create protected product fields so that the children classes can access its parent fields to print the summary
	protected int productID;
	protected String description;
	protected double price;
	protected int year;

	/**Prodcuct constructor method initializes all the fields in the product
	@param typeIn string for product type
	@param idIn integer id
	@param descIn string description for product
	@param priceIn double product price
	@param yearIn integer product year
	@return no return type*/
	public Product (String typeIn, int idIn,String descIn,double priceIn, int yearIn){//product constructor class. Sets related fields. These fields are common between all products
		this.type = typeIn;
		this.productID = idIn;
		this.description = descIn;
		this.price = priceIn;
		this.year = yearIn;
	}

	/**toString converts the products data into a single string with formatting
	@param toFile signifies whether to include the summary line or not
	@return string with all field data*/
	public String toString(boolean toFile){//create a string with all the product details. Price is formatted to 2 decimal places, and id is formatted to 6 leading digits
		String details = "";
		details += "Type: <" + this.type + ">\n";
		details += String.format("Product ID: <%06d>\n",this.productID);
		details += "Description: <" + this.description + ">\n";
		details += String.format("Price: <%.2f>\n",this.price);
		details += "Year: <" + this.year + ">\n";

		return details;//return the concatenated string
	}

	/**compareYear takes an array with 2 integers and compares the values to the product intance year
	@param years is a size 2 int array that contains the 2 entered years
	@return true if the product year is within range*/
	public boolean compareYear(int[] years){//compare the given year to the two years given in the range (in the integer array)
		return (this.year >= years[0] && this.year <= years[1]);//year[0] is min year and year[1] is max year
	}

	/**compareID compares a given product id to the product instance id. if search is on, -1 will result as true
	@param id is the id to compare with the product id
	@param search determines whether to consider -1 as a true result
	@return boolean upon match of id (depending on search or no search)*/
	public boolean compareID(int id, boolean search){//takes an id and a search request
		if(search && id == -1){//if i am searching for products, then if the id is -1, return as true (because -1 is default)
			return true;
		}
		return (this.productID == id);//otherwise, compare normally
	}
}