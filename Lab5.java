/*Author: Erich MacLean
CIS2430*0209
Lab Exercise 5
file: Lab5.java
GUI designed to implement all previous functions*/
package Lab5;

//import the packages required for the program
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.io.*;

public class Lab5 extends JFrame{
	private static final int WIDTH = 1000;
	private static final int HEIGHT = 400;

	private static final int CHARS_PER_LINE = 70;

	private ArrayList<Student> guiStudents= new ArrayList<Student>();//create students arraylist
	private HashMap<String,Student> guiDirectory = new HashMap<String,Student>();//create the hashmap direcvtory for the new additions to the student list

	private String menuItem = "";

	private JPanel initial;
	private JPanel file;
	private JPanel addPanel;
	private JPanel searchPanel;
	private JPanel display;

	private JPanel innerFile;

	private JTextField guiFileName;

	private JLabel studentNumLabel = new JLabel("Total Students: " + guiStudents.size() + "; Total Average: " + totalaverage(guiStudents));
	private JTextArea studentDetails = new JTextArea(guiStudents.size(),CHARS_PER_LINE);

	private JTextField programSearch;
	private JTextField yearSearch;
	private JTextField nameSearch;

	private JTextArea searchResults = new JTextArea(guiStudents.size(),CHARS_PER_LINE);

	private JTextField addProgram;
	private JTextField addYear;
	private JTextField addLastName;
	private JTextField addGrade;
	private JTextField addSupervisor;
	private JComboBox<String> addDegree;
	private JTextField addSchool;

	private JComboBox<String> toggle;
	private JButton addRequest;

	private static final int FILE_LENGTH = 30;


	//Define actionListeners for each menu item
	private class fileListener implements ActionListener{//menu bar action listener for file item
    	public void actionPerformed(ActionEvent e){
    		//System.out.println("File");
       		addPanel.setVisible(false);
       		display.setVisible(false);
       		searchPanel.setVisible(false);
       		initial.setVisible(false);
       		file.setVisible(true);
    	}
    }

    private class addListener implements ActionListener{//menu bar action listener for add item
    	public void actionPerformed(ActionEvent e){
    		//System.out.println("Add");
       		file.setVisible(false);
       		display.setVisible(false);
       		searchPanel.setVisible(false);
       		initial.setVisible(false);
       		addPanel.setVisible(true);
    	}
    }

    private class searchListener implements ActionListener{//menu bar actionn listneer for search item
    	public void actionPerformed(ActionEvent e){
    		//System.out.println("Search");
    		addPanel.setVisible(false);
       		display.setVisible(false);
       		file.setVisible(false);
       		initial.setVisible(false);
       		searchPanel.setVisible(true);
    	}
    }

    private class displayListener implements ActionListener{//menu bar action listener for display item
    	public void actionPerformed(ActionEvent e){
    		double totalAverage = totalaverage(guiStudents);//update the average
			//System.out.println("Gui student Size: " + guiStudents.size());
			//System.out.println("Directory size " + guiDirectory.size());

			studentNumLabel.setText("Total Students: " + guiStudents.size() + "; Total Average: " + totalAverage);//update data being displayed
			studentDetails.setText(concatAll(guiStudents));

    		//System.out.println("Access");
       		file.setVisible(false);
       		addPanel.setVisible(false);
       		searchPanel.setVisible(false);
       		initial.setVisible(false);
       		display.setVisible(true);
    	}
    }
    //define actionlisteners for each menu item

