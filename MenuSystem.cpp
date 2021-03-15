//Simeon Eseyin
// Midterm Project: MenuSystem.cpp 
//October/16/2020

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void readfile(string Name[], double price[], ifstream &iFile, int &counter, int item_quantity[])
{
		while (!iFile.eof())
	{
		getline(iFile, Name[counter]);
		iFile>> price[counter];
		iFile >> item_quantity[counter];
		counter++;
		iFile.ignore();
	}
}

void openCheck(ifstream& iFile, string fileName)
{
	iFile.open(fileName);
	if (!iFile.is_open())
	{
		cout << "input file not found" << endl;
		cin.get();
		exit(1);
	}
}
void receipt(string Name, double price, int quantity, ofstream& oFile)
{
	oFile << "x" << quantity << " " << Name << " " << "@ " << "$" << price * quantity <<endl << endl;
}

void selection(string Name[],double &subtotal, double price[],int &counter, int quantity[], int item_quantity[], ofstream &oFile, string title)
{
	int choice = 0;
	int qty = 0;
	while (choice != 99)
	{
		system("cls");
		cout << "====Welcome to SimJoe's Steak 'n' Shake!!!=====" << endl << endl;
		cout << "Please select an item from our " << title << " Menu:" << endl << endl;
		for (int a = 0; a < counter; a++)
		{
			cout << a + 1 << ". " << Name[a] << " - $" << price[a] << endl;
			cout <<"Qty: "<< item_quantity[a] << endl << endl;
		}
		cout << "Subtotal: $" << subtotal << endl;
		cout << "Enter Selection (99 to exit): ";
		cin >> choice;
		
		if (choice != 99 && choice > 0 && choice <= counter && item_quantity[choice-1] > 0 )
		{
			cout << "Enter Quantity: ";
			cin >> qty;
			if (qty <= item_quantity[choice - 1])
			{
				item_quantity[choice - 1] = item_quantity[choice - 1] - qty;
				subtotal += price[choice - 1] * qty;
				receipt(Name[choice - 1], price[choice - 1], qty, oFile);
			}
			else
			{
				cout << "Out of Order! Please check the quantity and select again:" << endl;
				system("pause");
			}
		}
	}

	system("cls");
}

void payment(double &subtotal, double &paid, double total, double &tax, ofstream &oFile, double &tip, double &amount_due)
{
	tax *= subtotal;      
	
	cout << "Subtotal: $" << subtotal << endl;
	oFile << "Subtotal: $" << subtotal << endl;
	cout << "Tax: $" << tax << endl;
	oFile << "Tax: $" << tax << endl;
	cout << "Enter Tip Amount: $";
	cin >> tip;
	total = tax + subtotal + tip;
	cout << "Total: $" << total << endl;
	oFile << "Total: $" << total << endl;
	cout << "Enter Payment Amount: $";
	cin >> paid;
	oFile << "Tip: $" << tip << endl;
    double mod_paid = 0;
	while (paid < total)
	{
		cout << "Ooops!!! $" << total - paid << " is due today!" << endl;
		cout << "Please pay amount due: $";
		cin >> mod_paid;
		paid = mod_paid + paid;
	}
		cout << "Change Due: $" << paid - total << endl << endl;
		oFile << "Change Due: $" << paid - total << endl << endl;
		cout << "-----Thank You For Eating With Us!!!-----" << endl;
		oFile << "===================================================================" << endl;
		oFile << "****************Thank You For Eating With Us!!!********************" << endl;
		oFile << "===================================================================" << endl;
}	
int main()
{
	//declaring variables
	ifstream iFile1, iFile2, iFile3, iFile4;
	ofstream oFile;
	string Name1[100], Name2[100], Name3[100], Name4[100];
	double price1[100], price2[100], price3[100], price4[100], paid = 0, tip = 0, amount_due = 0;
	int item_quantity1[100], item_quantity2[100], item_quantity3[100], item_quantity4[100];
	int quantity1[100], quantity2[100], quantity3[100], quantity4[100];
	double subtotal = 0, tax = .10, total = 0;
	int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0, choice = 0, quantity = 0;

	//setting decimal points to 2 decimal points
	cout << fixed << showpoint << setprecision(2);
	oFile << fixed << showpoint << setprecision(2);

	oFile.open("receipt.txt");
	//calling functions to open files
	openCheck(iFile1, "Appetizers.txt");
	openCheck(iFile2, "Desserts.txt");
	openCheck(iFile3, "Entrees.txt");
	openCheck(iFile4, "DRINKS.txt");
	
	oFile << "===================================================================" << endl;
	oFile << "***************Welcome to SimJoe's Stake 'n' Shake*****************" << endl;
	oFile << "=========================YOUR ORDER================================="<< endl << endl;
	//calling functions to read files
	readfile(Name1, price1, iFile1, counter1, item_quantity1);
	readfile(Name2, price2, iFile2, counter2, item_quantity2);
	readfile(Name3, price3, iFile3, counter3, item_quantity3);
	readfile(Name4, price4, iFile4, counter4, item_quantity4);
	//calling functions to make selections, display output and print receipt
	selection(Name1, subtotal, price1, counter1, quantity1, item_quantity1, oFile,"Appetizers");
	selection(Name2, subtotal, price2, counter2, quantity2, item_quantity2, oFile, "Desserts");
	selection(Name3, subtotal, price3, counter3, quantity3, item_quantity3, oFile, "Entrees");
	selection(Name4, subtotal, price4, counter4, quantity4, item_quantity4, oFile, "DRINKS");
	//calling functions to calculate payments due
	payment(subtotal, paid, total, tax, oFile, tip, amount_due);
	
	iFile1.close();
	iFile2.close();
	iFile3.close();
	iFile4.close();
	return 0;
}