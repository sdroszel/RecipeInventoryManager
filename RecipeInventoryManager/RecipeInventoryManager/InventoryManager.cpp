#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class InventoryManager
{

private:

	// class variables
	ofstream fout;
	ifstream fin;
	string fileName = "inventory.txt";

	// used to create a single inventory item holding the name, amount and cost
	struct inventoryItem
	{
		string itemName = "";
		int amount = 0;
		double cost = 0;
	};

	// a vector that holds each inventoryItem created using the inventoryItem struct
	vector<inventoryItem> inventory;

	// writes the header for the inventory.txt file
	void WriteFileHeader()
	{
		fout.open(fileName, ios::app);

		fout << "Item" << "\t|Amount" << "|Cost" << endl << endl;

		fout.close();
	}

	// returns if the item is found in the inventory
	bool FoundInInventory(string item)
	{
		bool isFound = false;

		for (inventoryItem currentItem : inventory)
		{
			if (currentItem.itemName == item)
			{
				isFound = true;
			}
		}

		return isFound;
	}

	/*
	*  This method traverses each line of the inventory.txt
	*  file and puts each set of characters separated by a space
	*  into a vector.
	*/
	void ExtractInventoryTokens(std::string& line, std::vector<std::string>& tokenStream)
	{
		getline(fin, line);

		if (line.find('$') != string::npos)
		{
			istringstream buf(line);

			istream_iterator<string> beg(buf), end;

			vector<string> tokens(beg, end);

			for (string i : tokens)
			{
				// cout << i << endl;   (used to test the extraction of tokens)
				tokenStream.push_back(i);
			}
		}
	}

	/*
	*  Adds each line's tokens to the current index in the inventory vector.
	*/
	void AddTokensToInventory(std::vector<std::string>& tokenStream, int& i)
	{
		inventory.push_back(inventoryItem());

		int index = inventory.size() - 1;

		inventory.at(index).itemName = tokenStream[i];

		inventory.at(index).amount = stod(tokenStream[++i].substr(1));

		inventory.at(index).cost = stod(tokenStream[++i].substr(2));
	}

	/*
	*  When the program is launched and this method is called it will
	*  extract the inventory tokens from the inventory.txt file and add
	*  the tokens to the inventory vector.
	*/
	void SeedInventoryVector()
	{
		// local variables
		string line;
		string item;
		char amount = '\t';
		vector<string> tokenStream;

		fin.ignore();

		while (!fin.eof())
		{
			ExtractInventoryTokens(line, tokenStream);
		}

		for (int i = 0; i < tokenStream.size(); i++)
		{
			AddTokensToInventory(tokenStream, i);
		}
	}

	/*
	*  Adds a new inventoryItem to the inventory vector.
	*/
	void PushNewInventoryItem(std::string& item, double amount, double totalCost)
	{
		inventory.push_back(inventoryItem());

		int index = inventory.size() - 1;

		inventory.at(index).itemName = item;

		inventory.at(index).amount = amount;

		inventory.at(index).cost = totalCost;
	}

	/*
	*  If the item is found in the inventory this method adds the new
	*  amount and cost to the current amount and cost.
	*/
	void UpdateInventoryItem(std::string& item, double amount, double totalCost)
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			if (inventory.at(i).itemName == item)
			{
				int tempAmount = inventory.at(i).amount;

				double tempCost = inventory.at(i).cost;

				inventory.at(i).amount = tempAmount + amount;

				inventory.at(i).cost = (double)(tempCost + totalCost);
			}
		}
	}

	/*
	*  Method to rename the tempInventory.txt file to inventory.txt
	*/
	void RenameInventory(char  oldName[18], char  newName[14])
	{
		int value = rename(oldName, newName);

		if (!value)
		{
			cout << "File rename successful" << endl;
		}
		else
		{
			cout << "File rename failed" << endl;
		}
	}

	/*
	*  When an item has been added or updated this method will seed the updated inventory
	*  to the tempInventory.txt file.
	*/
	void TransferInventory()
	{
		fout.open("tempInventory.txt", ios::app);

		fout << "Item" << "\t| Amount" << "| Cost" << endl << endl;

		for (int i = 0; i < inventory.size(); i++)
		{
			fout << inventory.at(i).itemName << "\t|" << inventory.at(i).amount << "\t|$" << inventory.at(i).cost << endl;
		}
		fout.close();
	}

public:

	/*
	*  Constructor: if there is no inventory.txt file it will create one.
	*  If inventory.txt file is found it seeds the inventory vector.
	*/
	InventoryManager()
	{
		fin.open(fileName);

		if (!fin.is_open())
		{
			ofstream MyFile(fileName.c_str());

			WriteFileHeader();
		}
		else if (fin.is_open())
		{
			SeedInventoryVector();
		}

		fin.close();
	}

	/*
	*  This method adds items to the inventory vector.
	*  If item is not found it calls PushNewInventoryItem()
	*  If iten is found it calls UpdateInventoryItem()
	*/
	void AddToInventory(string item, double amount, double cost)
	{
		double totalCost = (double)(cost * amount);

		if (!FoundInInventory(item))
		{
			PushNewInventoryItem(item, amount, totalCost);
		}
		else if (FoundInInventory(item))
		{
			UpdateInventoryItem(item, amount, totalCost);
		}
	}

	/*
	*  This method updates the inventory.txt file after adding an item.
	*  It calls TransferInventory() to add the inventory vector items to a
	*  temp .txt file. The current inventory.txt file is removed and RenameInventory()
	*  is called to rename the temp file to inventory.txt
	*/
	void UpdateInventoryFile()
	{
		char oldName[] = "tempInventory.txt";

		char newName[] = "inventory.txt";

		TransferInventory();

		remove("inventory.txt");

		RenameInventory(oldName, newName);
	}

	/*
	*  This method would remove item from inventory.
	* 
	*  Low priority, will complete if time allows.
	*/
	//void RemoveFromInventory(string itemName, double total)
	//{

	//}

	/*
	*  This method opens the inventory.txt file and prints each
	*  line formatted to the console.
	*/
	void DisplayInventory()
	{
		fout.open(fileName, ios::app);

		cout << "\n\tInventory:\n" << endl;

		cout << "\t" << "Item" << "\t|Amount" << "\t|Cost" << endl << endl;

		for (int i = 0; i < inventory.size(); i++)
		{
			cout << "\t" << inventory.at(i).itemName << "\t|" << inventory.at(i).amount << "\t|$" << inventory.at(i).cost << endl;
		}

		fout.close();
	}

};