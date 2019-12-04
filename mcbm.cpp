#include <bits/stdc++.h>
#include <pthread.h>
#define INF 1000000007
using namespace std;

int capacity[2005][2005];
int flowPassed[2005][2005];
int path_flow[2005];
int parent[2005];
vector<int> adj[2005];

int BFS(int source, int sink) {
    // reinitializing the pareng and path_flow array
    memset (parent, -1, sizeof(parent));
    memset (path_flow, 0, sizeof(path_flow));
    // initializing the queue (used for BFS)
    queue<int> q;
    // the source has no parent, and should not be visited
    parent[source] = -2;
    // push the source vertex to the queue
    q.push(source);
    // the source has infinite flow
    path_flow[source] = INF;
    // BFS Algorithm
    while (!q.empty()) {
        // get the front vertex, and pop it out of the queue
        int cur = q.front();
        q.pop();
        // iterate through all adjacent vertices
        for (int i=0;i<adj[cur].size();i++) {
            // obtain the adjacent vertex
            int next = adj[cur][i];
            // don't visit a visited vertex
            if (parent[next] == -1) {
                // if flow is still below capacity
                if (capacity[cur][next] > flowPassed[cur][next]) {
                    // set the parent for backtracking
                    parent[next] = cur;
                    // the allowed flow is the minimum of current flow in current node and allowed flow in an edge
                    path_flow[next] = min(path_flow[cur], capacity[cur][next] - flowPassed[cur][next]);
                    // if we already arrived at the sink, simply return the flow
                    if (next == sink) return path_flow[cur];
                    // insert the new vertex into queue
                    else q.push(next);
                }
            }
        }
    }

    return 0;
}

int maxflow(int source, int sink) {
    int maxFlow = 0;
    while (true) {
        int flow = BFS(source, sink);
        // all edges exhausted. not giving any more flows.
        if (flow == 0) break;
        int cur = sink;
        // add the flow to our answer
        maxFlow += flow;
        // backtracking the path
        while (cur != source) {
            int par = parent[cur];
            // decrease capacity of backward edges
            flowPassed[par][cur] += flow;
            // increase capacity of forward edges
            flowPassed[cur][par] -= flow;
            cur = par;
        }
    }
    return maxFlow;
}

int main () {
    clock_t start = clock();
    ifstream cin("tc7.in");
    ofstream cout("tc7.out");
    int N, M;
    cout << "Number of workers: ";
    cin >> N;
    cout << "Number of projects: ";
    cin >> M;
    int source = 0, sink = N + M + 1;
    memset (capacity, 0, sizeof(capacity));
    for (int i=1;i<=N;i++) {
        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i] = 1;
    }
    for (int i=1;i<=M;i++) {
        int maxAssigned;
        cout << "Workers required for project " << i << ": ";
        cin >> maxAssigned;
        int projectId = N + i;
        adj[projectId].push_back(sink);
        adj[sink].push_back(projectId);
        capacity[projectId][sink] = maxAssigned;
    }
    int preference;
    cout << "Number of preferences: ";
    cin >> preference;
    cout << "Preference list:" << endl;
    for (int i=1;i<=preference;i++) {
        int x,y;
        cin >> x >> y;
        // convert project into projectId
        y += N;
        adj[x].push_back(y);
        adj[y].push_back(x);
        capacity[x][y]=1;
    }
    cout << "Maximum flow: " << maxflow(source, sink) << endl;
    for (int i=1;i<=N;i++) {
        for (int j=N + 1;j <= N + M;j++) {
            if (flowPassed[i][j]) cout << "Worker " << i << " is assigned to project " << j-N << endl;
        }
    }
    cerr << "Time required: " << fixed << setprecision(3) << (clock()-start)*1./CLOCKS_PER_SEC << endl;
    return 0;
}