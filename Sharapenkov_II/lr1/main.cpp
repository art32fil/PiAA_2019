#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <time.h>

#define N 41

struct valley {
    int l;
    int r;
    int done;
    int x;
    int y;
};

struct found {
    int level;

    explicit found(int _level)
            : level(_level) {}
};

static valley valleys[N][N + 1];
static int logs[N][2];

static void search(int level, int width, int bound);

static void searchT(int level, int width)
{

    if (width == 0)
        throw found(level);

    for (int i = 0; i < width; i++) {
        if (valleys[level][i].l == valleys[level][i].r &&
            valleys[level][i].done < valleys[level][i].r)
        {
            int w = valleys[level][i].l;
            for (int j = 0; j < i; j++) {
                valleys[level+1][j] = valleys[level][j];
                valleys[level+1][j].done =
                        std::min(valleys[level+1][j].l, valleys[level+1][j].r);
            }
            for (int j = i; j < width-1; j++)
                valleys[level+1][j] = valleys[level][j+1];
            logs[level][0] = i+1;
            logs[level][1] = w;
            if (i > 0)
                valleys[level+1][i-1].r += w;
            valleys[level+1][i].l += w;
            searchT(level+1, width-1);
        }
    }
}

static void searchT1(int level, int width)
{

    if (width == 0)
        throw found(level);

    for (int i = 0; i < width; i++) {
        int w = std::min(valleys[level][i].l, valleys[level][i].r);
        if (valleys[level][i].done < w) {
            for (int j = 0; j < i; j++) {
                valleys[level+1][j] = valleys[level][j];
                valleys[level+1][j].done =
                        std::min(valleys[level+1][j].l, valleys[level+1][j].r);
            }
            if (valleys[level][i].l == valleys[level][i].r) {
                if (i > 0)
                    valleys[level+1][i-1].r += w;
                valleys[level+1][i].l = valleys[level][i+1].l + w;
                valleys[level+1][i].r = valleys[level][i+1].r;
                valleys[level+1][i].y = valleys[level][i+1].y;
                valleys[level+1][i].x = valleys[level][i+1].x;
                valleys[level+1][i].done = valleys[level][i+1].done;
                for (int j = i+1; j < width-1; j++)
                    valleys[level+1][j] = valleys[level][j+1];
                logs[level][0] = i+1;
                logs[level][1] = w;
                searchT1(level+1, width-1);
            } else if (valleys[level][i].l == w) {
                if (i > 0)
                    valleys[level+1][i-1].r += w;
                valleys[level+1][i].l = valleys[level][i].l;
                valleys[level+1][i].r = valleys[level][i].r - w;
                valleys[level+1][i].y = valleys[level][i].y;
                valleys[level+1][i].x = valleys[level][i].x + w;
                valleys[level+1][i].done = 0;
                for (int j = i+1; j < width; j++)
                    valleys[level+1][j] = valleys[level][j];
                logs[level][0] = i+1;
                logs[level][1] = w;
                searchT(level+1, width);
            } else {
                valleys[level+1][i].l = valleys[level][i].l - w;
                valleys[level+1][i].r = valleys[level][i].r;
                valleys[level+1][i].y = valleys[level][i].y + w;
                valleys[level+1][i].x = valleys[level][i].x;
                valleys[level+1][i].done = 0;
                valleys[level+1][i+1].l = valleys[level][i+1].l + w;
                valleys[level+1][i+1].r = valleys[level][i+1].r;
                valleys[level+1][i+1].y = valleys[level][i+1].y;
                valleys[level+1][i+1].x = valleys[level][i+1].x;
                valleys[level+1][i+1].done = valleys[level][i+1].done;
                for (int j = i+2; j < width; j++)
                    valleys[level+1][j] = valleys[level][j];
                logs[level][0] = i+1;
                logs[level][1] = w;
                searchT(level+1, width);
            }
        }
    }
}

double b;