    //Create button action listeners
    private class loadListener implements ActionListener{//load listener is linked to the load button to take the given file name and attempt to read it into the list and hashmap
    	public void actionPerformed(ActionEvent e){
    		//System.out.println("loadSelect");
			String fileName = guiFileName.getText();
			fileName = fileName.trim();

			boolean error = false;
			try{//try to read in from given file
				File f = new File(fileName);
				Scanner fr = new Scanner(f);
				while(fr.hasNextLine()){
					String [] current = ((fr.nextLine()).trim()).split(" ");
					//length of either 4 or 7 entries
					//Line: program0 year1 grade supervisor phdstatus school lastname
					//Line: program year grade lastname
					//String program, int yearIn,String lName,double averageIn
					//String program, int yearIn,String lName,double averageIn,String supervisorIn,int phd,String school)

					if(current.length == 4){
						try{
							Student s = (new Student(current[0].trim(),Integer.parseInt(current[1].trim()),current[3].trim(),Double.parseDouble(current[2].trim())));
							if(guiDirectory.containsKey(s.toString(2))){
								throw new Exception("ERROR: A duplicate entry has been found");
							}else{
								guiDirectory.put(s.toString(2),s);
								guiStudents.add(s);
							}
						}catch(Exception err1){
							if(!error){
								newWindow("File loaded with duplicate entries voided",2);
								error = true;
							}
							//System.out.println(err1.getMessage() + "\nNew student could not be added");
						}
					}else if(current.length == 7){
						try{//try to add the new student if is not already in the directory
							Student s = (new GraduateStudent(current[0].trim(),Integer.parseInt(current[1].trim()),current[6],Double.parseDouble(current[2].trim()),current[3],Integer.parseInt(current[4]),current[5]));
							if(guiDirectory.containsKey(s.toString(2))){
								throw new Exception("ERROR: A duplicate entry has been found");
							}else{
								guiDirectory.put(s.toString(2),s);
								guiStudents.add(s);
							}
						}catch(Exception err2){
							if(!error){
								newWindow("File loaded with duplicate entries voided",2);
								error = true;
							}
							//System.out.println(err2.getMessage() + "\nNew graduate student could not be added");
						}
					}else{
						throw new Exception();
					}
				}
				fr.close();
			}catch(Exception err){//catch any exceptions
				//System.out.println("ERROR: File could not be read from correctly");
				if(!error){
					newWindow("Error while loading file: Some entries may not appear",3);
					error = true;
				}
			}
			
			if(!error){//Outputs success message if success
				newWindow("Loaded Data!",1);
			}
    	}
    }

    private class saveListener implements ActionListener{//save listener linked to the save button. Writes current data to the given file name
    	public void actionPerformed(ActionEvent e){
    		//System.out.println("saveSelect");
			String fileName = (guiFileName.getText()).trim();
			boolean caught = false;
			try{//try to print to file
				File f = new File(fileName);
				PrintWriter pw = new PrintWriter(f);
				for(int i = 0;i < guiStudents.size();i++){
					pw.println((guiStudents.get(i)).toString(0));
				}
				pw.close();
			}catch(Exception err){//catch any file errors
			//	System.out.println("ERROR: The specified destination could not be printed to at this time");
				caught = true;
				newWindow("ERROR: File could not be written to",2);
			}
			if(!caught){
				newWindow("Saved!",1);
			}
    	}
    }

    private class searchButtonListener implements ActionListener{//linked to search button. Validates entry and then performs search. Updates search display area
    	public void actionPerformed(ActionEvent e){
    		//System.out.println("search select");
    		String tempProgram = (programSearch.getText()).trim();
    		String tempYear = (yearSearch.getText()).trim();
    		String tempName = (nameSearch.getText()).trim();

    		if(tempName.equals("") && tempYear.equals("") && !tempProgram.equals("")){
    			//System.out.println("1:"+concatSearch(guiStudents,tempProgram));
    			searchResults.setText(concatSearch(guiStudents,tempProgram));
    		}else if(!tempProgram.equals("") && !tempYear.equals("") && !tempName.equals("")){
    			//System.out.println("2:"+concatLookup(guiDirectory,tempProgram,tempYear,tempName));
    			if(tempYear.matches("[0-9]+")){
					searchResults.setText(concatLookup(guiDirectory,tempProgram,tempYear,tempName));
    			}else{
    				newWindow("ERROR: Year field requires integer value",2);
    				searchResults.setText("Invalid search terms");
    			}
    		}else{
    			if(tempYear.matches("[0-9]+")){
	    			newWindow("ERROR: Search by program name or all fields",2);
	    			searchResults.setText("Invalid search terms");
	    		}else{
	    			newWindow("ERROR: Year field requires integer value",2);
	    			searchResults.setText("Invalid search terms");
	    		}
    		}
    	}
    }

