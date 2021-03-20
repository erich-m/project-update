/*Author: Erich MacLean
CIS2430-0209
Title: Assignment 3
Project Folder: 
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

//import awt,awt.event and swing for grapics
//import util and io for other read/write related functions
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.io.*;

//Assignment 3 class is an extension of JFrame in order to run the subsequent code as a gui
public class Assignment3 extends JFrame{//define main class
	//define constants used through the program
	private static final int WIDTH = 600;//initial window size
	private static final int HEIGHT = 800;

	private static final int SCROLL_ROWS = 600;//set scroll window size
	private static final int SCROLL_COLS = 75;

	private static final int BORDER_T = 20;//set border sizes
	private static final int BORDER_L= 20;
	private static final int BORDER_B = 20;
	private static final int BORDER_R = 20;

	private static final int CHARS_PER_LINE = 15;//set default characters per line

	private static final int MIN_YEAR = 1000;//set min and max years
	private static final int MAX_YEAR = 9999;

	private static final String[] TYPES = {"book","electronic"};//set product types

	private static String fileName = "";//make a global file name for reading and writing

	private static EStoreSearch eStore = new EStoreSearch();//make a global eStore instance

	private JPanel initial;//Create the 3 root panels for the gui
	private JPanel addPanel;
	private JPanel searchPanel;

	private JTextArea messageDisplay;//global d3efine text areas for message display
	private JTextArea searchMessageDisplay;


	private JComboBox<String> typeBox;//create global add product fields 
	private JTextField addIdBox;
	private JTextField addDescBox;
	private JTextField addPriceBox;
	private JTextField addYearBox;

	private JLabel authMakerLabel;//create global label for the author/maker field (rather than changing the visibility and putting it in the same spot, I can change the author/maker label and hide the publisher panel)
	private JTextField addAuthMakerBox;

	private JPanel addPublisherPanel;//make publisher panel global
	private JTextField addPublisherBox;


	private JTextField searchIdBox;//make search fields global
	private JTextField searchDescBox;
	private JTextField searchSYearBox;
	private JTextField searchFYearBox;

	//SaveOnExit is an extension of window listener
	//listens for window closing in order to save the data to the given file on exit
	private class SaveOnExit extends WindowAdapter{
		/**windowClosing uses WindowEvent to detect closing window to save to output file*/
		public void windowClosing(WindowEvent e){
			//System.out.println("Save");
			try{
				//System.out.println("Saving Product Data");//provide user with progress updates
				PrintWriter fw = new PrintWriter(fileName,"UTF-8");
				String [] allData = eStore.printProducts();
				for(int d = 0;d < allData.length;d++){//prints each field on a separate line as well as a single line product summary
					fw.println(allData[d]);
				}
				//System.out.println("Successfully Saved " + allData.length + " Products\n");
				fw.close();
			}catch(Exception err){//catch file io exceptions
				//System.out.println("ERROR: Output to " + fileName + " failed");
			}
			//System.out.println("Exiting Store");
		}
	}

	//addProductListener is linked to the command menu add option
	//all text fields are reset (except for the message display)
	private class addProductListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			//System.out.println("Add");
			//reset all text fields
			typeBox.setSelectedIndex(0);
			addIdBox.setText("");
			addDescBox.setText("");
			addPriceBox.setText("");
			addYearBox.setText("");
			addAuthMakerBox.setText("");
			addPublisherBox.setText("");

			searchPanel.setVisible(false);//change panel display
			initial.setVisible(false);
			addPanel.setVisible(true);
		}
	}

	//searchProductListener is linked to the command menu search option
	//all text fields are reset except for the search result display
	private class searchProductListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			//System.out.println("Search");
			//reset text fields
			searchIdBox.setText("");
			searchDescBox.setText("");
			searchSYearBox.setText(Integer.toString(MIN_YEAR));
			searchFYearBox.setText(Integer.toString(MAX_YEAR));

			initial.setVisible(false);//change panel display
			addPanel.setVisible(false);
			searchPanel.setVisible(true);
		}
	}

	//quitListener is linked to the command menu quit option
	//saves the current data to the output file upon exit
	private class quitListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			try{
				//System.out.println("Saving Product Data");//provide user with progress updates
				PrintWriter fw = new PrintWriter(fileName,"UTF-8");
				String [] allData = eStore.printProducts();
				for(int d = 0;d < allData.length;d++){//prints each field on a separate line as well as a single line product summary
					fw.println(allData[d]);
				}
				//System.out.println("Successfully Saved " + allData.length + " Products\n");
				fw.close();
			}catch(Exception err){//catch file io exceptions
				//System.out.println("ERROR: Output to " + fileName + " failed");
			}
			//System.out.println("Exiting Store");
			System.exit(0);
		}
	}

	//addAddListener is linked to the add button on the add panel
	//verfies some of the data before adding it to the store
	private class addAddListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			//System.out.println("Add Product");
			if(!(messageDisplay.getText()).equals("")){
				messageDisplay.setText(messageDisplay.getText() + "\nAdding product______________________________________________\n");
			}else{
				messageDisplay.setText(messageDisplay.getText() + "Adding product______________________________________________\n");
			}
			//set defualt values
			int productID = -1;;
			String desc = "";
			double price = 0;
			int year = 0;
			String authMaker = "";
			String publisher = "";

			boolean error = false;//keeps track of errors 
			try{//try to parse the data. If errors, exceptions are thrown
				if(!(cleanString(addIdBox.getText(),true,0)).equals("") && !(cleanString(addDescBox.getText(),true,0)).equals("") && !(cleanString(addYearBox.getText(),true,0)).equals("")){//make sure the three required fields are filled
					if((cleanString(addIdBox.getText(),true,0)).length() == 6 && (cleanString(addIdBox.getText(),true,0)).matches("[0-9]+")){//checks that the id is correct
						productID = Integer.parseInt(cleanString(addIdBox.getText(),true,0));
					}else{
						throw new Exception("Please make sure the product has an ID, Decription and Year\n");//throw exception if id is incorrect format
					}
					desc = cleanString(addDescBox.getText(),true,0);//set description

					if(!(cleanString(addPriceBox.getText(),true,0)).equals("")){//check if price is entered
						String parsePrice = cleanString(addPriceBox.getText(),true,0);if((cleanString(addPriceBox.getText(),true,0)).length() > 3){//check if length is greater than 3 (.00)
							if((cleanString(addPriceBox.getText(),true,0)).contains(".") && (cleanString(addPriceBox.getText(),true,0)).charAt((cleanString(addPriceBox.getText(),true,0)).length() - 3) != '.'){//check format of price
								throw new Exception("Entered Price not formatted correctly. Default 0.00\n");
							}
						}else{
							if((cleanString(addPriceBox.getText(),true,0)).contains(".")){//if length is less than or equal to 3, znd still contains a decimal, then throw exception
								throw new Exception("Entered Price not formatted correctly. Default 0.00\n");
							}
						}
						price = Double.parseDouble(parsePrice);
					}
					if((cleanString(addYearBox.getText(),true,0)).length() == 4){//check year formatting
						year = Integer.parseInt(cleanString(addYearBox.getText(),true,0));
					}else{
						throw new Exception("Entered Year is not formatted correctly. Must be a 4 digit number\n");
					}
					authMaker = cleanString(addAuthMakerBox.getText(),true,0);//get the author
					publisher = cleanString(addPublisherBox.getText(),true,0);//get the publisher
				}else{
					throw new Exception("Please ensure that the Product ID, Description and Year are provided\n");
				}
			}catch(Exception err){
				if(!error){//if there is no error yet, print the following
					messageDisplay.setText(messageDisplay.getText() + err.getMessage() + "\n\nWARNING: New product not added\n");
					error = true;
				}
			}
			try{//try to add the new product to the store if there is no error with the entered data
				if(typeBox.getSelectedIndex() == 0 && !error){
					eStore.addProduct(productID,desc,price,year,authMaker,publisher);//throws error if id in database
				}else if(typeBox.getSelectedIndex() == 1 && !error){
					eStore.addProduct(productID,desc,price,year,authMaker);//throws error if id in database
				}
				if(!error){
					messageDisplay.setText(messageDisplay.getText() + "Successfully added new product\n");
				}
			}catch(Exception err1){
				if(!error){
					messageDisplay.setText(messageDisplay.getText() + err1.getMessage() + " " + cleanString(addIdBox.getText(),true,0) + "\nWARNING: New product not added\n");
				}
			}
			//System.out.println(eStore.getSize());
		}
	}

	//Toggle listener for the type change in the add panel
	//hides the publisher panel and changes the label for the author maker box
	private class typeChangeListner implements ActionListener{
		public void actionPerformed(ActionEvent e){
			//System.out.println("Type Change");

			if(typeBox.getSelectedIndex() == 0){//if set to 0 (book) set authors and publisher open
				authMakerLabel.setText("Authors:    ");
				addPublisherPanel.setVisible(true);
			}else if(typeBox.getSelectedIndex() == 1){//otherwise, set maker and publisher off
				addPublisherPanel.setVisible(false);
				addPublisherBox.setText("");
				authMakerLabel.setText("Maker:      ");
			}
		}
	}

	//searchButtonListener is linked to the search button in the search panel
	//performs the search on the store
	private class searchButtonListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			//System.out.println("Search Product");

			if(!(searchMessageDisplay.getText()).equals("")){
				searchMessageDisplay.setText(searchMessageDisplay.getText() + "\nSearching___________________________________________________\n");
			}else{
				searchMessageDisplay.setText(searchMessageDisplay.getText() + "Searching___________________________________________________\n");	
			}

			//set default values
			int productID = -1;
			String desc = "";
			int[] years = {MIN_YEAR,MAX_YEAR};

			boolean error= false;

			try{//try to convert the filled values to their respective fields
				if(!(cleanString(searchIdBox.getText(),true,0)).equals("")){
					if((cleanString(searchIdBox.getText(),true,0)).length() == 6 &&(cleanString(searchIdBox.getText(),true,0)).matches("[0-9]+")){
						productID = Integer.parseInt(searchIdBox.getText());
					}else{
						throw new Exception("Please make sure the product id you\nare searching for is a 6 digit number\n");
					}
				}
				if(!(cleanString(searchDescBox.getText(),true,0)).equals("")){
					desc = searchDescBox.getText();
				}
				if((cleanString(searchSYearBox.getText(),true,0)).length() == 4 && (cleanString(searchSYearBox.getText(),true,0)).matches("[0-9]+")){
					if(!(cleanString(searchSYearBox.getText(),true,0)).equals("")){
						years[0] = Integer.parseInt(searchSYearBox.getText());	
					}else{
						searchSYearBox.setText(Integer.toString(MIN_YEAR));
					}
				}else{
					throw new Exception("Please amke sure the start year is a 4 digit number\n");
				}
				if((cleanString(searchFYearBox.getText(),true,0)).length() == 4 && (cleanString(searchFYearBox.getText(),true,0)).matches("[0-9]+")){
					if(!(cleanString(searchFYearBox.getText(),true,0)).equals("")){
						years[1] = Integer.parseInt(searchFYearBox.getText());
					}else{
						searchFYearBox.setText(Integer.toString(MAX_YEAR));
					}
				}else{
					throw new Exception("Please make sure that the end year is a 4 digit number\n");
				}

				if(years[0] > years[1]){//if the second year is greater than the first, throw an exception
					throw new Exception("Please make sure the end year comes after the start year\n");
				}
			}catch(Exception err){
				searchMessageDisplay.setText(searchMessageDisplay.getText() + err.getMessage());
				error = true;
			}
			if(!error){
				searchMessageDisplay.setText(searchMessageDisplay.getText() + eStore.printSearch(desc,productID,years));//prints the search results
			}
		}
	}

	//main class runs the gui 
	//loads in the data from the file
	public static void main(String[] args){//define main method
		//System.out.println("Starting Store");//output progress of startup
		fileName = "default.txt";//defaults to a default.txt file
		if(args.length == 1){//ensure there is only one argument provided
			fileName = args[0];//save the name of the file
		}else if(args.length > 1){//if there is more than 1 argument, throw an error
			//System.out.println("FATAL ERROR: To many arguments in the command linenStore failed to start");
			System.exit(-1);
		}else{//otherwise, generate a warning that there is no input file. Default output is the default.txt which may or may not exist
			//System.out.println("WARNING: No input file selected\nData will be saved to " + fileName);
		}

		Scanner input = new Scanner(System.in);//create input scanner

		//read in from a file
		int count = 0;
		try {//get input from the file
			//System.out.println("Loading Saved Data");//give user progress info
			File f = new File(fileName);//create a file with given product name
			Scanner fInput = new Scanner(f);

			while(fInput.hasNextLine()){//loop while there are more lines in the text file
				String current = fInput.nextLine();

				count += parseSummary(current,eStore,fileName);
			}
			fInput.close();//close file scanner
		}catch(Exception e){//catch filenotfound exception and any other exceptions from file input
			//System.out.println("WARNING: File <" + fileName + "> could not be opened\nProducts may not load");
		}

		//System.out.println("Successfully Loaded " + eStore.getSize() + " Products\n");

		Assignment3 gui = new Assignment3();//creates the gui
		gui.setVisible(true);//set visible
	}//end main method

	/**cleanString takes a string and performs modifications to it
	@param inputString is the stringto be modified
	@param trimString signals whether to trim the whitespace or not
	@param lowerUpper is an integer to signal whether to convert case of string
	@return the modified string*/
	public static String cleanString (String inputString,boolean trimString,int lowerUpper){
		if(trimString){//trim the input string
			inputString = inputString.trim();
		}
		if(lowerUpper == 1){//convert string to lowercase
			inputString = inputString.toLowerCase();
		}
		if(lowerUpper == 2){//convert string to upper case
			inputString = inputString.toUpperCase();
		}
		return inputString;//return new string
	}

	/**parseSummary reads in the lines from the text files and determines how to parse it
	@param current is the current string line from the text file
	@param store is the eStore to which the data will be saved to
	@param fileName was to be used for comprehensive messages to the user
	@return number of lines parsed*/
	public static int parseSummary(String current,EStoreSearch store,String fileName){
		int count = 0;
		if(current.contains("Summary#/#")){//check for the summary line for each product
			String [] details = current.split("#/#");//split the summary line
			try{//parse the data respectively
				if(details.length == 7){//add new product depending on the length of the summary line
					try{
						store.addProduct(Integer.parseInt(details[2]),cleanString(details[3],true,0),Double.parseDouble(details[4]),Integer.parseInt(details[5]),cleanString(details[6],true,0));
					}catch(Exception e){
					//	System.out.println("Error while adding");
					}
					count++;
				}else if(details.length == 8){
					try{
						store.addProduct(Integer.parseInt(details[2]),cleanString(details[3],true,0),Double.parseDouble(details[4]),Integer.parseInt(details[5]),cleanString(details[6],true,0),cleanString(details[7],true,0));
					}catch(Exception e){
						//System.out.println("Error while adding");
					}
					count++;
				}else{//throw an error if formatting incorrect
					//System.out.println("WARNING: Incorrect data found in " + fileName + "\nSome products may not load");
				}
			}catch (NumberFormatException e){//catch conversion errors
				//System.out.println("WARNING: Incorrect data found in " + fileName + "\nSome products may not load");
			}
		}
		return count;
	}

	//GUI part of the program
	//Creates a tree structure of panels with the root being the main window
	//Branches off into add and search panels
	//add and search break off into grid based layouts integrated with flow layouts and border layouts
	public Assignment3(){
		super("EStore Search");//Set tile of window
		setSize(WIDTH,HEIGHT);//set dimensions
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//close operation
		setLayout(new BoxLayout(getContentPane(),BoxLayout.X_AXIS));//set layout

		addWindowListener(new SaveOnExit());//add the save listener

		//Create the Command menu////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		JMenu commandList = new JMenu("Commands");

		//Create the menu options//////////////////////////////////////////////////////////////////////
		JMenuItem addProduct = new JMenuItem("Add");
		addProduct.addActionListener(new addProductListener());
		commandList.add(addProduct);

		JMenuItem searchProducts = new JMenuItem("Search");
		searchProducts.addActionListener(new searchProductListener());
		commandList.add(searchProducts);

		JMenuItem quitMenu = new JMenuItem("Quit");
		quitMenu.addActionListener(new quitListener());
		commandList.add(quitMenu);
		//Create the winodw options\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		//Create the menu bar
		JMenuBar menuBar = new JMenuBar();
		menuBar.add(commandList);
		setJMenuBar(menuBar);
		//Create the command menu\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		//Create the initial message panel////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		initial = new JPanel();
		initial.setBackground(Color.GREEN);
		initial.setLayout(new BorderLayout());

		//Create the message area//////////////////////////////////////////////////////////////////
		JTextArea message = new JTextArea();
		if(eStore.getSize() != 1){
			message.setText("Welcome to EStore Search\n\nChoose a command from the menu to add a product,\nsearch for products or quit the program\n\nThere are " + eStore.getSize() + " products are in the database\n");
		}else{
			message.setText("Welcome to EStore Search\n\nChoose a command from the menu to add a product,\nsearch for products or quit the program\n\nThere is " + eStore.getSize() + " product in the database\n");	
		}
		message.setBackground(Color.GREEN);
		message.setFont(new Font("Monospaced", Font.BOLD, 16));//Set font
		message.setEditable(false);
		message.setLineWrap(true);
		initial.add(message,BorderLayout.CENTER);
		//Create the message area\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
		add(initial);
		//create the initial message panel\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		//create the add panel////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		addPanel = new JPanel();
		addPanel.setBorder(BorderFactory.createEmptyBorder(BORDER_T,BORDER_L,BORDER_B,BORDER_R));
		addPanel.setLayout(new BorderLayout());
		addPanel.setBackground(Color.CYAN);
		addPanel.setVisible(false);

		//Create the add menu header
		JLabel addHeader = new JLabel();
		addHeader.setText("Add Product:");
		addHeader.setFont(new Font("Monospaced", Font.BOLD, 15));//Set font
		addPanel.add(addHeader,BorderLayout.NORTH);

		//Create the outer add panel
		JPanel addCenterOuter = new JPanel();
		addCenterOuter.setBackground(Color.CYAN);
		addCenterOuter.setLayout(new GridLayout(2,1));

		//Create the top center add panel
		JPanel addCenterTop = new JPanel();
		addCenterTop.setBackground(Color.CYAN);
		addCenterTop.setLayout(new GridLayout(1,2));

		//Create the top left center panel
		JPanel addCenterLeft = new JPanel();
		addCenterLeft.setBackground(Color.CYAN);
		addCenterLeft.setLayout(new GridLayout(7,1));

		//Create the type panel
		JPanel addTypePanel = new JPanel();
		addTypePanel.setBackground(Color.CYAN);
		addTypePanel.setLayout(new FlowLayout());
		JLabel typeLabel = new JLabel();
		typeLabel.setText("Type:       ");
		addTypePanel.add(typeLabel);

		//Create the type combo box
		typeBox = new JComboBox<String>(TYPES);
		typeBox.addActionListener(new typeChangeListner());
		addTypePanel.add(typeBox);

		addCenterLeft.add(addTypePanel);

		//Create the id panel
		JPanel addIdPanel = new JPanel();
		addIdPanel.setBackground(Color.CYAN);
		addIdPanel.setLayout(new FlowLayout());
		JLabel idLabel = new JLabel();
		idLabel.setText("Product ID: ");
		addIdPanel.add(idLabel);

		//Create the id box
		addIdBox = new JTextField(CHARS_PER_LINE);
		addIdPanel.add(addIdBox);

		addCenterLeft.add(addIdPanel);

		//Create the description panel
		JPanel addDescPanel = new JPanel();
		addDescPanel.setBackground(Color.CYAN);
		addDescPanel.setLayout(new FlowLayout());
		JLabel descLabel = new JLabel();
		descLabel.setText("Description:");
		addDescPanel.add(descLabel);

		//Create the description box
		addDescBox = new JTextField(CHARS_PER_LINE);
		addDescPanel.add(addDescBox);

		addCenterLeft.add(addDescPanel);

		//Create the price panel
		JPanel addPricePanel = new JPanel();
		addPricePanel.setBackground(Color.CYAN);
		addPricePanel.setLayout(new FlowLayout());
		JLabel priceLabel =  new JLabel();
		priceLabel.setText("Price:      ");
		addPricePanel.add(priceLabel);

		//Create the price box
		addPriceBox = new JTextField(CHARS_PER_LINE);
		addPricePanel.add(addPriceBox);

		addCenterLeft.add(addPricePanel);

		//Create the year panel
		JPanel addYearPanel = new JPanel();
		addYearPanel.setBackground(Color.CYAN);
		addYearPanel.setLayout(new FlowLayout());
		JLabel yearLabel = new JLabel();
		yearLabel.setText("Year:       ");
		addYearPanel.add(yearLabel);

		//Create the year box
		addYearBox = new JTextField(CHARS_PER_LINE);
		addYearPanel.add(addYearBox);

		addCenterLeft.add(addYearPanel);

		//Create the author/maker panel
		JPanel addAuthMakerPanel = new JPanel();
		addAuthMakerPanel.setBackground(Color.CYAN);
		addAuthMakerPanel.setLayout(new FlowLayout());
		authMakerLabel = new JLabel();
		authMakerLabel.setText("Authors:    ");
		addAuthMakerPanel.add(authMakerLabel);

		//Create the author/maker box
		addAuthMakerBox = new JTextField(CHARS_PER_LINE);
		addAuthMakerPanel.add(addAuthMakerBox);

		addCenterLeft.add(addAuthMakerPanel);
		
		//Create the publisher panel (global)
		addPublisherPanel = new JPanel();
		addPublisherPanel.setBackground(Color.CYAN);
		addPublisherPanel.setLayout(new FlowLayout());
		JLabel publisherLabel = new JLabel();
		publisherLabel.setText("Publisher:  ");
		addPublisherPanel.add(publisherLabel);

		//Create the publisher box
		addPublisherBox = new JTextField(CHARS_PER_LINE);
		addPublisherPanel.add(addPublisherBox);

		addCenterLeft.add(addPublisherPanel);

		addCenterTop.add(addCenterLeft);

		//Create the button side right center add panel
		JPanel addCenterRight = new JPanel();
		addCenterRight.setBackground(Color.CYAN);
		addCenterRight.setLayout(new GridLayout(2,1));
		addCenterRight.setBorder(BorderFactory.createEmptyBorder(2*BORDER_T,0,2*BORDER_B,0));

		//Create the addButton panel
		JPanel addButtonPanel = new JPanel();
		addButtonPanel.setBorder(BorderFactory.createEmptyBorder(BORDER_T,0,BORDER_B/2,0));
		addButtonPanel.setBackground(Color.CYAN);

		//Create the add button for the add panel
		JButton addButton = new JButton();
		addButton.setText("Add");
		addButton.addActionListener(new addAddListener());
		addButtonPanel.add(addButton);

		//Create the reset button panel
		JPanel resetButtonPanel = new JPanel();
		resetButtonPanel.setBorder(BorderFactory.createEmptyBorder(BORDER_T/2,0,BORDER_B,0));
		resetButtonPanel.setBackground(Color.CYAN);

		//Create the reset button
		JButton addResetButton = new JButton();
		addResetButton.setText("Reset");
		addResetButton.addActionListener(new addProductListener());
		resetButtonPanel.add(addResetButton);

		addCenterRight.add(addButtonPanel);
		addCenterRight.add(resetButtonPanel);

		addCenterTop.add(addCenterRight);

		addCenterOuter.add(addCenterTop);

		//Create the bottom panel for the add panel
		JPanel addCenterBottom = new JPanel();
		addCenterBottom.setBackground(Color.CYAN);
		addCenterBottom.setLayout(new BorderLayout());

		//Create the message panel header
		JLabel messageHeader = new JLabel();
		messageHeader.setText("Messages:");
		addCenterBottom.add(messageHeader,BorderLayout.NORTH);

		//Create the scroll area for the message display
		messageDisplay = new JTextArea(SCROLL_ROWS,SCROLL_COLS);
		messageDisplay.setText("");
		messageDisplay.setEditable(false);
		messageDisplay.setFont(new Font("Monospaced", Font.PLAIN, 13));//Set font
		JScrollPane scrollableText = new JScrollPane(messageDisplay);
		scrollableText.setPreferredSize(new Dimension(SCROLL_ROWS,SCROLL_COLS));
		scrollableText.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        scrollableText.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

        addCenterBottom.add(scrollableText,BorderLayout.CENTER);

		addCenterOuter.add(addCenterBottom);

		addPanel.add(addCenterOuter,BorderLayout.CENTER);

		add(addPanel);
		//create the add panel\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

		//create the search panel///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		searchPanel = new JPanel();
		searchPanel.setLayout(new BorderLayout());
		searchPanel.setBorder(BorderFactory.createEmptyBorder(BORDER_T,BORDER_L,BORDER_B,BORDER_R));
		searchPanel.setBackground(Color.YELLOW);
		searchPanel.setVisible(false);

		//Create the header for the search panel
		JLabel searchMenuHeader = new JLabel();
		searchMenuHeader.setText("Search for a Product:");
		searchMenuHeader.setFont(new Font("Monospaced", Font.BOLD, 15));//Set font
		searchPanel.add(searchMenuHeader,BorderLayout.NORTH);

		//Create the search center panel
		JPanel searchCenter = new JPanel();
		searchCenter.setBackground(Color.YELLOW);
		searchCenter.setLayout(new GridLayout(2,1));

		//Create the top search center panel
		JPanel searchTop = new JPanel();
		searchTop.setBackground(Color.YELLOW);
		searchTop.setLayout(new GridLayout(1,2));

		//Create the top center left search panel
		JPanel searchLeft = new JPanel();
		searchLeft.setBackground(Color.YELLOW);
		searchLeft.setLayout(new GridLayout(4,1));

		//Create the id panel
		JPanel searchIDPanel = new JPanel();
		searchIDPanel.setBackground(Color.YELLOW);
		searchIDPanel.setLayout(new FlowLayout());
		JLabel searchIdLabel = new JLabel();
		searchIdLabel.setText("Product ID: ");
		searchIDPanel.add(searchIdLabel);

		//Create the id box
		searchIdBox = new JTextField(CHARS_PER_LINE);
		searchIDPanel.add(searchIdBox);

		searchLeft.add(searchIDPanel);

		//Create the description panel
		JPanel searchDescPanel = new JPanel();
		searchDescPanel.setBackground(Color.YELLOW);
		searchDescPanel.setLayout(new FlowLayout());
		JLabel searchDescLabel = new JLabel();
		searchDescLabel.setText("Keywords:   ");
		searchDescPanel.add(searchDescLabel);

		//Create the description box
		searchDescBox = new JTextField(CHARS_PER_LINE);
		searchDescPanel.add(searchDescBox);

		searchLeft.add(searchDescPanel);

		//Create the start year panel
		JPanel searchSYearPanel = new JPanel();
		searchSYearPanel.setBackground(Color.YELLOW);
		searchSYearPanel.setLayout(new FlowLayout());
		JLabel searchSYearLabel = new JLabel();
		searchSYearLabel.setText("Start Year: ");
		searchSYearPanel.add(searchSYearLabel);

		//Create the start year box
		searchSYearBox = new JTextField(CHARS_PER_LINE);
		searchSYearPanel.add(searchSYearBox);

		searchLeft.add(searchSYearPanel);

		//Create the end year panel
		JPanel searchFYearPanel = new JPanel();
		searchFYearPanel.setBackground(Color.YELLOW);
		searchFYearPanel.setLayout(new FlowLayout());
		JLabel searchFYearLabel = new JLabel();
		searchFYearLabel.setText("End Year:   ");
		searchFYearPanel.add(searchFYearLabel);

		//Create the end year box
		searchFYearBox = new JTextField(CHARS_PER_LINE);
		searchFYearPanel.add(searchFYearBox);

		searchLeft.add(searchFYearPanel);

		searchTop.add(searchLeft);

		//Create the search right top center panel
		JPanel searchRight = new JPanel();
		searchRight.setBackground(Color.YELLOW);
		searchRight.setBorder(BorderFactory.createEmptyBorder(2*BORDER_T,0,2*BORDER_B,0));
		searchRight.setLayout(new GridLayout(2,1));

		//Create the search button panel
		JPanel searchButtonPanel = new JPanel();
		searchButtonPanel.setBackground(Color.YELLOW);
		searchButtonPanel.setBorder(BorderFactory.createEmptyBorder(BORDER_T,0,BORDER_B/2,0));

		//Create the search button
		JButton searchButton = new JButton();
		searchButton.addActionListener(new searchButtonListener());
		searchButton.setText("Search");
		searchButtonPanel.add(searchButton);
		searchRight.add(searchButtonPanel);

		//Create the searfch reset panel
		JPanel searchResetPanel = new JPanel();
		searchResetPanel.setBackground(Color.YELLOW);
		searchResetPanel.setBorder(BorderFactory.createEmptyBorder(BORDER_T/2,0,BORDER_B,0));

		//Create the reset button
		JButton searchResetButton = new JButton();
		searchResetButton.addActionListener(new searchProductListener());
		searchResetButton.setText("Reset");
		searchResetPanel.add(searchResetButton);
		searchRight.add(searchResetPanel);

		searchTop.add(searchRight);

		searchCenter.add(searchTop);

		//Create the bottom of the search panel message area
		JPanel searchBottom = new JPanel();
		searchBottom.setBackground(Color.YELLOW);
		searchBottom.setLayout(new BorderLayout());

		//Create the search result header
		JLabel searchResultHeader = new JLabel();
		searchResultHeader.setText("Search Results:");
		searchBottom.add(searchResultHeader,BorderLayout.NORTH);

		//Create the search result text area
		searchMessageDisplay = new JTextArea(SCROLL_ROWS,SCROLL_COLS);
		searchMessageDisplay.setText("");
		searchMessageDisplay.setEditable(false);
		searchMessageDisplay.setFont(new Font("Monospaced", Font.PLAIN, 13));//Set font
		JScrollPane scrollText = new JScrollPane(searchMessageDisplay);
		scrollText.setPreferredSize(new Dimension(SCROLL_ROWS,SCROLL_COLS));
		scrollText.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        scrollText.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        searchBottom.add(scrollText,BorderLayout.CENTER);

        searchCenter.add(searchBottom);

        searchPanel.add(searchCenter,BorderLayout.CENTER);
		add(searchPanel);
		//create the search panel\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	}
}//end main class
