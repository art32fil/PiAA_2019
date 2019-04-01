#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream> 
#include <cstring>

using namespace std;

struct vertex
{
	char begin;
	char end;
	float weight;
};

int main()
{
	char start, finish;
	
	cin >> start >> finish;

	vector <vertex> graph;
	vertex temp;

 	ifstream file("/home/admin1/piaa/2/in.txt");
	string str;
    	char* c;

    	while(getline(file, str))
    	{      
        	c = strdup(str.c_str());
        	char* p = NULL;

		p = strtok(c, " ");
		temp.begin = p[0];
		
		p = strtok(NULL, " ");
		temp.end = p[0];
		
		p = strtok(NULL, " ");
		temp.weight = atof(p);

		graph.push_back(temp);
    	}
    	file.close();

	vector <char> result;
	result.push_back(start);
	char tmp;

	while(start != finish)
	{
		float min = 20.0;
		int flag = 0;

		for(int i = 0; i<graph.size(); i++)
			if(start == graph[i].begin)
				if(min > graph[i].weight)
				{
					min = graph[i].weight;
					tmp = graph[i].end;
					flag = 1;
				}
	
		if(flag == 0)
		{
			for(int i = 0; i<graph.size(); i++)
				if(graph[i].begin == result[result.size()-2] && graph[i].end == start)
				{
					graph.erase(graph.begin() + i);
					break;
				}

			start = result[result.size()-2];
			result.erase(result.begin() + result.size()-1);
			continue;
		}

		start = tmp;
		result.push_back(start);
	}

	for(int i = 0; i<result.size(); i++) 
 		cout << result[i];

	cout << endl;
	
	return 0;
}

