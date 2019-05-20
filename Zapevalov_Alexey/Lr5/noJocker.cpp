    #include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

typedef struct Node
{
    Node(Node* cur, char c) : parent(cur), toParent(c)
    {
        suffLink = NULL;
        dictSuffLink = NULL;
        end = false;
    }
    vector <Node*> children;
    vector <Node*> go;
    Node* parent;
    Node* suffLink;
    Node* dictSuffLink;
    char toParent;
    bool end;
    vector<int> endStringNumber;
}Node;

typedef struct result
{
    result(int p, int n) : pos(p), numb(n){}
    int pos;
    int numb;
}result;

int operator > (result first, result second)
{
    if (first.pos == second.pos)
        return first.numb > second.numb;
    return first.pos > second.pos;
}

//Поиск ребенка
int findChild(vector <Node*> nodes, char c)
{
    for (auto &n : nodes)
        if (n->toParent == c)
            return &n - &nodes[0]; //возвращаем номер в массиве
    return -1;
}

//Добавление слова в бор
void addString(string s, int stringNumber, Node* root)
{
    Node* cur = root;
    for (auto &c : s)
    {
        Node* newNode = new Node(cur, c);
        if (findChild(cur->children, c) == -1)
            cur->children.push_back(newNode);
        cur = cur->children[findChild(cur->children, c)];
    }
    cur->end = true;
    cur->endStringNumber.push_back(stringNumber);
}

Node* getSuffLink(Node* v, Node* root);

/*  Переход к ребёнку
 * Если есть - возвращаем на него указатель
 * Если нет:
 * 1 Если родитель - корень, возвращаем корень
 * 2 Если нет - находим суффикс поменьше
*/
Node* getLink(Node* v, char c, Node* root)
{
    if (findChild(v->go, c) == -1)
    {
        if (findChild(v->children, c) != -1)
            v->go.push_back(v->children[findChild(v->children, c)]);
        else if ( v == root )
            v->go.push_back(root);
        else
            v->go.push_back(getLink(getSuffLink(v, root), c, root));
    }
    if (findChild(v->go, c) != -1)
        return v->go[findChild(v->go, c)];
    return v->go.back();
}


/*  Поиск суффиксной ссылки
 * Пока не найден ребенок по символу
 * исследуем суффиксы пока не дошли до корня
 */
Node* getSuffLink(Node* v, Node* root)
{
    if (!v->suffLink)
    {
        if (v == root || v->parent == root)
            v->suffLink = root;
        else
            v->suffLink = getLink(getSuffLink(v->parent, root), v->toParent, root);
    }
    return v->suffLink;
}


/* Поиск сжатой суффиксной ссылки
 * Пока суффиксная ссылка не привела в терминал или корень
 */
Node* getDictSuffLink(Node* v, Node* root)
{
    if (!v->dictSuffLink)
    {
        if (getSuffLink(v, root)->end)
            v->dictSuffLink = getSuffLink(v, root);
        else if (getSuffLink(v, root) == root)
            v->dictSuffLink = root;
        else
            v->dictSuffLink = getDictSuffLink(getSuffLink(v, root), root);
    }
    return v->dictSuffLink;
}

priority_queue <result, vector<result>, greater<result> > processText(string T, vector <string> P, priority_queue <result, vector<result>, greater<result> > q)
{
    Node* root = new Node(NULL, '~');
    for (auto &s: P)
        addString(s, &s - &P[0], root);
    Node* cur = root;
    for (auto &c: T)
    {
        cur = getLink(cur, c, root);
        Node* dsl = cur;
        do
        {
            for (auto &n : dsl->endStringNumber)
            {
                q.push(result(&c - &T[0] - P[n].length() + 2, n + 1));
            }
            dsl = getDictSuffLink(dsl, root);
        } while (dsl != root);
    }
    return q;
}

int main()
{
    ifstream fin("input.txt");
    string T;
    string tmpstring;
    int n;
    vector <string> P;
    fin >> T;
    fin >> n;
    //cin >> T;
    //cin >> N;
    //while(cin >> tmpstring)
        //P.push_back(tmpstring);
    while (fin >> tmpstring)
        P.push_back(tmpstring);
    fin.close();
    priority_queue <result, vector<result>, greater<result> > q;
    q = processText(T, P, q);
    while (!q.empty())
    {
        cout << q.top().pos << ' ' << q.top().numb << endl;
        q.pop();
    }
    return 0;
}
