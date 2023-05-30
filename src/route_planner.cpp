#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}


// TODO 3: Implement the CalculateHValue method.
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    // *node means node is dereferenced in parameter itself
    // Use Euclidean distance implemented in RouteModel::Node
    return end_node->distance(*node);
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    for (RouteModel::Node* n : current_node->neighbors) {
        // need to dereference, neighbors is a vector of pointers
        n->parent = current_node;
        n->h_value = CalculateHValue(n); 
        n->g_value = current_node->g_value + current_node->distance(*n); 
        if (n->visited != true) {
            //open_list is also a list of pointers
            open_list.push_back(n);
            n->visited = true;
        }
    }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.

// To implement this as a nested function, it has to be created as a lambda
// As a nested function it belongs to RoutePlanner class vs just floating in the same route_planner.cpp file
bool Compare(RouteModel::Node const *a, RouteModel::Node const *b) {
    return ((a->h_value + a->g_value) > (b->h_value + b->g_value)) ? true : false; 
}

RouteModel::Node *RoutePlanner::NextNode() {
    sort(open_list.begin(), open_list.end(), Compare); 
    //Note, there's no check for if open_list is empty, could be an error point with first element access
    RouteModel::Node* first_node = open_list[0];
    open_list.erase(open_list.begin());
    return first_node;
}



// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.

    // Edge case if while loop doesn't run, path still has the start==end node
    if (current_node->parent == nullptr) path_found.push_back(*current_node);

    while (current_node != nullptr) {
        path_found.push_back(*current_node);
        distance += current_node->distance(*current_node->parent);
        current_node = current_node->parent;
    }

    reverse(path_found.begin(), path_found.end());

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
void RoutePlanner::AStarSearch() {
    // pointer to start node 
    RouteModel::Node *current_node = start_node;

    // TODO: Implement your solution here.
    AddNeighbors(current_node);
    // testing equality through memory addresses
    //if open list size fails, no path was found 
    while (&current_node != &end_node && open_list.size() > 0) {
        current_node = NextNode();
        AddNeighbors(current_node);
    }
    //so if end_node wasn't reached, will just return the last node as the path
    m_Model.path = ConstructFinalPath(end_node);
}