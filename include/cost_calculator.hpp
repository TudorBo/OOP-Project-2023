#include "data.hpp"

//template for summing two numbers
template <typename size_t>
size_t sum(size_t a, size_t b)
{
    return a + b;
}

//template for summing five numbers
template <typename size_t>
size_t total_sum(size_t a, size_t b, size_t c, size_t d, size_t e)
{
    return a + b + c + d + e;
}

//template for converting RON to USD
template <typename size_t>
size_t convToUSD(size_t a)
{
    return (a / 4.6);
}

//class for calculating the total cost of the event(transport, food, hotel, makeup, rental) and wriring it in CSV files in English and Romanian language
class Cost
{
    private:
        int transport_cost;
        std::vector <int> food_cost;
        std::vector <int> hotel_cost;
        std::vector <int> makeup_cost;
        std::vector <int> rental_cost;
        std::vector <int> total_cost;

    public:
        //all the methods writes the resuls in CSV files, except the calculateTotalCost method
        //all files are in the data/costs folder
        Cost() = default;
        void totalEN(Cast cast);
        void totalEN(std::vector <int> days);
        void hotelEN(std::vector <int> days);
        void makeupEN(std::vector <int> days);
        void rentalEN(std::vector <int> days);
        void writeDataEN(std::vector <int> days, Cast cast);
        void totalRO(Cast cast);
        void totalRO(std::vector <int> days);
        void hotelRO(std::vector <int> days);
        void makeupRO(std::vector <int> days);
        void rentalRO(std::vector <int> days);
        void writeDataRO(std::vector <int> days, Cast cast);
        void calculateTotalCost(std::vector <int> days, Cast cast);
        ~Cost() = default; 
};

//calculatates the total of transport cost for the cast and random actors
void Cost::totalEN(Cast cast)
{
    int bus_capacity = 50;
    int bus_cost = 5680;
    int num_of_buses = 0;
    std::ofstream fout;
    std::ofstream fout2;


    num_of_buses = cast.cast_size / bus_capacity;
    transport_cost = num_of_buses * bus_cost;

    if(cast.cast_size % bus_capacity != 0)
    {
        transport_cost = sum(transport_cost, bus_cost);
        num_of_buses = sum(num_of_buses, 1);
    }
    
    transport_cost = transport_cost * 2;
        
    fout.open(".//data//costs//transport_cost_EN.csv", std::ios::out);

    if(!fout.is_open())
    {
        std::cout << "Error opening transport_cost_EN.csv in totalEN(Cast cast)" << std::endl;
        return;
    }

    fout << "-------------------TRANSPORT COST-------------------" << "\n";
    fout << "Number of buses," << num_of_buses << "\n";
    fout << "Transport cost," << transport_cost << " RON," << convToUSD(transport_cost) << " USD" << "\n"; 
    fout << "NOTE: The cost of the transport is calculated only for the route from the airport to the castel and back." << "\n";

    fout.close();
}

