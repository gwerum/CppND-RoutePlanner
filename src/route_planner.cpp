#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage (normalization to map size 1x1)
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) const {
    return node->distance(*end_node);
}

float RoutePlanner::CalculateGValue(RouteModel::Node const *node, RouteModel::Node const *parent_node) const {
    return parent_node->g_value + parent_node->distance(*node);
}

// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    // Create current_node's neighbors list
    current_node->FindNeighbors();
    for (RouteModel::Node *neighbor_node : current_node->neighbors) {
        float h_neighbor = CalculateHValue(neighbor_node);
        float g_neighbor = CalculateGValue(neighbor_node, current_node);
        // Update all unvisited neighbors and add them to open list
        if (!(neighbor_node->visited)) {
            neighbor_node->parent = current_node;
            neighbor_node->h_value = h_neighbor;
            neighbor_node->g_value = g_neighbor;
            neighbor_node->visited = true;
            open_list.emplace_back(neighbor_node);
        // Update visited neighbors if total cost is cheaper
        } else if ((h_neighbor + g_neighbor) < (neighbor_node->cost())) {
            neighbor_node->parent = current_node;
            neighbor_node->h_value = h_neighbor;
            neighbor_node->g_value = g_neighbor;
        }
    }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {
    RouteModel::Node *cheapest_node;
    std::sort(open_list.begin(), open_list.end(), RouteModel::Node::CompareNodes());
    cheapest_node = open_list.back();
    open_list.pop_back();
    return cheapest_node;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *final_node) {
    // Create final_path vector
    distance = 0.0f;
    std::vector<RouteModel::Node> final_path;
    RouteModel::Node *current_node = final_node;

    // TODO: Implement your solution here.
    while (current_node != start_node) {
        distance += current_node->distance(*current_node->parent);
        final_path.emplace_back(*current_node);
        current_node = current_node->parent;
    }
    final_path.emplace_back(*current_node);
    std::reverse(final_path.begin(), final_path.end());

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.

    return final_path;
}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
    start_node->visited = true; // Set start node as visited
    AddNeighbors(start_node);   // Initialize open_list with neighbors of start node
    // While still unvisited nodes and end node not found, keep searching
    while (open_list.size() > 0)
    {
        current_node = NextNode();
        if (current_node == end_node) {
            m_Model.path = ConstructFinalPath(current_node);
        } else {
            AddNeighbors(current_node);
        }
    }
}