#include <iostream>
#include <vector>

using namespace std;

class Path {
public:
	char start, end;
	bool visit;
	double weight;

	Path() {};

	Path(char s, char e, double w) :start(s), end(e), weight(w) {
		this->start = s;
		this->end = e;
		this->weight = w;
	}
};
vector<Path*> path;
vector<Path*> listPath;
vector<char> res;

void greedy(char start_way, char end_way, char current) {
	if (end_way == current)
		return;

	vector<Path*> temp;
	for (int i = 0; i < path.size(); i++) {
		if (path[i]->start == current) {
			temp.push_back(path[i]);
		}
	}

	if (temp.size() != 0) {
		double min = 10000.0, id = 0;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i]->weight < min) {
				min = temp[i]->weight;
				id = i;
			}
		}
		for (int i = (temp.size() - 1); i > 0; i--) {
			listPath.push_back(temp[i]);
		}
		res.push_back(temp[id]->end);
		greedy(start_way, end_way, temp[id]->end);
	}
	else {
		char next = listPath[listPath.size() - 1]->end;
		listPath.pop_back();
		res.pop_back();
		res.push_back(next);
		greedy(start_way, end_way, next);
	}
}

int main()
{
	char start_way, end_way;
	cin >> start_way >> end_way;

	res.push_back(start_way);

	while (true) {
		char s, e;
		double w;
		if ((cin >> s) && (cin >> e) && (cin >> w)) {
			Path *p = new Path(s, e, w);
			path.push_back(p);
		}
		else
			break;
	}
	greedy(start_way, end_way, start_way);

	for (int i = 0; i < res.size(); i++)
		cout << res[i];
	cout << endl;

	system("pause");
	return 0;
}