static void search(int level, int width, int bound) {

    if (width == 0) {
        throw found(level);
    }

    if (width > bound) {
        return;
    }

    if (width == bound) {
        searchT(level, width);
        return;
    }
    if (width == bound-1) {
        searchT1(level, width);
        return;
    }

    for (int i = 0; i < width; i++) {
        int w = std::min(valleys[level][i].l, valleys[level][i].r);
        int w1 = valleys[level][i].done + 1;
        if (w1 <= w) {
            for (int j = 0; j < i; j++) {
                valleys[level + 1][j] = valleys[level][j];
                valleys[level + 1][j].done =
                        std::min(valleys[level][j].l, valleys[level][j].r);
            }
            if (w1 < w) {
                valleys[level + 1][i].l = valleys[level][i].l - w1;
                valleys[level + 1][i].r = w1;
                valleys[level + 1][i].y = valleys[level][i].y + w1;
                valleys[level + 1][i].x = valleys[level][i].x;
                valleys[level + 1][i].done = 0;
                valleys[level + 1][i + 1].l = w1;
                valleys[level + 1][i + 1].r = valleys[level][i].r - w1;
                valleys[level + 1][i + 1].y = valleys[level][i].y;
                valleys[level + 1][i + 1].x = valleys[level][i].x + w1;
                valleys[level + 1][i + 1].done = 0;
                for (int j = i + 1; j < width; j++)
                    valleys[level + 1][j + 1] = valleys[level][j];
                logs[level][0] = i + 1;
                for (;;) {
                    logs[level][1] = w1;
                    search(level + 1, width + 1, bound - 1);
                    if(++w1 >= w)
                        break;
                    valleys[level + 1][i].l--;
                    valleys[level + 1][i].r = w1;
                    valleys[level + 1][i].y++;
                    valleys[level + 1][i].x = valleys[level][i].x;
                    valleys[level + 1][i + 1].l = w1;
                    valleys[level + 1][i + 1].r--;
                    valleys[level + 1][i + 1].y = valleys[level][i].y;
                    valleys[level + 1][i + 1].x++;
                }
            }
            if (valleys[level][i].l == valleys[level][i].r && level != 0) {
                if (i > 0)
                    valleys[level + 1][i - 1].r += w;
                valleys[level + 1][i].l = valleys[level][i + 1].l + w;
                valleys[level + 1][i].r = valleys[level][i + 1].r;
                valleys[level + 1][i].y = valleys[level][i + 1].y;
                valleys[level + 1][i].x = valleys[level][i + 1].x;
                valleys[level + 1][i].done = valleys[level][i + 1].done;
                for (int j = i + 1; j < width - 1; j++)
                    valleys[level + 1][j] = valleys[level][j + 1];
                logs[level][0] = i + 1;
                logs[level][1] = w;
                search(level + 1, width - 1, bound - 1);
            } else if (valleys[level][i].l == w) {
                if (i > 0)
                    valleys[level + 1][i - 1].r += w;
                valleys[level + 1][i].l = valleys[level][i].l;
                valleys[level + 1][i].r = valleys[level][i].r - w;
                valleys[level + 1][i].y = valleys[level][i].y;
                valleys[level + 1][i].x = valleys[level][i].x + w;
                valleys[level + 1][i].done = 0;
                for (int j = i + 1; j < width; j++)
                    valleys[level + 1][j] = valleys[level][j];
                logs[level][0] = i + 1;
                logs[level][1] = w;
                search(level + 1, width, bound - 1);
            } else {
                valleys[level + 1][i].l = valleys[level][i].l - w;
                valleys[level + 1][i].r = valleys[level][i].r;
                valleys[level + 1][i].y = valleys[level][i].y + w;
                valleys[level + 1][i].x = valleys[level][i].x;
                valleys[level + 1][i].done = 0;
                valleys[level + 1][i + 1].l = valleys[level][i + 1].l + w;
                valleys[level + 1][i + 1].r = valleys[level][i + 1].r;
                valleys[level + 1][i + 1].y = valleys[level][i + 1].y;
                valleys[level + 1][i + 1].x = valleys[level][i + 1].x;
                valleys[level + 1][i + 1].done = valleys[level][i + 1].done;
                for (int j = i + 2; j < width; j++)
                    valleys[level + 1][j] = valleys[level][j];
                logs[level][0] = i + 1;
                logs[level][1] = w;
                search(level + 1, width, bound - 1);
            }
        }
    }
}

