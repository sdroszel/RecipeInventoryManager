#include "RecipeManager.cpp"
#include "InventoryManager.cpp"

using namespace std;

/*
*  Thsi method contains the prompts for the main loop
*/
void Prompts(int& selInput)
{
    cout << endl;

    cout << "Please choose a selection:" << endl << endl;

    cout << "1) Create a new Recipe" << endl;

    cout << "2) Display recipe list" << endl;

    cout << "3) Display recipe" << endl;

    cout << "4) Add to inventory" << endl;

    cout << "5) Print inventory" << endl;

    cout << "0) Quit" << endl;

    cout << endl;

    cin >> selInput;
}

/*
*  This method creates a new recipe
*/
void CreateNewRecipe(std::string& recipeName, int& numOfIngredients, int& numOfSteps, RecipeManager& currentRecipe)
{
    cout << "\nEnter a recipe name: "
        ;
    cin.ignore();

    getline(cin, recipeName);

    recipeName = recipeName + ".txt";

    cout << "Enter total number of ingredients: ";

    cin >> numOfIngredients;

    cout << "Enter total number of steps: ";

    cin >> numOfSteps;

    cout << endl;

    currentRecipe.CreateNewRecipe(recipeName, numOfIngredients, numOfSteps);
}

/*
*  This method adds items to the inventory
*/
void AddItemToInventory(int& numOfItems, std::string& item, double& amount, double& cost, InventoryManager& inventory)
{
    cout << "Enter number of items to add to inventory: ";

    cin >> numOfItems;

    for (int i = 1; i <= numOfItems; i++)
    {
        cin.ignore();

        cout << "Enter item #" << i << ": ";

        getline(cin, item);

        transform(item.begin(), item.end(), item.begin(), ::tolower);

        cout << "Enter number of " << item << " to add: ";

        cin >> amount;

        cout << "Enter the cost per " << item << ": ";

        cin >> cost;

        inventory.AddToInventory(item, amount, cost);
    }

    inventory.UpdateInventoryFile();
}

int main()
{
    // local variables
    int selInput;
    int numOfIngredients;
    int numOfSteps;
    int numOfItems;
    double amount;
    double cost;
    string item;
    string recipeName;
    bool quit = false;
    
    InventoryManager inventory;
    RecipeManager currentRecipe;
    
    while (!quit)
    {
        Prompts(selInput);

        switch (selInput)
        {
        case 1:
            CreateNewRecipe(recipeName, numOfIngredients, numOfSteps, currentRecipe);
            break;

        case 2:
            currentRecipe.DisplayAll();
            break;

        case 3:
            currentRecipe.DisplayRecipe();
            break;

        case 4:
            AddItemToInventory(numOfItems, item, amount, cost, inventory);
            break;

        case 5:
            inventory.DisplayInventory();
            break;

        case 0:
            quit = true;
            break;

        default:
            cout << "Enter a valid command." << endl;
            break;
        }
    }
}