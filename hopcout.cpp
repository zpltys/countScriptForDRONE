#include<bits/stdc++.h>
using namespace std;

const int maxm = 58333344 + 10;
const int maxn = 23947347;

struct edge {
    int v;
    int type, nex, len;
}e[maxm];
int ee = 0;
int p[maxn], dis[maxn];
int fa[maxn], paType[maxn], hop[maxn];

int ans[10000];

void addedge(int u, int v, double len, int t) {
    e[ee].v = v; e[ee].len= int(len); e[ee].type = t; e[ee].nex = p[u];
    p[u] = ee++;
}

struct pai {
    int v, len;
    bool operator < (const pai& an) const {
        return len > an.len;
    }
};

int main() {
    int i;
    char filePath[1000];
    for (i = 0; i < maxn; i++) {
        dis[i] = 1e9 + 7;
        p[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        sprintf(filePath, "/mnt/nfs/xwen/graphData/G.%d", i);
        cout << filePath << endl;
        FILE *fp = fopen(filePath, "r");
        int u, v;
        double l;
        while (~fscanf(fp, "%d%d%lf", &u, &v, &l)) {
            addedge(u, v, l, i);
        }
    }

    int startId = 1;

    priority_queue<pai> pq;

    dis[startId] = 0;
    hop[startId] = 0;
    fa[startId] = startId;
    paType[startId] = 0;
    pai start;
    start.len = 0;
    start.v = startId;
    pq.push(start);

    while (!pq.empty()) {
        pai pp = pq.top();
        pq.pop();

        int s = pp.v;
        int nowDis = pp.len;
        if (nowDis > dis[s]) continue;
        for (i = p[s]; i != -1; i = e[i].nex) {
            int v = e[i].v;
            if (dis[v] <= nowDis + e[i].len) continue;
            dis[v] = nowDis + e[i].len;
            fa[v] = s;
            paType[v] = e[i].type;

            if (paType[v] == paType[s]) hop[v] = hop[s];
            else hop[v] = hop[s] + 1;

            pai npp;
            npp.len = dis[v];
            npp.v = v;
            pq.push(npp);
        }
    }

    for (i = 0; i < 10000; i++) ans[i] = 0;
    for (i = 0; i < maxn; i++) {
        ans[hop[i]]++;
    }

    for(i = 0; i < 1000; i++) printf("hop[%d]:%d\n", i, ans[i]);

    FILE* fp = fopen("hopcount.csv", "w+");
    fprintf(fp, "hop,count\n")
    for (i = 0; i < 10000; i++) {
        fprintf(fp, "%hop[d],%d\n", i, ans[i]);
    }
}

