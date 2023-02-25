#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>

class RandomActors
{
    protected:
        //number of random actors (132 in this case)
        int dim = 132;
        std::vector <std::string> random_names;
        std::vector <std::string> random_type_of_menu;
    
    public:
        RandomActors() = default;
        void generateData();
        void writeData();
        ~RandomActors() = default;
};

void RandomActors::generateData()
{   

    std::vector<std::string> male_first_names = {"John", "James", "Michael", "David", "William", "Robert", "Joseph", "Richard", "Charles", "Thomas"};

    std::vector<std::string> female_first_names = {"Mary", "Patricia", "Elizabeth", "Jennifer", "Linda", "Barbara", "Susan", "Jessica", "Sarah", "Karen"};

    std::vector<std::string> male_last_names = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"};

    
    std::vector<std::string> female_last_names = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"};

    
    std::vector<std::string> type_of_menu = {"normal", "vegetarian", "flexitarian"};

    std::random_device rng;

    // Generate 132 random names
    for (int i = 0; i < dim; i++) 
    {
        // Create a string to store the full name
        std::string full_name;

        // Choose a random first name from either the male or female list
        std::string first_name;

        if (rng() % 2 == 0)
        {
            first_name = male_first_names[rng() % male_first_names.size()];
        }
        else
        {
            first_name = female_first_names[rng() % female_first_names.size()];
        }

        // Choose a random last name from either the male or female list
        std::string surname;

        if (rng() % 2 == 0) 
        {
            surname = male_last_names[rng() % male_last_names.size()];
        }
        else 
        {
            surname = female_last_names[rng() % female_last_names.size()];
        }

        full_name = first_name + " " + surname;

        //choose a random type of meal
        std::string type_of_meal;
        type_of_meal = type_of_menu[rng() % type_of_menu.size()];

        // Add the first and last name to the matrix
        random_names.push_back(full_name);
        random_type_of_menu.push_back(type_of_meal);

        // Write the data to the file
        writeData();
    }
}

// Write the data to the file "random_actors.csv"
void RandomActors::writeData()
{   
    std::ofstream fout;
    fout.open(".//data//cast and random actors//random_actors.csv");

    if(!fout.is_open())
    {
        std::cout << "Error opening random_actors.csv in writeData()" << std::endl;
        return;
    }

    for(int i = 0; i < random_names.size(); i++)
    {
        fout << random_names.at(i) << "," << "actor/actress" << "," << random_type_of_menu.at(i) << "\n";
    }

    fout.close();
}

class Cast : protected RandomActors
{
    private:
        std::vector <std::string> cast_names;
        std::vector <std::string> cast_jobs;
        std::vector <std::string> cast_menu;
        int cast_size;

    public:
        Cast() = default;
        void readData();
        void setMenu();
        void writeData();
        ~Cast() = default;
        //it is necessary to make the class Cost a friend class in order to access the private members of the class Cast
        friend class Cost;   
    
};

