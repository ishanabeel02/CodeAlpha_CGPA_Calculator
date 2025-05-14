#include <iostream>
#include <iomanip>
#include <windows.h> 
#include <algorithm>
#include <limits>

using namespace std;

// Node structure to store information about each course
struct Node
{
    float points;        
    int credit_hours;   
    string grades;       
    Node* next;         
};

// Linkedlist class to manage the list of courses
class Linkedlist
{
private:
    Node* head;         
public:
    // Constructor to initialize the head pointer to NULL (empty list)
    Linkedlist()
    {
        head = NULL;
    }

    // Set the head of the linked list 
    void setHead(Node* newhead)
    {
        head = newhead;
    }

    // Get the head of the linked list 
    Node* getHead()
    {
        return head;
    }

    // Function to add a node (course) to the front of the linked list
    void add_To_front(int new_value, float point, string grade = "--")
    {
        Node* newnode = new Node; 
        newnode->credit_hours = new_value;
        newnode->grades = grade;
        newnode->points = point;
        newnode->next = head;     
        head = newnode;          
    }

    // Function to delete a course from the list based on grade
    void delete_from_list(string value)
    {
        Node* current = head;
        Node* previous = NULL;

        // Traverse the list to find the course with the specified grade
        while (current != NULL && current->grades != value)
        {
            previous = current;
            current = current->next;
        }

        // If the course wasn't found
        if (current == NULL)
        {
            cout << "Value not found in the list." << endl;
            return;
        }
        else
        {
            // If the course to delete is the head
            if (previous == NULL)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next; 
            }
            delete current; 
        }
    }

    // Recursive function to display the points for each course in the list
    void recursive_display(Node* head)
    {
        if (head == NULL) 
        {
            cout << "NULL" << endl;
            return;
        }
        cout << head->points << " --> "; 
        recursive_display(head->next);    
    }
	void clear() 
	{
	    Node* current = head;
	    while (current != NULL) 
		{
	        Node* temp = current;
	        current = current->next;
	        delete temp;
	    }
	    head = NULL; 
	}

    // Destructor to free all dynamically allocated nodes in the list
    ~Linkedlist()
    {
        Node* current = head;
        while (current != NULL)
        {
            Node* temp = current;
            current = current->next;
            delete temp; 
    	}
    }
};

// CGPA_Calculator class to calculate GPA and CGPA based on courses in linked lists
class CGPA_Calculator
{
private:
    Linkedlist l2; 
public:
    // Function to convert grade to grade points and add the course to the linked list
    float grade_points(int hour, string grade, Linkedlist& l)
    {
        float gpa = 0.0;

        // Assign grade points based on the grade
        if (grade == "A") gpa = 4.0;
        else if (grade == "A-") gpa = 3.70;
        else if (grade == "B+") gpa = 3.33;
        else if (grade == "B") gpa = 3.0;
        else if (grade == "B-") gpa = 2.70;
        else if (grade == "C+") gpa = 2.33;
        else if (grade == "C") gpa = 2.0;
        else if (grade == "C-") gpa = 1.70;
        else if (grade == "F") gpa = 0.0;
        else {
            cout << "Invalid grade entered!\n";
            return 0;
        }

        // Add the course (with grade points) to the linked list
        l.add_To_front(hour, gpa * hour, grade);
        return gpa * hour; 
    }
    Linkedlist &list()
    {
    	return l2;
	}
    // Function to calculate GPA from the courses in the linked list
    float GPA_Calculator(Linkedlist& l)
    {
        float total = 0.0;
        int total_hour = 0;
        Node* temp = l.getHead();

        // Traverse the list to calculate total points and total credit hours
        while (temp != NULL)
        {
            total += temp->points;
            total_hour += temp->credit_hours;
            temp = temp->next;
        }

        // Avoid division by zero if there are no courses
        if (total_hour == 0) return 0.0;

        // Add the result to the second linked list
        l2.add_To_front(total_hour, (total / total_hour));

        return total / total_hour; // Return the GPA
    }