//calculates the total of food cost for the cast
//overloaded function
void Cost::totalEN(std::vector <int> days)
{
    std::vector <std::string> cast_names;
    std::vector <std::string> cast_jobs;
    std::vector <std::string> cast_meals;
    std::string row;
    std::string aux;
    int normal_meals = 0, flexitarian_meals = 0, vegetarian_meals = 0;
    int normal_meal_cost = 40, flexitarian_meal_cost = 46, vegetarian_meal_cost = 33;
    int normal_meals_cost_total = 0, flexitarian_meals_cost_total = 0, vegetarian_meals_cost_total = 0;
    int total_meals = 0, total_meals_cost = 0;
    int total_water_cost = 0, total_coffee_cost = 0, total_juice_cost = 0;
    std::ifstream fin;
    std::ofstream fout;
    std::ofstream fout2;

    fin.open(".//data//new_Wednesday_cast.csv", std::ios::in);

    if(!fin.is_open())
    {
        std::cout << "Error opening new_Wednesday_cast.csv int totalEN(int days)" << std::endl;
        return;
    }

    while(std::getline(fin, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        cast_names.push_back(aux);

        std::getline(sin, aux, ',');
        cast_jobs.push_back(aux);

        std::getline(sin, aux, ',');
        cast_meals.push_back(aux);
    }
    
    fin.close();

    fout.open(".//data//costs//food_cost_EN.csv", std::ios::out);

    if(!fout.is_open())
    {
        std::cout << "Error opening food_cost_EN.csv in total(int days)" << std::endl;
        return;
    }
    
     try{    
        for(auto i : cast_meals)
        {
            if(i == "normal")
            {
                normal_meals = sum(normal_meals, 1);
            }
            else if(i == "flexitarian")
            {
                flexitarian_meals = sum(flexitarian_meals, 1);
            }
            else if(i == "vegetarian")
            {
                vegetarian_meals = sum(vegetarian_meals, 1);
            }
            else
            {
                throw std::invalid_argument("Invalid meal type");
            }
        }

        total_meals = sum(normal_meals, flexitarian_meals);
        total_meals = sum(total_meals, vegetarian_meals);
        
    } catch(std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }

    fout << "-------------------FOOD COST-------------------" << "\n";
    for(int i = 0; i < days.size(); i++)
    {

        normal_meals_cost_total = normal_meals * days.at(i) * normal_meal_cost;
        flexitarian_meals_cost_total = flexitarian_meals * days.at(i) * flexitarian_meal_cost;
        vegetarian_meals_cost_total = vegetarian_meals * days.at(i) * vegetarian_meal_cost;
        total_meals_cost = normal_meals_cost_total + flexitarian_meals_cost_total + vegetarian_meals_cost_total;

        total_water_cost = total_meals * 3 * days.at(i);
        total_coffee_cost = total_meals * 15 * days.at(i);
        total_juice_cost = total_meals * 0.8 * 4 * days.at(i);
        
        food_cost.push_back(total_meals_cost + total_water_cost + total_coffee_cost + total_juice_cost);
        
        fout << "For " << days.at(i) << " days\n\n";
        fout << "Total number of menus, " << total_meals << "\n";
        fout << "Normal menus," << normal_meals << "\n";
        fout << "Flexitarian menus," << flexitarian_meals << "\n";
        fout << "Vegetarian menus," << vegetarian_meals << "\n\n";
        fout << "Total menus cost," << total_meals_cost << " RON," << convToUSD(total_meals_cost) << " USD" << "\n";
        fout << "Normal menus cost," << normal_meals_cost_total << " RON," << convToUSD(normal_meals_cost_total) << " USD" << "\n";
        fout << "Flexitarian menus cost," << flexitarian_meals_cost_total << " RON," << convToUSD(flexitarian_meals_cost_total) << " USD" << "\n";
        fout << "Vegetarian menus cost," << vegetarian_meals_cost_total << " RON," << convToUSD(vegetarian_meals_cost_total) << " USD" << "\n\n";
        fout << "Water (litres)," << (total_meals * 0.5 * days.at(i)) << "\n";
        fout << "Coffee (litres)," << (total_meals * 0.5 * days.at(i)) << "\n";
        fout << "Juice (litres)," << (total_meals * 0.8 * days.at(i)) << "\n";
        fout << "Total water cost," << total_water_cost << " RON," << convToUSD(total_water_cost) << " USD" << "\n";
        fout << "Total coffee cost," << total_coffee_cost << " RON," << convToUSD(total_coffee_cost) << " USD" << "\n";
        fout << "Total juice cost," << total_juice_cost << " RON," << convToUSD(total_juice_cost) << " USD" << "\n\n";
        fout << "Menus and drinks total cost," << food_cost.at(i) << " RON," << convToUSD(food_cost.at(i)) << " USD" << "\n";
        fout << "-------------------------------------------------------------\n\n";
    }

    fout.close();
    
}

//calculates the total cost of the hotel for the cast and random actors
void Cost::hotelEN(std::vector <int> days)
{
    int cast_size = 0;
    int random_actors = 0;
    int cast_rooms = 0, random_actors_rooms = 0;
    int cast_rooms_cost = 0, random_actors_hotel_cost = 0;
    int total = 0;
    std::string row;
    std::ifstream fin1;
    std::ifstream fin2;
    std::ofstream fout;

    fin1.open(".//data//cast and random actors//wednesdayCast.csv", std::ios::in);

    if(!fin1.is_open())
    {
        std::cout << "Error opening wednesdayCast.csv in hotelEN(int days)" << std::endl;
        return;
    }

    while(std::getline(fin1, row))
    {
        cast_size++;
    }

    fin1.close();

    fin2.open(".//data//cast and random actors//random_actors.csv", std::ios::in);

    if(!fin2.is_open())
    {
        std::cout << "Error opening random_actors.csv in hotelEN(int days)" << std::endl;
        return;
    }

    while(std::getline(fin2, row))
    {
        random_actors++;
    }

    fin2.close();

    cast_rooms = cast_size / 2;

    if(cast_size % 2 != 0)
    {
        cast_rooms++;
    }

    random_actors_rooms = random_actors / 3;

    if(random_actors % 3 != 0)
    {
        random_actors_rooms++;
    }

    fout.open(".//data//costs//hotel_cost_EN.csv", std::ios::out);

    if(!fout.is_open())
        {
            std::cout << "Error opening hotel_cost_EN.csv in hotelEN(int days)" << std::endl;
            return;
        }

    fout << "-------------------HOTEL COSTS-------------------" << "\n";
    for(int i = 0; i < days.size(); i++)
    {
        cast_rooms_cost = cast_rooms * 350 * days.at(i);
        random_actors_hotel_cost = random_actors_rooms * 420 * days.at(i);

        hotel_cost.push_back(sum(cast_rooms_cost, random_actors_hotel_cost));
        
        
        fout << "For" << days.at(i) << " days\n\n";
        fout << "Cast size," << cast_size << "\n";
        fout << "Cast rooms," << cast_rooms << "\n";
        fout << "Cast rooms cost," << cast_rooms_cost << " RON," << convToUSD(cast_rooms_cost) << " USD" << "\n\n";
        fout << "Random actors," << random_actors << "\n";
        fout << "Random actors rooms," << random_actors_rooms << "\n";
        fout << "Random actors hotel cost," << random_actors_hotel_cost << " RON," << convToUSD(random_actors_hotel_cost) << " USD" << "\n\n";
        fout << "Total hotel cost," << hotel_cost.at(i) << " RON," << convToUSD(hotel_cost.at(i)) << " USD" << "\n";
        fout << "-----------------------------------------------" << "\n\n";

    }
    fout.close();
}

//calculates the total cost of the makeup for the cast and random actors
void Cost::makeupEN(std::vector <int> days)
{
    int num_of_actors = 0;
    int num_of_vampires = 0, num_of_werewolves = 0, num_of_mermaids = 0, num_of_clairvoyants = 0, num_of_humans = 0;
    int num_of_vampires_cost = 0, num_of_werewolves_cost = 0, num_of_mermaids_cost = 0, num_of_clairvoyants_cost = 0, num_of_humans_cost = 0;
    std::string row;
    std::ifstream fin;
    std::ofstream fout;

    fin.open(".//data//cast and random actors//actors_list.csv", std::ios::in);

    if(!fin.is_open())
    {
        std::cout << "Error opening actors_list.csv in makeupEN(int days)" << std::endl;
        return;
    }

    try
    {
        while(std::getline(fin, row))
        {
            num_of_actors = sum(num_of_actors, 1);

            if(row.find("Vampire") != std::string::npos)
            {
                num_of_vampires = sum(num_of_vampires, 1);
            }
            else if(row.find("Werewolf") != std::string::npos)
            {
                num_of_werewolves = sum(num_of_werewolves, 1);
            }
            else if(row.find("Mermaid") != std::string::npos)
            {
                num_of_mermaids = sum(num_of_mermaids, 1);
            }
            else if(row.find("Clairvoyant") != std::string::npos)
            {
                num_of_clairvoyants = sum(num_of_clairvoyants, 1);
            }
            else if(row.find("Human") != std::string::npos)
            {
                num_of_humans = sum(num_of_humans, 1);
            }
            else
            {
                throw std::invalid_argument("Invalid actor type");
            }
        }
    } catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    fin.close();

    fout.open(".//data//costs//makeup_cost_EN.csv", std::ios::out);

    if(!fout.is_open())
    {
        std::cout << "Error opening makeup_cost_EN.csv in makeupEN(int days)" << std::endl;
        return;
    }

    fout << "-------------------MAKEUP COSTS-------------------" << "\n";

    for(int i = 0; i < days.size(); i++)
    {
        num_of_vampires_cost = num_of_vampires * 230 * days.at(i);
        num_of_werewolves_cost = num_of_werewolves * 555 * days.at(i);
        num_of_mermaids_cost = num_of_mermaids * 345 * days.at(i);
        num_of_clairvoyants_cost = num_of_clairvoyants * 157 * days.at(i);
        num_of_humans_cost = num_of_humans * 55 * days.at(i);

        makeup_cost.push_back(num_of_vampires_cost + num_of_werewolves_cost + num_of_mermaids_cost + num_of_clairvoyants_cost +  num_of_humans_cost);

        fout << "For " << days.at(i) << " days\n\n";
        fout << "Actors," << num_of_actors << "\n\n";
        fout << "Vampires," << num_of_vampires << "\n";
        fout << "Vampires makeup cost," << num_of_vampires_cost << " RON," << convToUSD(num_of_vampires_cost) << " USD" << "\n\n";
        fout << "Werewolves," << num_of_werewolves << "\n";
        fout << "Werewolves makeup cost," << num_of_werewolves_cost << " RON," << convToUSD(num_of_werewolves_cost) << " USD" << "\n\n";
        fout << "Mermaids," << num_of_mermaids << "\n";
        fout << "Mermaids makeup cost," << num_of_mermaids_cost << " RON," << convToUSD(num_of_mermaids_cost) << " USD" << "\n\n";
        fout << "Clairvoyants," << num_of_clairvoyants << "\n";
        fout << "Clairvoyants makeup cost," << num_of_clairvoyants_cost << " RON," << convToUSD(num_of_clairvoyants_cost) << " USD" << "\n\n";
        fout << "Humans," << num_of_humans << "\n";
        fout << "Humans makeup cost," << num_of_humans_cost << " RON," << convToUSD(num_of_humans_cost) << " USD" << "\n\n";
        fout << "Makeup cost," << makeup_cost.at(i) << " RON," << convToUSD(makeup_cost.at(i)) << " USD" << "\n";
        fout << "-----------------------------------------------" << "\n\n";
    }

    fout.close();
}

//calculates the total cost of renting the Cantacuzino Castle for a certain number of days
void Cost::rentalEN(std::vector <int> days)
{   
    std::ofstream fout;

    fout.open(".//data//costs//rental_cost_EN.csv", std::ios::out);

    if(!fout.is_open())
    {
        std::cout << "Error opening total_cost_EN.csv in rentalEN(int days)" << std::endl;
        return;
    }

    fout << "-------------------RENTAL COSTS-------------------" << "\n\n";

    for(int i = 0; i < days.size(); i++)
    {

        if(days.at(i) > 10)
        {
            rental_cost.push_back((10000 * days.at(i)) - ((10000 * days.at(i)) * 0.02));
        }
        else
        {
            rental_cost.push_back(10000 * days.at(i));
        }

        fout << "For" << days.at(i) << " days\n";
        fout << "Rental cost: " << rental_cost.at(i) << " RON," << convToUSD(rental_cost.at(i)) << " USD" << "\n";
    }
    
    fout.close();
}

//calculates the total cost of the production
void Cost::writeDataEN(std::vector <int> days, Cast cast)
{
    std::ofstream fout;
    
    fout.open(".//data//total_cost_EN.csv", std::ios::out);
    
    if(!fout.is_open())
    {
        std::cout << "Error opening total_cost_EN.csv in writeDataEN(std::vector <int> days, Cast cast)" << std::endl;
        return;
    }

    fout << "--------------------TOTAL COST--------------------" << "\n";

    totalEN(cast);
    hotelEN(days);
    totalEN(days);
    makeupEN(days);
    rentalEN(days);

    for(int i = 0; i < days.size(); i++)
    {
        fout << "For " << days.at(i) << " days: " << "\n";
        fout << "Transport," << transport_cost << " RON," << convToUSD(transport_cost) << " USD" << "\n";
        fout << "Hotel cost," << hotel_cost.at(i) << " RON," << convToUSD(hotel_cost.at(i)) << " USD" << "\n";
        fout << "Makeup," << makeup_cost.at(i) << " RON," << convToUSD(makeup_cost.at(i)) << " USD" << "\n";
        fout << "Food cost," << food_cost.at(i) << " RON," << convToUSD(food_cost.at(i)) << " USD" << "\n";
        fout << "Rental cost," << rental_cost.at(i) << " RON," << convToUSD(rental_cost.at(i)) << " USD" << "\n\n";

        total_cost.push_back(total_sum(transport_cost, hotel_cost.at(i), makeup_cost.at(i), food_cost.at(i), rental_cost.at(i)));

        fout << "Total cost," << total_cost.at(i) << " RON," << convToUSD(total_cost.at(i)) << " USD" << "\n\n";
        fout << "-----------------------------------------------" << "\n\n";
        
    }

    fout.close();
}

//this methods are like the ones above, but writes the results in Romanian language
void Cost::totalRO(Cast cast)
{
    int bus_capacity = 50;
    int bus_cost = 5680;
    int num_of_buses = 0;
    std::ofstream fout;

    num_of_buses = cast.cast_size / bus_capacity;
    transport_cost = num_of_buses * bus_cost;

    if(cast.cast_size % bus_capacity != 0)
    {
        transport_cost = sum(transport_cost, bus_cost);
        num_of_buses = sum(num_of_buses, 1);
    }
    
    transport_cost = transport_cost * 2;
        
    fout.open(".//data//costs//transport_cost_RO.csv", std::ios::out);

    if(!fout.is_open())
    {
        std::cout << "Error opening transport_cost_RO.csv in totalRO(Cast cast)" << std::endl;
        return;
    }

    fout << "-------------------COSTUL TRANSPORTULUI-------------------" << "\n";
    fout << "Numarul de autobuze," << num_of_buses << "\n";
    fout << "Costul transportului," << transport_cost << " RON," << convToUSD(transport_cost) << " USD" << "\n";
    fout << "NOTA: Costul transportului este calculat doar pentru ruta de la aeroport la castel si inapoi." << "\n";

    fout.close();
}

void Cost::totalRO(std::vector <int> days)
{
    std::vector <std::string> cast_names;
    std::vector <std::string> cast_jobs;
    std::vector <std::string> cast_meals;
    std::string row;
    std::string aux;
    int normal_meals = 0, flexitarian_meals = 0, vegetarian_meals = 0;
    int normal_meal_cost = 40, flexitarian_meal_cost = 46, vegetarian_meal_cost = 33;
    int normal_meals_cost_total = 0, flexitarian_meals_cost_total = 0, vegetarian_meals_cost_total = 0;
    int total_meals = 0, total_meals_cost = 0;
    int total_water_cost = 0, total_coffee_cost = 0, total_juice_cost = 0;
    std::ifstream fin;
    std::ofstream fout;

    fin.open(".//data//new_Wednesday_cast.csv", std::ios::in);

    if(!fin.is_open())
    {
        std::cout << "Error opening new_Wednesday_cast.csv int totalRO(int days)" << std::endl;
        return;
    }

    while(std::getline(fin, row))
    {
        std::istringstream sin(row);

        std::getline(sin, aux, ',');
        cast_names.push_back(aux);

        std::getline(sin, aux, ',');
        cast_jobs.push_back(aux);

        std::getline(sin, aux, ',');
        cast_meals.push_back(aux);
    }
    
    fin.close();

    fout.open(".//data//costs//food_cost_RO.csv", std::ios::out);

    if(!fout.is_open())
    {
        std::cout << "Error opening food_cost_RO.csv in totalRO(int days)" << std::endl;
        return;
    }
    
     try{    
        for(auto i : cast_meals)
        {
            if(i == "normal")
            {
                normal_meals = sum(normal_meals, 1);
            }
            else if(i == "flexitarian")
            {
                flexitarian_meals = sum(flexitarian_meals, 1);
            }
            else if(i == "vegetarian")
            {
                vegetarian_meals = sum(vegetarian_meals, 1);
            }
            else
            {
                throw std::invalid_argument("Invalid meal type");
            }
        }

        total_meals = sum(normal_meals, flexitarian_meals);
        total_meals = sum(total_meals, vegetarian_meals);
        
    } catch(std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
    }

    fout << "-------------------COSTUL MANCARII SI A BAUTURILOR-------------------" << "\n";
    for(int i = 0; i < days.size(); i++)
    {

        normal_meals_cost_total = normal_meals * days.at(i) * normal_meal_cost;
        flexitarian_meals_cost_total = flexitarian_meals * days.at(i) * flexitarian_meal_cost;
        vegetarian_meals_cost_total = vegetarian_meals * days.at(i) * vegetarian_meal_cost;
        total_meals_cost = normal_meals_cost_total + flexitarian_meals_cost_total + vegetarian_meals_cost_total;

        total_water_cost = total_meals * 0.5 * 3 * days.at(i);
        total_coffee_cost = total_meals * 0.5 * 15 * days.at(i);
        total_juice_cost = total_meals * 0.8 * 4 * days.at(i);
        
        food_cost.push_back(total_meals_cost + total_water_cost + total_coffee_cost + total_juice_cost);
        
        fout << "Pentru " << days.at(i) << " de zile\n\n";
        fout << "Numarul total al meniurilor," << total_meals << "\n";
        fout << "Meniuri normale," << normal_meals << "\n";
        fout << "Meniuri flexitariene," << flexitarian_meals << "\n";
        fout << "Meniuri vegetariene," << vegetarian_meals << "\n\n";
        fout << "Costul total al meniurilor," << total_meals_cost << " RON," << convToUSD(total_meals_cost) << " USD" << "\n";
        fout << "Costul total al meniuilor normale," << normal_meals_cost_total << " RON," << convToUSD(normal_meals_cost_total) << " USD" << "\n";
        fout << "Costul total al meniurilor flexitariene," << flexitarian_meals_cost_total << " RON," << convToUSD(flexitarian_meals_cost_total) << " USD" << "\n";
        fout << "Costul total al meniurilor vegetariene," << vegetarian_meals_cost_total << " RON," << convToUSD(vegetarian_meals_cost_total) << " USD" << "\n\n";
        fout << "Apa (litri)," << (total_meals * 0.5 * days.at(i)) << "\n";
        fout << "Cafea (litri)," << (total_meals * 0.5 * days.at(i)) << "\n";
        fout << "Suc (litri)," << (total_meals * 0.8 * days.at(i)) << "\n\n";
        fout << "Costul total al apei," << total_water_cost << " RON," << convToUSD(total_water_cost) << " USD" << "\n";
        fout << "Costul total al cafelei," << total_coffee_cost << " RON," << convToUSD(total_coffee_cost) << " USD" << "\n";
        fout << "Costul total al sucului," << total_juice_cost << " RON," << convToUSD(total_juice_cost) << " USD" << "\n";
        fout << "Costul total al mancarii si al bauturilor," << food_cost.at(i) << " RON," << convToUSD(food_cost.at(i)) << " USD" << "\n\n";
        fout << "-------------------------------------------------------------\n\n";
    }

    fout.close();
    
}

void Cost::hotelRO(std::vector <int> days)
{
    int cast_size = 0;
    int random_actors = 0;
    int cast_rooms = 0, random_actors_rooms = 0;
    int cast_rooms_cost = 0, random_actors_hotel_cost = 0;
    int total = 0;
    std::string row;
    std::ifstream fin1;
    std::ifstream fin2;
    std::ofstream fout;

    fin1.open(".//data//cast and random actors//wednesdayCast.csv", std::ios::in);

    if(!fin1.is_open())
    {
        std::cout << "Error opening wednesdayCast.csv in hotelRO(int days)" << std::endl;
        return;
    }

    while(std::getline(fin1, row))
    {
        cast_size++;
    }

    fin1.close();

    fin2.open(".//data//cast and random actors//random_actors.csv", std::ios::in);

    if(!fin2.is_open())
    {
        std::cout << "Error opening random_actors.csv in hotelRO(int days)" << std::endl;
        return;
    }

    while(std::getline(fin2, row))
    {
        random_actors++;
    }

    fin2.close();

    cast_rooms = cast_size / 2;

    if(cast_size % 2 != 0)
    {
        cast_rooms++;
    }

    random_actors_rooms = random_actors / 3;

    if(random_actors % 3 != 0)
    {
        random_actors_rooms++;
    }

    fout.open(".//data//costs//hotel_cost_RO.csv", std::ios::out);

    if(!fout.is_open())
        {
            std::cout << "Error opening hotel_cost_RO.csv in hotelRO(int days)" << std::endl;
            return;
        }

    fout << "-------------------HOTEL COSTS-------------------" << "\n";
    for(int i = 0; i < days.size(); i++)
    {
        cast_rooms_cost = cast_rooms * 350 * days.at(i);
        random_actors_hotel_cost = random_actors_rooms * 420 * days.at(i);

        hotel_cost.push_back(sum(cast_rooms_cost, random_actors_hotel_cost));

        fout << "Pentru " << days.at(i) << " de zile\n\n";
        fout << "Numarul de persoane din distributia serialului," << cast_size << "\n";
        fout << "Numarul de camere pentru distributia serialului," << cast_rooms << "\n";
        fout << "Costul camerelor pentru distributia serialului," << cast_rooms_cost << " RON," << convToUSD(cast_rooms_cost) << " USD" << "\n\n";
        fout << "Numarul de figuranti," << random_actors << "\n";
        fout << "Numarul de camere pentru figuranti," << random_actors_rooms << "\n";
        fout << "Costul camerelor pentru figuranti," << random_actors_hotel_cost << " RON," << convToUSD(random_actors_hotel_cost) << " USD" << "\n\n";
        fout << "Costul total pentru cazare," << hotel_cost.at(i) << " RON," << convToUSD(hotel_cost.at(i)) << " USD" << "\n";
        fout << "-----------------------------------------------" << "\n\n";
    }

    fout.close();
}

void Cost::makeupRO(std::vector <int> days)
{
    int num_of_actors = 0;
    int num_of_vampires = 0, num_of_werewolves = 0, num_of_mermaids = 0, num_of_clairvoyants = 0, num_of_humans = 0;
    int num_of_vampires_cost = 0, num_of_werewolves_cost = 0, num_of_mermaids_cost = 0, num_of_clairvoyants_cost = 0, num_of_humans_cost = 0;
    std::string row;
    std::ifstream fin;
    std::ofstream fout;

    fin.open(".//data//cast and random actors//actors_list.csv", std::ios::in);

    if(!fin.is_open())
    {
        std::cout << "Error opening actors_list.csv in makeupRO(int days)" << std::endl;
        return;
    }

    try
    {
        while(std::getline(fin, row))
        {
            num_of_actors = sum(num_of_actors, 1);

            if(row.find("Vampire") != std::string::npos)
            {
                num_of_vampires = sum(num_of_vampires, 1);
            }
            else if(row.find("Werewolf") != std::string::npos)
            {
                num_of_werewolves = sum(num_of_werewolves, 1);
            }
            else if(row.find("Mermaid") != std::string::npos)
            {
                num_of_mermaids = sum(num_of_mermaids, 1);
            }
            else if(row.find("Clairvoyant") != std::string::npos)
            {
                num_of_clairvoyants = sum(num_of_clairvoyants, 1);
            }
            else if(row.find("Human") != std::string::npos)
            {
                num_of_humans = sum(num_of_humans, 1);
            }
            else
            {
                throw std::invalid_argument("Invalid actor type");
            }
        }
    } catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    fin.close();

    fout.open(".//data//costs//makeup_cost_RO.csv", std::ios::out);

    if(!fout.is_open())
    {
        std::cout << "Error opening makeup_cost_EN.csv in makeupRO(int days)" << std::endl;
        return;
    }

    fout << "-------------------COSTUL MACHIAJULUI-------------------" << "\n";

    for(int i = 0; i < days.size(); i++)
    {
        num_of_vampires_cost = num_of_vampires * 230 * days.at(i);
        num_of_werewolves_cost = num_of_werewolves * 555 * days.at(i);
        num_of_mermaids_cost = num_of_mermaids * 345 * days.at(i);
        num_of_clairvoyants_cost = num_of_clairvoyants * 157 * days.at(i);
        num_of_humans_cost = num_of_humans * 55 * days.at(i);

        makeup_cost.push_back(num_of_vampires_cost + num_of_werewolves_cost + num_of_mermaids_cost + num_of_clairvoyants_cost +  num_of_humans_cost);

        fout << "Pentru " << days.at(i) << " de zile" << "\n\n";
        fout << "Numar de actori," << num_of_actors << "\n\n";
        fout << "Vampiri," << num_of_vampires << "\n";
        fout << "Costul machiajului pentru vampiri," << num_of_vampires_cost << " RON," << convToUSD(num_of_vampires_cost) << " USD" << "\n\n";
        fout << "Varcolaci," << num_of_werewolves << "\n";
        fout << "Costul machiajului pentru varcolaci," << num_of_werewolves_cost << " RON," << convToUSD(num_of_werewolves_cost) << " USD" << "\n\n";
        fout << "Sirene," << num_of_mermaids << "\n";
        fout << "Costul machiajului pentru sirene," << num_of_mermaids_cost << " RON," << convToUSD(num_of_mermaids_cost) << " USD" << "\n\n";
        fout << "Clarvazatori," << num_of_clairvoyants << "\n";
        fout << "Costul machiajului pentru clarvazatori," << num_of_clairvoyants_cost << " RON," << convToUSD(num_of_clairvoyants_cost) << " USD" << "\n\n";
        fout << "Oameni," << num_of_humans << "\n";
        fout << "Costul machiajului pentru oameni," << num_of_humans_cost << " RON," << convToUSD(num_of_humans_cost) << " USD" << "\n\n";
        fout << "Costul total al machiajului," << makeup_cost.at(i) << " RON," << convToUSD(makeup_cost.at(i)) << " USD" << "\n";
        fout << "-----------------------------------------------" << "\n\n";
    }

    fout.close();
}

void Cost::rentalRO(std::vector <int> days)
{   
    std::ofstream fout;

    fout.open(".//data//costs//rental_cost_RO.csv", std::ios::out);

    if(!fout.is_open())
    {
        std::cout << "Error opening total_cost_RO.csv in rentalRO(int days)" << std::endl;
        return;
    }

    fout << "-------------------COSTUL INCHIRIERII-------------------" << "\n\n";

    for(int i = 0; i < days.size(); i++)
    {

        if(days.at(i) > 10)
        {
            rental_cost.push_back((10000 * days.at(i)) - ((10000 * days.at(i)) * 0.02));
        }
        else
        {
            rental_cost.push_back(10000 * days.at(i));
        }

        fout << "Pentru " << days.at(i) << " de zile\n";
        fout << "Costul inchirierii: " << rental_cost.at(i) << " RON, " << convToUSD(rental_cost.at(i)) << " USD" << "\n";
    }
    
    fout.close();
}

void Cost::writeDataRO(std::vector <int> days, Cast cast)
{
    std::ofstream fout;
    
    fout.open(".//data//total_cost_RO.csv", std::ios::out);
    
    if(!fout.is_open())
    {
        std::cout << "Error opening total_cost_EN.csv in writeDataRO(std::vector <int> days, Cast cast)" << std::endl;
        return;
    }

    fout << "--------------------TOTAL COST--------------------" << "\n";

    totalRO(cast);
    hotelRO(days);
    totalRO(days);
    makeupRO(days);
    rentalRO(days);

    for(int i = 0; i < days.size(); i++)
    {
        fout << "Pentru " << days.at(i) << " de zile: " << "\n";
        fout << "Transport," << transport_cost << " RON," << convToUSD(transport_cost) << " USD" << "\n";
        fout << "Cazare hotel," << hotel_cost.at(i) << " RON," << convToUSD(hotel_cost.at(i)) << " USD" << "\n";
        fout << "Machiaj actori si figuranti," << makeup_cost.at(i) << " RON," << convToUSD(food_cost.at(i)) << " USD" << "\n";
        fout << "Costul meniurilor si bauturilor," << food_cost.at(i) << " RON," << convToUSD(food_cost.at(i)) << " USD" << "\n";
        fout << "Costul inchirierii," << rental_cost.at(i) << " RON," << convToUSD(rental_cost.at(i)) << " USD" << "\n\n";

        total_cost.push_back(total_sum(transport_cost, hotel_cost.at(i), makeup_cost.at(i), food_cost.at(i), rental_cost.at(i)));

        fout << "Costul total," << total_cost.at(i) << " RON," << convToUSD(total_cost.at(i)) << " USD" << "\n\n";
        fout << "-----------------------------------------------" << "\n\n";
        
    }

    fout.close();
}

//calls the methods that calculate the total cost for production
void Cost::calculateTotalCost(std::vector <int> days, Cast cast)
{
    writeDataEN(days, cast);
    writeDataRO(days, cast);
}