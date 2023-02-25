#include ".//include//cost_calculator.hpp"

int main()
{
    std::vector <int> days = {30, 45, 60, 100};

    RandomActors random_actors;
    random_actors.generateData();
    
    Cast cast;
    cast.readData();
    cast.writeData();
    
    Actors actors;
    actors.readData();

    Menu menu;
    menu.setMenu();

    Cost cost;
    cost.calculateTotalCost(days, cast);  
    
    std::cout << "All data has been written to the files. Press any key to close the program." << "\n";
    std::cin.get();
    
    return 0;
}