    // Function to calculate CGPA from all GPA calculations
    float CGPA_Calculators()
    {
        float total = 0.0;
        int total_hour = 0;
        Node* temp = l2.getHead();

        // Traverse the list to calculate total points and total credit hours for CGPA
        while (temp != NULL)
        {
            total_hour += temp->credit_hours;
            total += (temp->points * temp->credit_hours);
            temp = temp->next;
        }

        // Avoid division by zero if no GPA calculations are available
        if (total_hour == 0) return 0.0;

        return total / total_hour; // Return the CGPA
    }
    // To Print the current table 
    	void print(int &subject, int Credit_hour, float GPA, string Grade, bool &header) 
		{
			//print the headings for table (Check condition to print it just once)
	        if (!header) 
			{
				cout << endl << endl;
				cout<< setw(13) << setfill(' ') << "Subject";
				cout<< setw(22) << setfill(' ') << "Credit Hours";
				cout<< setw(20) << setfill(' ') << "Grade";
				cout<< setw(15) << setfill(' ') << "GPA" << endl;
	            cout << "--------------------------------------------------------------------------------\n";
	            header = true; 
	        }
	        
        // Print the stack, Expression, and symbol
        cout<< setw(9) << setfill(' ') << subject << setw(9) << setfill(' ') << "          |" << setw(10) << setfill(' ') << Credit_hour << setw(10) << setfill(' ');
        cout << " | " << setw(10) << setfill(' ') << Grade << setw(10) << setfill(' '); 
        cout<< setw(10) << setfill(' ') << " |\t" << setw(8) << setfill(' ') << GPA << setw(8) << setfill(' ') << "  |" << endl;
        subject++;
    	}
    	void print2(int &Semester, int Credit_hours, float GPA, bool &header) 
		{
			//print the headings for table (Check condition to print it just once)
	        if (!header) 
			{
				cout << endl << endl;
				cout<< setw(20) << setfill(' ') << "Semester";
				cout<< setw(30) << setfill(' ') << "Credit Hours";
				cout<< setw(20) << setfill(' ') << "GPA" << endl;
	            cout << "--------------------------------------------------------------------------------\n";
	            header = true; 
	        }
	        
        // Print the stack, Expression, and symbol
        cout<< setw(15) << setfill(' ') << Semester << setw(12) << setfill(' ') << "\t   |" << setw(15) << setfill(' ') << Credit_hours << setw(10) << setfill(' ');
        cout<< setw(15) << setfill(' ') << " |\t" << setw(8) << setfill(' ') << GPA << setw(8) << setfill(' ') << "|" << endl;
        Semester++;
    	}
    	void display_gpa(Linkedlist &s1, bool h = true)
    	{
    		Node *temp = s1.getHead();
    		int hours = 0;
    		bool header = false;
    		int sem = 1;
    		if (temp == NULL) 
			{
			    cout << "The list is empty.\n";
			    return;
			};
    		while(temp != NULL)
    		{
    			print(sem, temp->credit_hours, temp->points,temp->grades, header);
    			hours+= temp->credit_hours;
				temp = temp->next;	
			}
			if(!h)
			{
				cout << "--------------------------------------------------------------------------------\n";
				cout << "\t\tTOTAL GPA: " << GPA_Calculator(s1) << "     | \t" << "Total Credit Hours: " << hours << "\t  \t       |" << endl;
				cout << "--------------------------------------------------------------------------------\n";
			}
			else
			{
				cout << "--------------------------------------------------------------------------------\n";
			}
		}
		void display_cgpa()
    	{
    		Node *temp = l2.getHead();
    		int hours = 0;
    		bool header = false;
    		int sem = 1;
    		while(temp != NULL)
    		{
    			print2(sem, temp->credit_hours, temp->points, header);
    			hours+= temp->credit_hours;
				temp = temp->next;	
			}
			cout << "--------------------------------------------------------------------------------\n";
			cout << "\t\tTOTAL GPA: " << CGPA_Calculators() << "     | \t" << "Total Credit Hours: " << hours << "\t  \t       |" << endl;
			cout << "--------------------------------------------------------------------------------\n";
		}
};


