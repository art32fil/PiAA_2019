#include <iostream>

#include <algorithm>
#include <fstream> 
#include <cstring>
#include <math.h>

using namespace std;

struct edge
{
	char begin;
	char end;
	float weight;
};

struct alter_way
{
	vector <char> vertex;
	float weight;
	float weightH;
};

struct minimal
{
	int m;
	vector <char> x;
};

int main()
{
	char start, finish;
	
	cin >> start >> finish;

	vector <edge> graph;
	edge temp;

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

	vector <alter_way> alt_way;
	alter_way tempel;
	int flag_ = 0;

	minimal min;

	while(start != finish)
	{
		cout << start << endl;
		min.m = 200.0;
		int flag = 0;

		for(int i = 0; i<graph.size(); i++)
			if(start == graph[i].begin)
			{
				if(flag_ == 0)
				{	
					tempel.vertex.push_back(start);					
					tempel.vertex.push_back(graph[i].end);
					tempel.weight = graph[i].weight;
					tempel.weightH = graph[i].weight + fabs((int)finish - (int)graph[i].end);
					alt_way.push_back(tempel); 
					tempel.vertex.clear();
				}

				else 
				{
					for(int j = 0; j<alt_way.size(); j++)
						if(alt_way[j].vertex[alt_way[j].vertex.size()-1] == start)
						{
							tempel = alt_way[j];
							alt_way.erase(alt_way.begin() + j);
						}
					alt_way.push_back(tempel);		
					alt_way[alt_way.size()-1].vertex.push_back(graph[i].end);
					alt_way[alt_way.size()-1].weight += graph[i].weight;
					alt_way[alt_way.size()-1].weightH = alt_way[alt_way.size()-1].weight + fabs((int)finish - (int)graph[i].end);
								
					for(int j = 0; j<alt_way[alt_way.size()-1].vertex.size()-1; j++) 
 						if(alt_way[alt_way.size()-1].vertex[j] == graph[i].end)
							alt_way[alt_way.size()-1].vertex.erase(alt_way[alt_way.size()-1].vertex.begin() + j); 
				}
				flag = 1;
			}

		flag_ = 1;
		int num;

		for(int i = 0; i<alt_way.size(); i++)
		{
			if(min.m > alt_way[i].weightH)
			{
cout << min.m << endl;
				min.m = alt_way[i].weightH;
				min.x = alt_way[i].vertex;
				num = i;
			}
		
			if(min.m == alt_way[i].weightH)
				if(fabs((int)finish - (int)min.x[min.x.size()-1]) > fabs((int)finish - (int)alt_way[i].vertex[alt_way[i].vertex.size()-1]))
				{
					min.x = alt_way[i].vertex;
					num = i;
				}	
		}

		if(flag == 0)
		{
			for(int i = 0; i<graph.size(); i++)
				if(graph[i].begin == alt_way[num].vertex[alt_way[num].vertex.size()-2] && graph[i].end == alt_way[num].vertex[alt_way[num].vertex.size()-1])
				{
					graph.erase(graph.begin() + i);
					break;
				}

			start = alt_way[num].vertex[alt_way[num].vertex.size()-2];
			alt_way.erase(alt_way.begin() + num);
			continue;
		}

		start = min.x[min.x.size()-1];
	}

	for(int i = 0; i<min.x.size(); i++) 
 		cout << min.x[i];

	cout << endl;

	return 0;
}

