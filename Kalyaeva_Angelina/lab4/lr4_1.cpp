#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <int> prefix(string arr) {
	vector <int> p(arr.size());
	size_t j = 0;
	size_t i = 1;
	p[0] = 0;
	while (i < arr.length()) {
		if (arr[i] == arr[j]) {
			p[i] = j + 1;
			i++;
			j++;
		}
		else if (j == 0) {
			p[i] = 0;
			i++;
		}
		else {
			j = p[j - 1];
		}
	}
	return p;
}

vector <int> KMP(string form, string line) {
	vector <int> res;
	vector <int> p = prefix(form);
	size_t i = 0;
	size_t j = 0;
	while ( i < line.length()) {
		if (line[i] == form[j]) {
			i++;
			j++;
			if (j == form.length()) {
				res.push_back(i - form.length());
			}
		}
		else if (j != 0) {
			j = p[j - 1];
		}
		else {
			i++;
		}
	}
	return res;
}

int main() {
	string form;
	string line;
	getline(cin, form);
	getline(cin, line);
	vector <int> res = KMP(form, line);
    if(res.size()==0){
        cout<<"-1";
    }
    else{
	    for (size_t i = 0; i < res.size(); i++) {
		    cout << res[i];
		    if (i != res.size() - 1) {
		    	cout << ",";
		    }
	    }
    }
	return 0;
}