    private class typeChangeListener implements ActionListener{//invokes a toggle for student and grad student. Implemented as the type identifier so that the user can see what needs to be entered for any given student/grad
    	public void actionPerformed(ActionEvent e){
    		//System.out.println("toggle");
    		//System.out.println(toggle.getSelectedItem());
    		if((toggle.getSelectedItem()).equals("Grad Student")){//open inputs for grad students, change colour to signal (does not delete any inputs)
    			addSupervisor.setBackground(Color.WHITE);
    			addDegree.setBackground(Color.WHITE);
    			addSchool.setBackground(Color.WHITE);

    			addSupervisor.setEditable(true);
    			addDegree.setEnabled(true);
    			addSchool.setEditable(true);

    			addRequest.setText("Add Grad Student");
    		}else{//closes inputs for grad student data (does not delete any current inputs)
				addSupervisor.setBackground(Color.LIGHT_GRAY);
    			addDegree.setBackground(Color.LIGHT_GRAY);
    			addSchool.setBackground(Color.LIGHT_GRAY);

    			addSupervisor.setEditable(false);
    			addDegree.setEnabled(false);
    			addSchool.setEditable(false);

    			addRequest.setText("Add Student");
    		}
    	}
    }

    private class addRequestListener implements ActionListener{//add button listener verifies and then performs add to the list and directory
    	public void actionPerformed(ActionEvent e){
    		//System.out.println("add request");

    		String tempProgram = addProgram.getText();//retrieve given inputs
    		String tempYear = addYear.getText();
    		String tempLastName = addLastName.getText();
    		String tempGrade = (addGrade.getText()).trim();
    		if(tempGrade.equals("")){
    			tempGrade = "0";
    		}
    		String tempSupervisor = addSupervisor.getText();
    		String tempDegree = (String)addDegree.getSelectedItem();
    		int deg = 0;
    		if(tempDegree.equals("PhD")){
    			deg = 1;
    		}
    		String tempSchool = addSchool.getText();

    		String type = (String)toggle.getSelectedItem();
    		if(tempProgram.equals("") || tempYear.equals("") || tempLastName.equals("") || (type.equals("Grad Student") && (tempSupervisor.equals("")))){//verifies that the inputs are entered correctly
    			newWindow("ERROR: Please ensure all required fields are provided",2);
    		}else{
	    		boolean error = false;
	    		if(type.equals("Student")){
	    			try{
						Student s = (new Student(tempProgram.trim(),Integer.parseInt(tempYear.trim()),tempLastName.trim(),Double.parseDouble(tempGrade.trim())));//try to create a new student
						try{
							if(!error){
								if(guiDirectory.containsKey(s.toString(2))){//check if the student is in the directory
									throw new Exception("ERROR: A duplicate entry has been found");
								}else{
									guiDirectory.put(s.toString(2),s);//dd to list and directory
									guiStudents.add(s);
									newWindow("New Student Successfully Added",1);//output message
								}
							}
						}catch(Exception err1){//catches duplicate error
							if(!error){
								newWindow(err1.getMessage(),2);
								error = true;
							}
						}
					}catch(Exception err4){//catches thrown errors from student constructor
						if(!error){
							newWindow("ERROR: Student could not be added",3);
							error = true;
						}
					}
	    		}else{//grad student
	    			try{
						Student s = (new GraduateStudent(tempProgram.trim(),Integer.parseInt(tempYear.trim()),tempLastName,Double.parseDouble(tempGrade.trim()),tempSupervisor,deg,tempSchool));//try to create a new grad student
						try{
							if(!error){
								if(guiDirectory.containsKey(s.toString(2))){//check if student exists
									throw new Exception("ERROR: A duplicate entry has been found");
								}else{
									guiDirectory.put(s.toString(2),s);//add to list and directory
									guiStudents.add(s);
									newWindow("New Grad Student Successfully Added",1);
								}
							}
						}catch(Exception err1){//catches duplicate errors
							if(!error){
								newWindow(err1.getMessage(),2);
								error = true;
							}
						}
					}catch(Exception err4){//catches errors thrown by constructor
						if(!error){
							newWindow("ERROR: Student could not be added",3);
							error = true;
						}
					}
	    		}
	    	}
    		//System.out.println(guiStudents.size());
    	}
    }