void decryptCoords(int bound, std::stringstream &s) {

    for (int lvl = 0; lvl < bound; lvl++) {
        int order = logs[lvl][0] - 1;
        s << valleys[lvl][order].x << " " << valleys[lvl][order].y << " " << logs[lvl][1] << std::endl;
    }

}

bool isPrime(int n) {
    int i, flag = 0;
    if(n == 2) return false;
    for (i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            flag = 1;
            break;
        }
    }
    return !flag;
}

int main(int argc, char **argv) {

    int x, y;

    std::cin >> x;

    y = x;
    std::string reason, coords;

    for(int i = 2; i <= 40; i++) {

        clock_t start = clock();
        x = y = i;

        b = 6*log2(x);

        int bound = int(b);

        if(isPrime(x)) {
            valleys[0][0].l = x;
            valleys[0][0].r = y;
            valleys[0][0].x = 0;
            valleys[0][0].y = 0;
            valleys[0][0].done = x / 2 + 1;
            logs[0][0] = 1;
            logs[0][1] = x / 2 + 1;
            valleys[1][0].l = x / 2;
            valleys[1][0].r = x / 2 + 1;
            valleys[1][0].x = 0;
            valleys[1][0].y = x / 2 + 1;
            valleys[1][0].done = x / 2;
            valleys[1][1].l = x / 2 + 1;
            valleys[1][1].r = x / 2;
            valleys[1][1].x = x / 2 + 1;
            valleys[1][1].y = 0;
            valleys[1][1].done = x / 2;
            logs[1][0] = 1;
            logs[1][1] = x / 2;
            valleys[2][0].l = x / 2;
            valleys[2][0].r = 1;
            valleys[2][0].x = x / 2;
            valleys[2][0].y = x / 2 + 1;
            valleys[2][0].done = 0;
            valleys[2][1].l = x / 2 + 1;
            valleys[2][1].r = x / 2;
            valleys[2][1].x = x / 2 + 1;
            valleys[2][1].y = 0;
            valleys[2][1].done = x / 2;
            valleys[3][0].l = x / 2;
            valleys[3][0].r = 1;
            valleys[3][0].x = x / 2;
            valleys[3][0].y = x / 2 + 1;
            valleys[3][0].done = 0;
            valleys[3][1].l = 1;
            valleys[3][1].r = x / 2;
            valleys[3][1].x = x / 2 + 1;
            valleys[3][1].y = x / 2;
            valleys[3][1].done = 0;
            logs[2][0] = 2;
            logs[2][1] = x / 2;
            for (;;) {
                try {
                    search(3, 2, bound - 1 - 3);
                } catch (found& f) {
                    bound = f.level;
                    std::stringstream s;
                    s << bound << std::endl;
                    decryptCoords(bound, s);
                    reason = s.str();
                    continue;
                }

                break;
            }
        } else {
            valleys[0][0].l = x;
            valleys[0][0].r = y;
            valleys[0][0].x = 0;
            valleys[0][0].y = 0;
            valleys[0][0].done = 0;
            for (;;) {
                try {
                    search(0, 1, bound - 1);
                } catch (found& f) {
                    bound = f.level;
                    std::stringstream s;
                    s << bound << std::endl;
                    decryptCoords(bound, s);
                    reason = s.str();
                    continue;
                }
                break;
            }
        }

        clock_t stop = clock();

        std::cout << "Number: " << x << std::endl
                << "Execution time: " << double(stop-start) / CLOCKS_PER_SEC << std::endl;
        std::cout << reason << std::endl;

    }
}