//To Set color
void setColor(int color)
{
   	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   	SetConsoleTextAttribute(hConsole, color);
}

	
void bye()
{
	for(int i = 0; i <= 15; i++) 
	{
        
		setColor(i);
        cout << "\t\t\t\tTTTTT  H   H  AAAAA  N   N  K   K    U   U" << endl;
	    cout << "\t\t\t\t  T    H   H  A   A  NN  N  K  K     U   U" << endl;
	    cout << "\t\t\t\t  T    HHHHH  AAAAA  N N N  K K      U   U" << endl;
	    cout << "\t\t\t\t  T    H   H  A   A  N  NN  KK       U   U" << endl;
	    cout << "\t\t\t\t  T    H   H  A   A  N   N  K  K     U   U" << endl;
	    cout << "\t\t\t\t  T    H   H  A   A  N   N  K   K    UUUUU" << endl;
        
        Sleep(300); 
    }
}

void display_menu()
{
					cout<< "--------------------------------------\n"
			            << "|                Menu                |\n"
			            << "--------------------------------------\n"
			            << "|  1. Enter a new subject            |\n"
			            << "|  2. Calculate GPA                  |\n"
			            << "|  3. Reset                          |\n"
			            << "|  4. Exit                           |\n"
			            << "--------------------------------------\n";
}
void display_menu2()
{
					cout<< "--------------------------------------\n"
			            << "|                Menu                |\n"
			            << "--------------------------------------\n"
			            << "|  1. Enter a new semester gpa       |\n"
			            << "|  2. Calculate CGPA                 |\n"
			            << "|  3. Reset                          |\n"
			            << "|  4. Exit                           |\n"
			            << "--------------------------------------\n"
			            << "Enter your choice: ";
}
// Main function to test the CGPA calculator
int main()
{
	setColor(3);
    cout << "\t\t\t\t\tW     W  EEEEE  L        CCCC  OOO   M     M  EEEEE  \n";
    cout << "\t\t\t\t\tW     W  E      L       C     O   O  MM   MM  E     \n";
    cout << "\t\t\t\t\tW W W W  EEEE   L      C      O   O  M M M M  EEEE  \n";
    cout << "\t\t\t\t\tW W W W  E      L       C     O   O  M     M  E     \n";
    cout << "\t\t\t\t\t W W W   EEEEE  LLLLLL   CCCC  OOO   M     M  EEEEE  \n";
    cout << endl;
    cout << "\t\t\t\t     ===========================================================" << endl;
    cout << "\t\t\t\t 		 G P A  &  C G P A    C A L C U L A T O R " << endl;
    cout << "\t\t\t\t     ===========================================================" << endl;
    setColor(15);
    //Variables
    int choice;
	int option = 1;
    CGPA_Calculator c;
    Linkedlist Semester[8];
    int j, i = 0;
    int c_h;
    float gpa;
    string g;
    bool h1, h2 = false;
    //loop to replay
    while(true)
    {	
    	cout<< "--------------------------------------\n"
            << "|                Menu                |\n"
            << "--------------------------------------\n"
            << "|  1. Calculate GPA                  |\n"
            << "|  2. Calculate CGPA                 |\n"
            << "|  3. Exit                           |\n"
            << "--------------------------------------\n"
            << "Enter your choice: ";
            cin>>choice;
    	
    	switch(choice)
    	{
    		case 1:
    			{
    				B:
	    				Linkedlist &s = Semester[i];
	    				option = 1;
    				do
    				{
    					if (option == 1)
						{
						    bool validInput = false;
						    // Validate Credit Hours (should be between 1 and 6)
						    while (!validInput) 
							{
						        cout << "Enter the Credit hours of the subject (1-6): ";
						        cin >> c_h;
						        if (cin.fail() || c_h < 1 || c_h > 6)
								{
						            cin.clear(); 
						            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
						            cout << "Invalid input! Credit hours should be between 1 and 6." << endl;
						        } 
								else 
								{
						            validInput = true;
						        }
						    }
						
						    validInput = false; 
						    // Validate Grade
						    while (!validInput) 
							{
						        cout << "Enter the Grade of the subject: \n['A', 'A-', 'B+', 'B', 'B-', 'C+', 'C', 'C-', 'F'] \n >>>>>  ";
						        cin >> g;
						        transform(g.begin(), g.end(), g.begin(), ::toupper); 
						
						        // Check if grade is valid
						        if (g == "A" || g == "A-" || g == "B+" || g == "B" || g == "B-" || g == "C+" || g == "C" || g == "C-" || g == "F") 
								{
						            validInput = true;
						        } 
								else 
								{
						            cout << "Invalid grade! Please enter a valid grade from the list." << endl;
						        }
						    }
						    c.grade_points(c_h, g, s);
						    c.display_gpa(s);
						    cout << "\n\n" << endl;
						}

						else if(option == 2)
						{
							c.display_gpa(s, false);
							cout << "\n\n" << endl;
						}
						else if(option == 3)
						{
							i++;
							goto B;
						}
						else if(option == 4)
						{
							break;
						}
    					else
    					{
    							cout << "===========================================================" << endl;
								cout << "                     Invalid choice                        " << endl;
								cout << "===========================================================" << endl;
						}
    					display_menu();
						cout << "Enter your choice >>> ";;
			            cin>>option;
    					
					}while(option != 4 && i < 8);
					i++;
			        break;		
				}
			case 2:
				{
				    if (i != 0) 
					{
				        cout << "\nYou have already calculated a GPA.\n";
				        cout << "Do you want to use the previous GPA or enter a new one?\n";
				        cout << "1. Use existing GPA\n";
				        cout << "2. Enter a new GPA\n";
				        cout << ">>> ";
				        cin >> option;
				
				        if (option == 1) 
						{
				            c.display_cgpa();
				            cout << "\n\n";
				            break;
				        }
				    }
				
				    Linkedlist& List = c.list();
				
				    // Display secondary menu
				    display_menu2();
				    cin >> option;
				
				    do {
				        switch (option) 
						{
				            case 1:
				                cout << "\n> Please enter your GPA: ";
				                cin >> gpa;
				                cout << "> Enter corresponding Credit Hours: ";
				                cin >> c_h;
				                List.add_To_front(c_h, gpa);
				                j++;
				                break;
				
				            case 2:
				                c.CGPA_Calculators();
				                c.display_cgpa();
				                cout << "\n\n";
				                break;
				
				            case 3:
				                List.clear();
				                cout << ">> List cleared successfully.\n";
				                break;
				
				            case 4:
				                cout << "\n====================== E X I T I N G ======================\n";
				                break;
				
				            default:
				                cout << "\n===========================================================\n";
				                cout << "                    ?? Invalid Choice                     \n";
				                cout << "===========================================================\n";
				                break;
				        }
				
				        if (option != 4 && j < 8) 
						 {
				            display_menu2();
				            cin >> option;
				        }
				
				    } while (option != 4 && j < 8);
				
				    break;
				}

			case 3:
				{
					cout << "========================== E X I T I N G =========================== \n" << endl;
					bye();
					return 0;
				}
			default:
				{
					cout << "===========================================================" << endl;
					cout << "                      Invalid Input!                       " << endl;
					cout << "===========================================================" << endl;
					break;
				}
    			
    		
		}
	}
    return 0;
}