	public static void main (String [] args){
		Lab5 gui = new Lab5();//run the jframe gui
		gui.setVisible(true);
	}
	public static double totalaverage(ArrayList<Student> s){//calculate the total average of all the students currently in the array list
		double sum = 0;
		int total = 0;
		for(int i = 0;i < s.size();i++){//loop through the arraylist of students
			sum += (s.get(i)).getaverage();//add to the total sum
			total++;
		}
		sum = sum / total;//divide the sum by the size of the students counted
		sum = Math.round(sum * 100.0) / 100.0;
		return (sum);
	}

	public static String concatAll(ArrayList<Student> s){//concatenates all the given details together into one string to set to text area
		String returnString = "";
		for (int t = 0;t < s.size();t++){
			returnString += ((s.get(t)).toString(1)) + "\n";
		}
		return returnString;
	}
	
	public static String concatSearch(ArrayList<Student> s,String searchString){//concat all terms found by linear search for product name
		String returnString = "";
		int count = 0;
		for(int i = 0;i < s.size();i++){//print out any students that match the entered program name
			if(((s.get(i)).getprogram()).equalsIgnoreCase(searchString)){
				returnString += ((s.get(i)).toString(1)) + "\n";
				count++;
			}
		}
		if(count == 0){
			returnString += ("There are no students that matched that description\n");
		}
		return returnString;
	}

	public static String concatLookup(HashMap<String,Student> d,String program,String year, String lastName){//concat all terms found by hashtable search
		String returnString = "";
		String key = program.toLowerCase() + " " + year + " " + lastName.toLowerCase();//create the expected key for the new student
		if(d.containsKey(key)){
			returnString += ((d.get(key)).toString(1)) + "\n";
		}else{
			returnString += ("There are no students that matched that description\n");
		}
		return returnString;
	}

