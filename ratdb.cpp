#include <iostream>
#include <cstdlib>
#include <fstream> 

using namespace std;

char getch()
{
      char c; // This function should return the keystroke
      system("stty raw");    // Raw input - wait for only a single keystroke
      system("stty -echo");  // Echo off
      c = getchar();
      system("stty cooked"); // Cooked input - reset
      system("stty echo");   // Echo on - Reset
      return c;
}

struct person {
    string firstName;
    string lastName;
    short age;
    string tele;
};

short peopleInDataBase;
person people[20];

void requireEnter();
void addPerson();
void showPeople();
void savePeopleToFile();
void loadPeopleFromFile();
void searchDatabase();
void removePersonFromDatabase();

int main() {

    char test;

    do
    {
	cout << endl;
	cout << "		RatDb" << endl;
	cout << "    The beady red eyes of the horde stare back at you from the abyss, guarding their precious data and skittering about as they perform their infernal tasks." << endl << endl;
	cout << "Number of People in DataBase: " << peopleInDataBase << endl << endl;
        cout << "	MENU: " << endl;

        cout << "	1. CREATE" << endl;
        cout << "	2. READ" << endl;
	cout << "	3. SAVE" << endl;
	cout << "	4. LOAD" << endl;
        cout << "	5. SEARCH" << endl;
        cout << "	6. DELETE" << endl;

        cout << endl;

        cout << "                       Version:0.0.01(PoC)" << endl;

        test = getch();

        switch(test)
        {
            case '1':
                addPerson();
                break;
            case '2':
                showPeople();
                break;
	    case '3':
		savePeopleToFile();
		break;
            case '4':
                loadPeopleFromFile();
                break;
            case '5':
                searchDatabase();
                break;
            case '6':
                removePersonFromDatabase();
                break;
        }

        requireEnter();

        system ("clear");

    }while(test != 27);

    return 0;

}

//User must press Enter to proceed.
void requireEnter()
{
    cout << "Press Enter to Continue..." << endl;
    while(getch() != 13);
}

//Create, but not saved.
void addPerson()
{
    cout << "First Name: ";
    cin >> people[peopleInDataBase].firstName;

    cout << "Last Name: ";
    cin >> people[peopleInDataBase].lastName;

    cout << "Age: ";
    cin >> people[peopleInDataBase].age;

    cout << "Telephone #: ";
    cin >> people[peopleInDataBase].tele;

    peopleInDataBase++;
}

//Read
void showPeople()
{
    if (peopleInDataBase > 0)
    {
        for(int i = 0; i < peopleInDataBase; i++)
        {
            cout << "Person Index: " << (i+1) << endl;
	    cout << "First Name: " << people[i].firstName << endl;
            cout << "Last Name: " << people[i].lastName << endl;
            cout << "Age: " << people[i].age << endl;
            cout << "Tele: " << people[i].tele << endl << endl;
        }

    }
    else
        cout << "No Entries in Database." << endl;
}

//Save to file
void savePeopleToFile()
{
    fstream file("database.txt");

    if (file.is_open())
    {
        file << peopleInDataBase << endl;

        for (int i = 0; i < peopleInDataBase; i++)
        {
            cout << "Success!" << endl;
	    file << people[i].firstName << endl;
            file << people[i].lastName << endl;
            file << people[i].age << endl;
            file << people[i].tele << endl;
        }

        file.close();
    }
    else
        cout << "Unable to Save to Filesystem" << endl;

}

//Populate a new Db process with data from file.
void loadPeopleFromFile()
{
	ifstream file("database.txt");

	if (file.is_open())
	{
		file >> peopleInDataBase;

		if(peopleInDataBase > 0)
		{
		        for (int i = 0; i < peopleInDataBase; i++)
		        {
            		file >> people[i].firstName;
            		file >> people[i].lastName;
            		file >> people[i].age;
            		file >> people[i].tele;
        		}
                    cout << "Success!" << endl;
		}
		else
			cout << "File is Empty" << endl;
	}
	else
		cout << "No Such File" << endl;
}

//Locate by lastName
void searchDatabase()
{
	if (peopleInDataBase > 0)
	{
		string name;
		cout << "Search by Last Name: " << endl;
		cin >> name;

		for (int i = 0; i < peopleInDataBase; i++)
		{
			if(name == people[i].lastName)
			{
				cout << "Person Index: " << (i+1) << endl;
            			cout << "First Name: " << people[i].firstName << endl;
            			cout << "Last Name: " << people[i].lastName << endl;
            			cout << "Age: " << people[i].age << endl;
            			cout << "Tele: " << people[i].tele << endl << endl;	
			}
		} 

	}
	else
		cout << "Load File or Add Data" << endl;
}

//DELETE, by index
void removePersonFromDatabase()
{
	if (peopleInDataBase > 0)
	{
		short index;
		cout << "Remove Person by Index: " << endl;
		cin >> index;

		if(peopleInDataBase >= index) 
		{
			for (short k = index; k < peopleInDataBase; k++)
			{
				people[k-1].firstName = people[k].firstName;
                                people[k-1].lastName = people[k].lastName;
                                people[k-1].age = people[k].age;
                                people[k-1].tele = people[k].tele;;
			}
			peopleInDataBase--;
			savePeopleToFile();
		}
		else
			cout << "Invalid Request" << endl;
	}
	else
		cout << "No Data to DELETE" << endl;

}
