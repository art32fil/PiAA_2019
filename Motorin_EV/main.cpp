//
// main.cpp
// FirstLabPIAA
//
// Created by Михаил Дементьев on 15/02/2019.
// Copyright © 2019 Михаил Дементьев. All rights reserved.
//

#include <iostream>
#include <cstring>

using namespace std;

int f[2505];
int M = 20;
int ind = 1;
int N;

bool a[55][55];
int r[55][55], d[55][55];

struct AS
{
int len;
int x, y;
} tmp[2505], ans[2505];

struct SS
{
int y, high;
} stack[55];

inline void backtracking(int x, int y, int square, int SQ){

if (square + f[SQ] >= M)
return;

if (x<N)
{
int tot = 0;
for (int i = 1; i <= N; ++i)
if (a[x + 1][i])
i += r[x + 1][i];
else
{
while (i<N && !a[x + 1][i])
++i;
++tot;
}
if (square + tot >= M)
return;
}
if (x>N)
{
// Сохраняем новое приближение
M = square;
memcpy(ans, tmp, sizeof(AS)*M);
ind++;
return;
}
else if (y>N)
{
int i, top = 0, tot = 0, mid, s = 0, tmp;
++x;
if (x <= N)
{
for (i = 1; i <= N; ++i)
if (!a[x][i])
{
while (i < N && !a[x][i + 1])++i;
{
struct SS n;
n.y = i;
n.high = 0;
stack[top++] = n;
}
}
else
{
if (top&&stack[top - 1].high <= d[x][i])
{
mid = stack[--top].high;
if (top)
while (top&&stack[top - 1].high <= d[x][i])
{
--top;
if (i - stack[top].y - 1 <= stack[top].high - mid)
tmp = (stack[top].high - mid) / (i - stack[top].y - 1);
else tmp = 0;
tot += tmp;
s += (stack[top].high - mid)*(i - stack[top].y - 1) -
tmp * (i - stack[top].y - 1)*(i - stack[top].y - 1);
mid = stack[top].high;
}
else
if (d[x][i] != mid)
{
if (i - 1 <= d[x][i] - mid)tmp = (d[x][i] - mid) / (i - 1);
else tmp = 0;
tot += tmp;
s += (d[x][i] - mid)*(i - 1) - tmp * (i - 1)*(i - 1);
}
}
struct SS n;
n.y = i + r[x][i] - 1;
n.high = d[x][i];
stack[top++] = n;
i += r[x][i] - 1;
}

mid = stack[top - 1].high;

if (top)
{
while (--top)
s += (stack[top].y - stack[top - 1].y)*(N - (x + stack[top].high - 1));
s += stack[top].y*(N - (x + stack[top].high - 1));
}
else
if (N != x + mid - 1)
tot += N / (N - (x + mid - 1));

if (square + tot + f[s] >= M)
return;
}

backtracking(x, 1, square, SQ);
}
else
if (a[x][y])
backtracking(x, y + r[x][y], square, SQ);
else
{
int i = y;
while (i - y + 2<N && i<N && i<N - x + y && !a[x][i + 1])
++i;
int j, len = i - y + 1;
for (i = 0; i<len; ++i)
for (j = 0; j<len; ++j)
a[x + i][y + j] = 1;
for (; len; --len)
{
r[x + len][y] = 0;
for (i = 0; i<len; ++i)
r[x + i][y] = len;
for (i = 0; i <= len; ++i)
d[x + i][y] = len - i;

struct AS n;
n.len = len;
n.x = x;
n.y = y;
tmp[square] = n;

backtracking(x, y + len, square + 1, SQ - len * len);
for (i = 0; i<len; ++i)
a[x + len - 1][y + i] = 0;
for (i = 0; i<len; ++i)
a[x + i][y + len - 1] = 0;
}
}
}

int mainsolver(int t)
{

// Выделение памяти
memset(f, 127, sizeof(f));
f[0] = 0;
for (int i = 1; i <= 2500; ++i)
{
for (int j = 1; j*j <= i; ++j)
f[i] = min(f[i], f[i - j * j]);
++f[i];
}

M = 20;
N = 0;
ind = 1;
N = t;

// Вызов функции backstrackingа
memset(a, 0, sizeof(a));
backtracking(1, 1, 0, N*N);

// Вывод сообщения о всех квадратах и их координатах в QLabel
//cout « "Минимальное число\nквадратов: " « M « "\n\n";
cout << M << endl;
for (int i = 0; i < M; ++i)
{
//cout « ". Вершина: (" « ans[i].x « "," « ans[i].y « ") Длина: " « ans[i].len « "\n\n";
cout << ans[i].x << " " << ans[i].y << " " << ans[i].len << endl;
}

return ind;
}

int main() {
int size;
//cout « "Введите длинну одной стороны: ";
cin >> size;

if (size <= 42 && size >=1 )
{
mainsolver(size);
}
return 0;
}
