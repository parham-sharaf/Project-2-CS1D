#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/array.hpp>
#include <array>
#include <utility>
#include <iostream>
#include <stack>

struct Distance {
    double distance;
    bool discovery = false;
};

struct City {
    std::string team;
    bool isVisited = false;
};

typedef boost::adjacency_list<boost::listS, boost::vecS,
        boost::undirectedS, City,
        Distance > Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef typename boost::graph_traits<Graph>::out_edge_iterator Iter;

class manage_teams {
public:
    enum Teams {Atlanta_Hawks, Boston_Celtics, Brooklyn_Nets, Charlotte_Hornets,
        Chicago_Bulls, Cleveland_Cavaliers, Dallas_Mavericks, Denver_Nuggets,
        Detroit_Pistons, Golden_State_Warriors, Houston_Rockets, Indiana_Pacers,
        Los_Angeles_Clippers, Los_Angeles_Lakers, Memphis_Grizzlies, Miami_Heat,
        Milwaukee_Bucks, Minnesota_Timberwolves, New_Orleans_Pelicans, New_York_Knicks,
        Oklahoma_City_Thunder, Orlando_Magic, Philadelphia_76ers, Phoenix_Suns,
        Portland_Trail_Blazers, Sacramento_Kings, San_Antonio_Spurs, Toronto_Raptors,
        Utah_Jazz, Washington_Wizards, endofTeams};


    void initialize();
    void shortest_path(int initial, int target);
    void minimum_spanning_tree();
    int depth_first_search(Teams team);
    int breadth_first_search(Teams team);

private:
    Graph g;
    std::array<double, 57> weights =
            {{
                 244.8, 383.8, 469.1, 438.8,
                 215.3, 550,
                 5.1, 97.4,
                 585.1, 730.9, 402,
                 282.6, 181.6, 92.1,
                 164.9, 315.5, 431.2, 371,
                 239.8, 206.7, 273.8,
                 1016.1, 913.9, 679.6, 862.4, 519.1,
                 694.7, 616.1, 231,
                 385.1, 87.9,
                 347.7, 197.4,
                 0.0, 1016.1, 385.1, 373, 388.4, 688.4,
                 373, 388.4, 688.4,
                 395, 466,
                 730.9, 866.1, 235.6,
                 337.1,
                 1729.3,
                 491.1,
                 679.6,
                 140,
                 579.7, 765.5,
                 491.1,
                 371,
                 -1}};

    std::array<std::string,30> teamNames
            {"Atlanta Hawks", "Boston Celtics", "Brooklyn Nets", "Charlotte_Hornets",
             "Chicago Bulls", "Cleveland Cavaliers", "Dallas Mavericks", "Denver Nuggets",
             "Detroit Pistons", "Golden State Warriors", "Houston Rockets", "Indiana Pacers",
             "Los Angeles Clippers", "Los Angeles Lakers", "Memphis Grizzlies", "Miami Heat",
             "Milwaukee Bucks", "Minnesota Timberwolves", "New Orleans Pelicans", "New York Knicks",
             "Oklahoma City Thunder", "Orlando Magic", "Philadelphia 76ers", "Phoenix Suns",
             "Portland Trail Blazers", "Sacramento Kings", "San Antonio Spurs", "Toronto Raptors",
             "Utah Jazz", "Washington Wizards"};

};