	public Lab5(){//gui extension to lab 5 main
        super("STUDENT DATABASE");//initialize main window
        setSize(WIDTH,HEIGHT);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.X_AXIS));

        //Create Menu Bar
        JMenu menuList = new JMenu("Select Action");//create main menu bar

        JMenuItem loadChoice = new JMenuItem("File");//add file option
        loadChoice.addActionListener(new fileListener());
        menuList.add(loadChoice);

        JMenuItem addChoice = new JMenuItem("Add");//add add option
        addChoice.addActionListener(new addListener());
        menuList.add(addChoice);

        JMenuItem searchChoice = new JMenuItem("Search");//add search option
        searchChoice.addActionListener(new searchListener());
        menuList.add(searchChoice);

        JMenuItem displayChoice = new JMenuItem("Display");//add display option
        displayChoice.addActionListener(new displayListener());
        menuList.add(displayChoice);

        JMenuBar bar = new JMenuBar();//create menu bar
        bar.add(menuList);
        setJMenuBar(bar);
        //Create menu bar

        initial = new JPanel();//create initial message panel
        initial.setLayout(new BorderLayout());
        JTextArea message = new JTextArea("Welcome. Navigate options using the menu above");
        message.setBackground(Color.ORANGE);
        message.setEditable(false);
        initial.add(message,BorderLayout.CENTER);
        add(initial);

        //Create All Student Display
        display = new JPanel();
        display.setBorder(BorderFactory.createEmptyBorder(50, 50, 50, 50));
        display.setBackground(Color.YELLOW);
        display.setVisible(false);
        display.setLayout(new BorderLayout());
        display.add(studentNumLabel,BorderLayout.NORTH);

        
        studentDetails.setEditable(false);
        studentDetails.setText("No students entered so far");
        JScrollPane scrollableText = new JScrollPane(studentDetails);
        scrollableText.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        scrollableText.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        display.add(scrollableText);

        add(display);
        //Create All Student Display

        //Create Add Panel
        addPanel = new JPanel();
        addPanel.setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
        addPanel.setLayout(new BorderLayout());
        addPanel.setBackground(Color.PINK);
        addPanel.setVisible(false);

		JPanel addLeft = new JPanel();
		addLeft.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 5));
		addLeft.setBackground(Color.PINK);
		addLeft.setLayout(new GridLayout(8,1));

		addLeft.add(new JLabel("Program Name:"));

		addProgram = new JTextField("Program Name",CHARS_PER_LINE);
		addLeft.add(addProgram);

		addLeft.add(new JLabel("Year:"));

		addYear = new JTextField("Year",CHARS_PER_LINE);
		addLeft.add(addYear);

		addLeft.add(new JLabel("Last Name:"));

		addLastName = new JTextField("Last Name",CHARS_PER_LINE);
		addLeft.add(addLastName);

		addLeft.add(new JLabel("Average:"));

		addGrade = new JTextField("Average Grade",CHARS_PER_LINE);
		addLeft.add(addGrade);
		//Add Grad Student Info
		JPanel addRight = new JPanel();
		addRight.setBorder(BorderFactory.createEmptyBorder(0, 5, 0, 0));
		addRight.setBackground(Color.PINK);
		addRight.setLayout(new GridLayout(6,1));

		addRight.add(new JLabel("Supervisor:"));
		addSupervisor = new JTextField("Supervisor",CHARS_PER_LINE);
		addSupervisor.setEditable(false);
		addSupervisor.setBackground(Color.LIGHT_GRAY);
		addRight.add(addSupervisor);

		addRight.add(new JLabel("Degree:"));
		String[] degreeOptions = {"Masters","PhD"};
		addDegree = new JComboBox<String>(degreeOptions);
		addDegree.setEnabled(false);
		addDegree.setBackground(Color.LIGHT_GRAY);
		addRight.add(addDegree);

		addRight.add(new JLabel("School:"));
		addSchool = new JTextField("School Name",CHARS_PER_LINE);
		addSchool.setEditable(false);
		addSchool.setBackground(Color.LIGHT_GRAY);
		addRight.add(addSchool);
		//Add Grad Student Info

		JPanel addFields = new JPanel();
		addFields.setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
		addFields.setBackground(Color.PINK);
		addFields.setLayout(new GridLayout(1,2));
		addFields.add(addLeft);
		addFields.add(addRight);

		addPanel.add(addFields,BorderLayout.CENTER);

		addPanel.add(new JLabel("Add New Student or Grad Student"),BorderLayout.NORTH);

		JPanel addControl = new JPanel();
		addControl.setLayout(new GridLayout(1,2));
		addControl.setBackground(Color.PINK);


		addRequest = new JButton();
		addRequest.setText("Add Student");
        addRequest.setPreferredSize(new Dimension(30,50));
        addRequest.addActionListener(new addRequestListener());
        addControl.add(addRequest);

        String[] types = {"Student","Grad Student"};
        toggle = new JComboBox<String>(types);
        toggle.addActionListener(new typeChangeListener());
        addControl.add(toggle);

        addPanel.add(addControl,BorderLayout.SOUTH);

        add(addPanel);
        //Create Add Panel

        //Create search panel
        searchPanel = new JPanel();
        searchPanel.setBackground(Color.GREEN);
        searchPanel.setVisible(false);
        searchPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        searchPanel.setLayout(new BorderLayout());

        JPanel innerSearch = new JPanel();
        innerSearch.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        innerSearch.setBackground(Color.GREEN);
        innerSearch.setLayout(new GridLayout(1,2));

        JPanel leftSearch = new JPanel();
        leftSearch.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 5));
        leftSearch.setBackground(Color.GREEN);
        leftSearch.setLayout(new GridLayout(6,1));


        leftSearch.add(new JLabel("Program Name:"));

        programSearch = new JTextField();
        leftSearch.add(programSearch);

        leftSearch.add(new JLabel("Year:"));

        yearSearch = new JTextField();
        leftSearch.add(yearSearch);

        leftSearch.add(new JLabel("Last Name:"));

        nameSearch = new JTextField();
        leftSearch.add(nameSearch);

        JPanel rightSearch = new JPanel();
        rightSearch.setLayout(new BorderLayout());
        rightSearch.setBackground(Color.GREEN);
        rightSearch.setBorder(BorderFactory.createEmptyBorder(0, 5, 0, 0));

        searchResults.setEditable(false);
        JScrollPane scrollResults = new JScrollPane(searchResults);
        scrollResults.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        scrollResults.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        rightSearch.add(scrollResults,BorderLayout.CENTER);

        innerSearch.add(leftSearch);
        innerSearch.add(rightSearch);

        searchPanel.add(innerSearch,BorderLayout.CENTER);

        JButton searchButton = new JButton();
        searchButton.setText("Search");
        searchButton.addActionListener(new searchButtonListener());
        searchButton.setPreferredSize(new Dimension(30,50));
        searchPanel.add(searchButton,BorderLayout.SOUTH);

        JLabel searchTitle = new JLabel();
        searchTitle.setText("Search by program only or by all fields:");

        searchPanel.add(searchTitle,BorderLayout.NORTH);

        add(searchPanel);
        //create search panel

        //Create File Panel Display
        file  = new JPanel();
        file.setBorder(BorderFactory.createEmptyBorder(50, 50, 50, 50));
        file.setBackground(Color.CYAN);
        file.setVisible(false);
        file.setLayout(new BorderLayout());

        JLabel fileInstruct = new JLabel("Enter the name of the file. Then Press Load or Save");
        file.add(fileInstruct,BorderLayout.NORTH);

        JPanel fileInput = new JPanel();
        fileInput.setLayout(new BorderLayout());
        fileInput.setBackground(Color.CYAN);
        fileInput.setBorder(BorderFactory.createEmptyBorder(50, 0, 50, 0));
        guiFileName = new JTextField("default.txt",FILE_LENGTH);
        fileInput.add(guiFileName,BorderLayout.CENTER);
        file.add(fileInput,BorderLayout.CENTER);

        JPanel fileButtons = new JPanel();
        fileButtons.setSize(100,30);
        fileButtons.setBackground(Color.CYAN);
        fileButtons.setVisible(true);
        fileButtons.setLayout(new GridLayout(1,2));

        JPanel leftButton = new JPanel();
        leftButton.setLayout(new BorderLayout());
        leftButton.setBackground(Color.CYAN);
        leftButton.setBorder(BorderFactory.createEmptyBorder(0, 20, 20, 10));
        JButton fileSelectLoad = new JButton("Load from File");
        fileSelectLoad.setPreferredSize(new Dimension(30, 50));
        fileSelectLoad.addActionListener(new loadListener());
        leftButton.add(fileSelectLoad,BorderLayout.CENTER);

        JPanel rightButton = new JPanel();
        rightButton.setLayout(new BorderLayout());
        rightButton.setBackground(Color.CYAN);
        rightButton.setBorder(BorderFactory.createEmptyBorder(0, 10, 20, 20));
        JButton fileSelectSave = new JButton("Save to File");
        fileSelectSave.setPreferredSize(new Dimension(30, 50));
        fileSelectSave.addActionListener(new saveListener());
        rightButton.add(fileSelectSave,BorderLayout.CENTER);

        fileButtons.add(leftButton);
        fileButtons.add(rightButton);

        file.add(fileButtons,BorderLayout.SOUTH);

        add(file);
        //Create file panel display
    }

    public void newWindow(String message,int severity){//creates a disposable new window that contains a user message. Colored by entered severity 
    	JFrame win = new JFrame("NEW MESSAGE");
    	win.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);//able to close this and not the other window
    	win.setSize(message.length() * 8 + 50,75);
    	win.setVisible(true);
    	JPanel pan = new JPanel();
    	pan.setLayout(new FlowLayout());
    	//pan.setBorder(BorderFactory.createEmptyBorder(50, 50, 50, 50));
    	if(severity == 3){
    		pan.setBackground(Color.RED);
    	}else if(severity == 2){
    		pan.setBackground(Color.YELLOW);
    	}else if(severity == 1){
    		pan.setBackground(Color.GREEN);
    	}else{
    		pan.setBackground(Color.LIGHT_GRAY);
    	}
    	JLabel messageArea = new JLabel(message);
    	messageArea.setFont(new Font("Serif", Font.BOLD, 15));//Set font
    	pan.add(messageArea);
    	win.add(pan);
    }
}

//Assumptions: When calculating the total average of all the students, include the students with 0 averages.