#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include "coordinate.h"

static int id_counter = 0;

int global_coord_id = 1;


void add_coordinate(Coordinate *list_end, float x, float y) {
    Coordinate *new_coord = new Coordinate;
    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = global_coord_id++;
    new_coord->next = nullptr;
    new_coord->previous = list_end;
    if (list_end != nullptr) {
        list_end->next = new_coord;
    }
}

void forward_display(Coordinate *list_beginning) {
    Coordinate *current = list_beginning;
    while (current != nullptr) {
        std::cout << "ID: " << current->coord_id << " x: " << current->x << " y: " << current->y << std::endl;
        current = current->next;
    }
}

void backward_display(Coordinate *list_end) {
    Coordinate *current = list_end;
    while (current != nullptr) {
        std::cout << "ID: " << current->coord_id << " x: " << current->x << " y: " << current->y << std::endl;
        current = current->previous;
    }
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete) {
    Coordinate *current = list_beginning;
    while (current != nullptr) {
        if (current->coord_id == coord_id_to_delete) {
            if (current->previous != nullptr) {
                current->previous->next = current->next;
            }
            if (current->next != nullptr) {
                current->next->previous = current->previous;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

int list_length(Coordinate *list_beginning) {
    int length = 0;
    Coordinate *current = list_beginning;
    while (current != nullptr) {
        length++;
        current = current->next;
    }
    return length;
}

void closest_to(Coordinate *list_beginning, float x, float y) {

  Coordinate *current = list_beginning;
    Coordinate *closest = nullptr;
    float min_distance = std::numeric_limits<float>::max();
    
    while (current != nullptr) {
        float distance = std::sqrt(std::pow(current->x, x - current->x) + std::pow(y - current->y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest = current;
        }
        current = current->next;
    }
    
    if (closest != nullptr) {
        std::cout << "Closest coordinate ID: " << closest->coord_id 
                  << " x: " << closest->x << " y: " << closest->y 
                  << " Distance: " << min_distance << std::endl;
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_coordinates>\n";
        return 1;
    }

    int num_coordinates = std::atoi(argv[1]);
    std::srand(static_cast<unsigned>(std::time(0)));

    Coordinate *list_start = nullptr;
    Coordinate *list_end = nullptr;

    for (int i = 0; i < num_coordinates; ++i) {
        float x = static_cast<float>(std::rand() % 100);
        float y = static_cast<float>(std::rand() % 100);

        if (list_start == nullptr) {
            list_start = new Coordinate{x, y, id_counter++, nullptr, nullptr};
            list_end = list_start;
        } else {
            add_coordinate(list_end, x, y);
            list_end = list_end->next;
        }
    }

    std::cout << "\nDisplaying list forwards:\n";
    forward_display(list_start);
    std::cout << "\nDisplaying list backwards:\n";
    backward_display(list_end);

    float x_target = static_cast<float>(std::rand() % 100);
    float y_target = static_cast<float>(std::rand() % 100);
    std::cout << "\nFinding the closest coordinate to (" << x_target << ", " << y_target << "):\n";
    closest_to(list_start, x_target, y_target);

    int coord_to_delete = std::rand() % num_coordinates + 1;
    std::cout << "\nDeleting coordinate with ID: " << coord_to_delete << "\n";
    delete_coordinate(list_start, coord_to_delete);

    std::cout << "\nList length after deletion: " << list_length(list_start) << "\n";

    std::cout << "\nDisplaying new list forwards:\n";
    forward_display(list_start);
    std::cout << "\nDisplaying new list backwards:\n";
    backward_display(list_end);

    Coordinate *current = list_start;
    while (current != nullptr) {
        Coordinate *next = current->next;
        delete current;
        current = next;
    }

    return 0;

}