//read the data from the file "wednesdayCast.csv" and sets the menu type for each memeber of the cast
void Cast::readData()
{
    std::string row;
    std::string aux;
    std::ifstream fin;

    fin.open(".//data//cast and random actors//wednesdayCast.csv", std::ios::in);

    if(!fin.is_open())
    {
        std::cout << "Error opening wednesdayCast.csv int readData()" << std::endl;
        return;
    }

    while(std::getline(fin, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        cast_names.push_back(aux);

        std::getline(sin, aux, ',');
        cast_jobs.push_back(aux);
    }

    fin.close();

    setMenu();
}

//sets the menu type for each memeber of the cast
void Cast::setMenu()
{
    std::vector<std::string> type_of_menu = {"normal", "vegetarian", "flexitarian"};
    std::random_device rng;

    for (int i = 0; i < cast_names.size(); i++) 
    {
        std::string type_of_meal;
        type_of_meal = type_of_menu[rng() % type_of_menu.size()];

        cast_menu.push_back(type_of_meal);
    }
}

//write the data to the file "new_Wednesday_cast.csv"
void Cast::writeData()
{
    std::ofstream fout;
    fout.open(".//data//new_Wednesday_cast.csv");

    if(!fout.is_open())
    {
        std::cout << "Error opening new_Wednesday_cast.csv in writeData()" << std::endl;
        return;
    }

    for(int i = 0; i < cast_names.size(); i++)
    {
        fout << cast_names.at(i) << "," << cast_jobs.at(i) << "," << cast_menu.at(i) << "\n";
    }

    generateData();
    for(int i = 0; i < random_names.size(); i++)
    {
        fout << random_names.at(i) << "," << "actor/actress" << "," << random_type_of_menu.at(i) << "\n";
    }

    fout.close();

    cast_size = random_names.size() + cast_names.size();
}


class Actors
{
    private:
        std::vector <std::string> actors_names;
        std::vector <std::string> actors_roles;

    public:
        Actors() = default;
        void readData();
        void writeData();
        ~Actors() = default;
};

//read the data from the file "new_Wednesday_cast.csv" and sets roles for each memeber of the actors
void Actors::readData()
{   
    std::random_device rng;

    std::vector <std::string> roles =  {"Vampire", "Werewolf", "Mermaid", "Clairvoyant", "Human"};

    std::vector <std::string> all_cast_menu, all_cast_jobs, all_cast_names;
    std::string row;
    std::string aux;
    std::ifstream fin;

    fin.open(".//data//new_Wednesday_cast.csv", std::ios::in);

    if(!fin.is_open())
    {
        std::cout << "Error opening new_Wednesday_cast.csv in readData()" << std::endl;
        return;
    }

    while(std::getline(fin, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        all_cast_names.push_back(aux);

        std::getline(sin, aux, ',');
        all_cast_jobs.push_back(aux);

        std::getline(sin, aux, ',');
        all_cast_menu.push_back(aux);
    }

    fin.close();

    for(int i = 0; i < all_cast_names.size(); i++)
    {
        if(all_cast_jobs.at(i).find("actor/actress") != std::string::npos)
        {
            actors_roles.push_back(roles[rng() % roles.size()]);
            actors_names.push_back(all_cast_names.at(i));
        }
    }

    writeData();
}

//write the data to the file "actors_list.csv"
void Actors::writeData()
{
    std::ofstream fout;
    fout.open(".//data//cast and random actors//actors_list.csv");

    if(!fout.is_open())
    {
        std::cout << "Error opening actors_list.csv in writeData()" << std::endl;
        return;
    }

    for(int i = 0; i < actors_names.size(); i++)
    {
        fout << actors_names.at(i) << "," << actors_roles.at(i) << "\n";
    }

    fout.close();
}

class Menu
{
    private:
        std::vector <std::string> normal_soups;
        std::vector <std::string> vegetarian_soups;
        std::vector <std::string> flexitarian_soups;

        std::vector <std::string> normal_main_courses;
        std::vector <std::string> vegetarian_main_courses;
        std::vector <std::string> flexitarian_main_courses;

        std::vector <std::string> normal_desserts;
        std::vector <std::string> vegetarian_desserts;
        std::vector <std::string> flexitarian_desserts;

        std::random_device rng;

    public:
        Menu() = default;
        void writeDataEN();
        void writeDataRO();
        void setMenu();
        ~Menu() = default;
};

//read the data from the CSV files from menus folder for each type of dish (soup, main course, desser) and create 2 menus for each type of meals(non-vegetarian, vegetarian, flexitarian)
//write the data to the file "menus_list_EN.csv" in English
void Menu::writeDataEN()
{
    //there are 10 types of dishes for each type of dish. Will be chosen 2 randomly for each type of menu
    std::string row;
    std::string aux;

    std::ifstream fin1;
    fin1.open(".//data//menus//soups_list_EN.csv", std::ios::in);

    if(!fin1.is_open())
    {
        std::cout << "Error opening soups_list_EN.csv in writeData()" << std::endl;
        return;
    }

    while(std::getline(fin1, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        normal_soups.push_back(aux);

        std::getline(sin, aux, ',');
        vegetarian_soups.push_back(aux);

        std::getline(sin, aux, ',');
        flexitarian_soups.push_back(aux);
    }

    normal_soups.erase(normal_soups.begin());
    vegetarian_soups.erase(vegetarian_soups.begin());
    flexitarian_soups.erase(flexitarian_soups.begin());

    fin1.close();


    std::ifstream fin2;
    fin2.open(".//data//menus//main_courses_list_EN.csv", std::ios::in);

    if(!fin2.is_open())
    {
        std::cout << "Error opening main_courses_list_EN.csv in writeData()" << std::endl;
        return;
    }

    while(std::getline(fin2, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        normal_main_courses.push_back(aux);

        std::getline(sin, aux, ',');
        vegetarian_main_courses.push_back(aux);

        std::getline(sin, aux, ',');
        flexitarian_main_courses.push_back(aux);
    }

    normal_main_courses.erase(normal_main_courses.begin());
    vegetarian_main_courses.erase(vegetarian_main_courses.begin());
    flexitarian_main_courses.erase(flexitarian_main_courses.begin());

    fin2.close();


    std::ifstream fin3;
    fin3.open(".//data//menus//desserts_list_EN.csv", std::ios::in);

    if(!fin3.is_open())
    {
        std::cout << "Error opening desserts_list_EN.csv in writeData()" << std::endl;
        return;
    }

    while(std::getline(fin3, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        normal_desserts.push_back(aux);

        std::getline(sin, aux, ',');
        vegetarian_desserts.push_back(aux);

        std::getline(sin, aux, ',');
        flexitarian_desserts.push_back(aux);
    }

    normal_desserts.erase(normal_desserts.begin());
    vegetarian_desserts.erase(vegetarian_desserts.begin());
    flexitarian_desserts.erase(flexitarian_desserts.begin());

    fin3.close();
   
    std::ofstream fout;
    fout.open(".//data//menu_EN.csv");

    if(!fout.is_open())
    {
        std::cout << "Error opening menu_EN.csv in writeData()" << std::endl;
        return;
    }

    fout << "Dish type" << "," << "Non-vegetarian menu" << "," << "Vegetarian menu" << "," << "Flexitarian menu\n" << "\n";

    for(int i = 0; i < 2; i++)
    {
        fout << "Soup" << "," << normal_soups[rng() % normal_soups.size()] << "," << vegetarian_soups[rng() % vegetarian_soups.size()] << "," << flexitarian_soups[rng() % flexitarian_soups.size()] << "\n";
        fout << "Main Course" << "," << normal_main_courses[rng() % normal_main_courses.size()] << "," << vegetarian_main_courses[rng() % vegetarian_main_courses.size()] << "," << flexitarian_main_courses[rng() % flexitarian_main_courses.size()] << "\n";
        fout << "Dessert" << "," << normal_desserts[rng() % normal_desserts.size()] << "," << vegetarian_desserts[rng() % vegetarian_desserts.size()] << "," << flexitarian_desserts[rng() % flexitarian_desserts.size()] << "\n";
        fout << "\n";
    }

    normal_soups.clear();
    normal_main_courses.clear();
    normal_desserts.clear();

    vegetarian_soups.clear();
    vegetarian_main_courses.clear();
    vegetarian_desserts.clear();

    flexitarian_soups.clear();
    flexitarian_main_courses.clear();
    flexitarian_desserts.clear();

    fout.close();
}

//write the menu in the file menu_RO.csv in Romanian language
void Menu::writeDataRO()
{
    //there are 10 menu for each type of meal. Will be chosen 2 randomly for each type of meal
    std::string row;
    std::string aux;

    std::ifstream fin1;
    fin1.open(".//data//menus//soups_list_RO.csv", std::ios::in);

    if(!fin1.is_open())
    {
        std::cout << "Error opening soups_list_RO.csv in writeData()" << std::endl;
        return;
    }

    while(std::getline(fin1, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        normal_soups.push_back(aux);

        std::getline(sin, aux, ',');
        vegetarian_soups.push_back(aux);

        std::getline(sin, aux, ',');
        flexitarian_soups.push_back(aux);
    }

    normal_soups.erase(normal_soups.begin());
    vegetarian_soups.erase(vegetarian_soups.begin());
    flexitarian_soups.erase(flexitarian_soups.begin());

    fin1.close();


    std::ifstream fin2;
    fin2.open(".//data//menus//main_courses_list_RO.csv", std::ios::in);

    if(!fin2.is_open())
    {
        std::cout << "Error opening main_courses_list_RO.csv in writeData()" << std::endl;
        return;
    }

    while(std::getline(fin2, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        normal_main_courses.push_back(aux);

        std::getline(sin, aux, ',');
        vegetarian_main_courses.push_back(aux);

        std::getline(sin, aux, ',');
        flexitarian_main_courses.push_back(aux);
    }

    normal_main_courses.erase(normal_main_courses.begin());
    vegetarian_main_courses.erase(vegetarian_main_courses.begin());
    flexitarian_main_courses.erase(flexitarian_main_courses.begin());

    fin2.close();


    std::ifstream fin3;
    fin3.open(".//data//menus//desserts_list_RO.csv", std::ios::in);

    if(!fin3.is_open())
    {
        std::cout << "Error opening desserts_list_RO.csv in writeData()" << std::endl;
        return;
    }

    while(std::getline(fin3, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        normal_desserts.push_back(aux);

        std::getline(sin, aux, ',');
        vegetarian_desserts.push_back(aux);

        std::getline(sin, aux, ',');
        flexitarian_desserts.push_back(aux);
    }

    normal_desserts.erase(normal_desserts.begin());
    vegetarian_desserts.erase(vegetarian_desserts.begin());
    flexitarian_desserts.erase(flexitarian_desserts.begin());

    fin3.close();
   
    std::ofstream fout;
    fout.open(".//data//menu_RO.csv");

    if(!fout.is_open())
    {
        std::cout << "Error opening menu_RO.csv in writeData()" << std::endl;
        return;
    }

    fout << "Tipul preparatului" << "," << "Meniu non-vegetarian" << "," << "Meniu vegetarian" << "," << "Meniu flexitarian\n" << "\n";

    for(int i = 0; i < 2; i++)
    {
        fout << "Supă" << "," << normal_soups[rng() % normal_soups.size()] << "," << vegetarian_soups[rng() % vegetarian_soups.size()] << "," << flexitarian_soups[rng() % flexitarian_soups.size()] << "\n";
        fout << "Main Course" << "," << normal_main_courses[rng() % normal_main_courses.size()] << "," << vegetarian_main_courses[rng() % vegetarian_main_courses.size()] << "," << flexitarian_main_courses[rng() % flexitarian_main_courses.size()] << "\n";
        fout << "Desert" << "," << normal_desserts[rng() % normal_desserts.size()] << "," << vegetarian_desserts[rng() % vegetarian_desserts.size()] << "," << flexitarian_desserts[rng() % flexitarian_desserts.size()] << "\n";
        fout << "\n";
    }

    fout.close();

}

void Menu::setMenu()
{
    writeDataEN();
    writeDataRO();
}