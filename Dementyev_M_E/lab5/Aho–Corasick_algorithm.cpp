#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define POWER 26

using namespace std;


struct Entry {
    int position;
    int pattern;
};

struct Node {
    char value;
    int parent;
    bool isLeaf;
    
    int nextNode[POWER]; //указатель на вершину, в которую ведет ребро, если не ведет -1
    int transition[POWER]; // массив переходов
    
    int suffixLink; // суффиксная ссылка
    int suffixLinkLeafOnly; // сжатая суффиксная ссылка
    
    int patternLength; // длина шаблона
    vector<int> patternNumber; // номер шаблона
    
    Node(char _value);
};

struct Bohr {
public:
    void push(const string &pattern, int patternIndex);
    
    vector<Entry> findEntries(string text);
    
    Bohr();
    
private:
    
    vector<Node> nodes;
    
    int getTransition(int index, char chr);
    
    int getSuffixLink(int index);
    
    int getSuffixLinkLeafOnly(int index);
    
};

int main() {
    Bohr bohr;
    
    string text;
    cin >> text;
    int num_pat;
    cin >> num_pat;
    
    for (int i = 0; i < num_pat; i++) {
        string pattern;
        cin >> pattern;
        bohr.push(pattern, i + 1);
    }
    
    vector<Entry> entries = bohr.findEntries(text);
    
    for (auto &i : entries) cout << i.position << " " << i.pattern << endl;
}

Node::Node(char _value) {
    for (int i = 0; i < POWER; i++) {
        nextNode[i] = -1;
        transition[i] = -1;
    }
    isLeaf = false;
    value = _value;
}

int Bohr::getSuffixLinkLeafOnly(int index) {
    Node &vertex = nodes[index];
    if (vertex.suffixLinkLeafOnly == 0) {
        int suffix_link = getSuffixLink(index);
        if (nodes[suffix_link].isLeaf) {
            vertex.suffixLinkLeafOnly = suffix_link;
        } else {
            if (suffix_link != 0)
                vertex.suffixLinkLeafOnly = getSuffixLinkLeafOnly(suffix_link);
            else vertex.suffixLinkLeafOnly = 0;
        }
    }
    return vertex.suffixLinkLeafOnly;
}

int Bohr::getSuffixLink(int index) {
    Node &vertex = nodes[index];
    if (vertex.suffixLink == 0) {
        if (vertex.parent == 0 || index == 0) vertex.suffixLink = 0;
        else {
            int suffix_link = getSuffixLink(vertex.parent); // Рекурсия
            vertex.suffixLink = getTransition(suffix_link, vertex.value);
        }
    }
    return vertex.suffixLink;
}


/**
 * Переход присутствует                                     -> Берем переход.
 * Переход отсутствует + Следующая присутствует             -> Следующая
 * Переход отсутствует + Следующая отсутствует + Корень     -> 0
 * Переход отсутствует + Следующая отсутствует + НЕ Корень  -> Рекурсия по суффиксной ссылке
 */
int Bohr::getTransition(int index, char chr) { //вычисление перехода
    int char_number = chr - 'A';
    Node &vertex = nodes[index];
    if (vertex.transition[char_number] != -1)
        return vertex.transition[char_number];
    if (vertex.nextNode[char_number] != -1)
        return vertex.transition[char_number] = vertex.nextNode[char_number];
    if (index != 0)
        return vertex.transition[char_number] = getTransition(getSuffixLink(index), chr);
    return vertex.transition[char_number] = 0;
}

Bohr::Bohr() {
    Node root('#');
    {// Инициализация
        root.isLeaf = false;
        root.suffixLink = -1;
        root.suffixLinkLeafOnly = -1;
        root.parent = 0;
    }
    nodes.push_back(root);
}

/**
 * Для каждой буквы нашего текста (text[i])
 *   Находим в боре вершину, соответствующую нашей букве и являющуюся прямым наследником корнем дерева.
 *   До тех пор, пока не попадем в корень:
 *     Если вершина - лист, собираем все ее паттерны как удачный результат.
 *     Переходим к следущей вершине по лист-суффиксной ссылке;
 **/
vector<Entry> Bohr::findEntries(string text) {
    vector<Entry> entries;
    int index = 0;
    for (int i = 0; i < text.length(); i++) {
        index = getTransition(index, text[i]);
        for (int j = index; j > 0; j = getSuffixLinkLeafOnly(j)) { // Пока не пришли в корень
            if (nodes[j].isLeaf) {
                for (size_t r = 0; r < nodes[j].patternNumber.size(); r++) {
                    Entry answer;
                    answer.position = i - nodes[j].patternLength + 2;
                    answer.pattern = nodes[j].patternNumber[r];
                    entries.push_back(answer);
                }
            }
        }
    }
    sort(entries.begin(), entries.end(), [](const Entry &a, const Entry &b) {
        return a.position != b.position ?
        a.position < b.position :
        a.pattern < b.pattern;
    });
    return entries;
}

void Bohr::push(const string &pattern, int patternIndex) {
    int index = 0;
    for (char letter : pattern) {
        int char_number = letter - 'A';
        if (nodes[index].nextNode[char_number] == -1) {
            Node symb(letter);
            symb.suffixLink = 0;
            symb.suffixLinkLeafOnly = 0;
            symb.parent = index;
            
            nodes.push_back(symb);
            nodes[index].nextNode[char_number] = nodes.size() - 1;
        }
        index = nodes[index].nextNode[char_number];
    }
    nodes[index].isLeaf = true;
    nodes[index].patternLength = pattern.length();
    nodes[index].patternNumber.push_back(patternIndex);
}



