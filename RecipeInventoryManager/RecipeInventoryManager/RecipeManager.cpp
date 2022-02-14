#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class RecipeManager
{
private:

	// private variables
	string recipeName;
	ofstream fout;
	ifstream fin;
	vector<string> recipeList;
	
	/*
	*  This method writes the recipe name section
	*  of the recipe .txt file.
	*/
	void WriteRecipeHeader(string name)
	{
		fout << "Recipe Name:" << endl << endl;

		fout << "\t" << name.substr(0, name.length() - 4);

		fout << endl << endl;
	}

	/*
	*  This method writes the ingredients section
	*  of the recipe .txt file.
	*/
	void WriteIngredients(int numOfIngredients)
	{
		// local vaiables
		string input;

		fout << "Ingredients:" << endl << endl;

		cout << "Enter ingredients" << endl;

		cin.ignore();

		for (int i = 1; i <= numOfIngredients; i++)
		{
			cout << "Enter ingredient #" << i << ": ";

			getline(cin, input);

			fout << "\t- " << input << endl;;
		}
	}

	/*
	*  This method writes the instruction section
	*  of the recipe .txt file.
	*/
	void WriteInstructions(int numOfInstructions)
	{
		// local vaiables
		string input;

		fout << endl;

		fout << "Instructions:" << endl << endl;

		cout << "Enter instructions:" << endl;

		for (int i = 1; i <= numOfInstructions; i++)
		{
			cout << "Enter instruction #" << i << ": ";

			getline(cin, input);

			fout << "\t" << i << ". " << input << endl;
		}
	}

	/*
	*  This method trasnfers the recipe names from the
	*  recipeList vector and writes it to texp .txt file.
	*/
	void TransferRecipeList(std::ofstream& MyFile)
	{
		for (int i = 0; i < recipeList.size(); i++)
		{
			MyFile << recipeList.at(i) << endl;
		}

		MyFile.close();
	}

	/*
	*  This method renames the temp .txt file to recipeList.txt
	*/
	void RenameRecipeList(char  oldName[19], char  newName[15])
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
	*  When called, this method calls TransferRecipeList(),
	*  removes the current recipeList.txt file and calls
	*  RenameRecipeList().
	*/
	void ReWriteRecipeList()
	{
		// local vaiables
		char oldName[] = "tempRecipeList.txt";
		char newName[] = "recipeList.txt";
		ofstream MyFile(oldName);

		TransferRecipeList(MyFile);

		remove("recipeList.txt");

		RenameRecipeList(oldName, newName);
	}

	/*
	*  The method is called when the program launches and
	*  recipeList.txt is found. Reads each line of the file
	*  and stores it in a vector.
	*/
	void SeedRecipeList()
	{
		// local vaiables
		string line;

		while (!fin.eof())
		{
			getline(fin, line);

			if (line != "")
			{
				recipeList.push_back(line);
			}
		}
	}

	/*
	*  This method is called when the program starts. If
	*  recipeList.txt is not found it creates a new .txt file.
	*/
	void CreateRecipeListFile()
	{
		ofstream MyFile("recipeList.txt");

		MyFile.close();
	}

public:

	/*
	*  Default constructor. Run at the start of program
	*  to handle the recipeList.txt file.
	*/
	RecipeManager()
	{
		fin.open("recipeList.txt");

		if (!fin.is_open())
		{
			CreateRecipeListFile();
		}
		else if (fin.is_open())
		{
			SeedRecipeList();
		}
		fin.close();
	}

	/*
	*  Constructor to create a new instance of a recipe.
	*/
	RecipeManager(string name)
	{
		recipeName = name;

		transform(recipeName.begin(), recipeName.end(), recipeName.begin(), ::tolower);

		fin.open(recipeName);

		if (!fin.is_open())
		{
			ofstream MyFile(recipeName);
		}

		fin.close();
	}

	/*
	*  Method to seed the new recipe file with header, ingredients, and instructions.
	*/
	void CreateNewRecipe(string name, int numOfIngredients, int numOfSteps)
	{
		fout.open(name);

		recipeList.push_back(name);

		ReWriteRecipeList();

		WriteRecipeHeader(name);

		WriteIngredients(numOfIngredients);

		WriteInstructions(numOfSteps);

		fout.close();
	}

	/*
	*  This method would search for available recipes
	*  and display only recipes that contain searched term.
	*
	*  Low priority, will complete if time allows.
	*/
	//void SearchRecipes(string searchTerm)
	//{

	//}

	/*
	*  This method displays a current list of all recipes
	*  to the console.
	*/
	void DisplayAll()
	{
		cout << "\n\tRecipe List:" << endl << endl;

		for (int i = 0; i < recipeList.size(); i++)
		{
			cout << "\t" << recipeList.at(i).substr(0, recipeList.at(i).length() - 4) << endl;
		}
	}

	/*
	*  This method would search for available recipes
	*  and display only recipes that contain available inventory items.
	*
	*  Low priority, will complete if time allows.
	*/
	//void DisplayAvailable()
	//{
	//	
	//}

	/*
	*  This method displays a recipe to the console based
	*  on search term.
	*/
	void DisplayRecipe()
	{
		// local vaiables
		string recipeInput;
		string line;

		cin.ignore();

		cout << "\nEnter a recipe name to display: ";

		getline(cin, recipeInput);

		recipeInput = recipeInput + ".txt";

		transform(recipeInput.begin(), recipeInput.end(), recipeInput.begin(), ::tolower);

		fin.open(recipeInput);

		cout << endl;

		while (!fin.eof())
		{
			getline(fin, line);

			cout << line << endl;
		}

		fin.close();
	}
};