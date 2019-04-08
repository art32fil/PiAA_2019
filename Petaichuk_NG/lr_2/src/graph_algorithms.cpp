#include "graph_algorithms.h"

string findWay_Greedy(Graph &field, Vertex start, Vertex end)
{
     map<Vertex, bool> visited_vertexes;
     Vertex_List way_to_end = {start};
     string answer = "";

     for (graph_iterator it = field.begin(); it != field.end(); it++)
         visited_vertexes[it->first] = false;
     while (way_to_end[way_to_end.size() - 1] != end)
     {
         vector<Edge> possible_ways;

         visited_vertexes[way_to_end[way_to_end.size() - 1]] = true;
         for (Edge possible_way : field[way_to_end[way_to_end.size() - 1]])
             if (visited_vertexes[possible_way.where] == false)
                 possible_ways.push_back(possible_way);
         if (possible_ways.empty())
         {
             way_to_end.pop_back();
             continue;
         }
         Edge next_way = *min_element(possible_ways.begin(), possible_ways.end(),
                                         [](const Edge &first, const Edge &second)
         {
             return first.length < second.length;
         });
         way_to_end.push_back(next_way.where);
     }
     for (unsigned int i = 0; i < way_to_end.size(); i++)
         answer += way_to_end[i];
     return answer;
}

string findWay_AStar(Graph &field, Vertex start, Vertex end)
{
     map<Vertex, bool> visited_vertexes;
     map<Vertex, Vertex> way_to_end;
     map<Vertex, double> destination_from_start = {{start, 0}};
     string answer = "";

     for (graph_iterator it = field.begin(); it != field.end(); it++)
         visited_vertexes[it->first] = false;
     for (unsigned int i = 0; i < field.size(); i++)
     {
         map<Vertex, double>::iterator now_element = min_element(destination_from_start.begin(), destination_from_start.end(),
                                                                 [end](const pair<Vertex, double> &one, const pair<Vertex, double> &another)
         {
             return (one.second + (end - one.first)) < (another.second + (end - another.first));
         });
         if (now_element->first == end)
             break;
         visited_vertexes[now_element->first] = true;
         for (Edge next_way : field[now_element->first])
         {
             if (visited_vertexes[next_way.where] == false)
             {
                 map<Vertex, double>::iterator way_to_vertex = destination_from_start.find(next_way.where);
                 if ((way_to_vertex == destination_from_start.end()) || (now_element->second + next_way.length < way_to_vertex->second))
                 {
                     destination_from_start[next_way.where] = now_element->second + next_way.length;
                     way_to_end[next_way.where] = now_element->first;
                 }
             }
         }
         destination_from_start.erase(now_element);
     }
     for (Vertex now_vertex = end; answer[0] != start; now_vertex = way_to_end.find(now_vertex)->second)
         answer = now_vertex + answer;
     return answer;
}

