// Fast version, taken from somewhere I don't remember.
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>

const int rows=80;
const int cols=80;
int input[rows*cols]; // input matrix goes here
int mat[rows*cols]; // temporary results are kept here
// initialize mat[] as:
// for(int i=0;i<rows*cols;i++)
//     mat[i] = std::numeric_limits<int>::max();

// std::priority_queue, by default, sorts elements in descending order
// we need them in ascending order
class greater
{
public:
    bool operator()(const int i1, const int i2) { return mat[i1]>mat[i2]; }
};
typedef std::priority_queue<int,std::vector<int>,greater> PQ;

// helps keeping code short and easy to understand
#define CHECK(na) {if(mat[na] > mat[a]+input[na]) { mat[na] = mat[a]+input[na]; pq.push(na); }}

// returns minimal sum
int dijkstra()
{
    PQ pq;
    pq.push(0);
    mat[0] = input[0];
    while(!pq.empty())
    {
        int a = pq.top();
        pq.pop();

        if(a>=cols) CHECK(a-cols) // up
        if(a%cols!=0) CHECK(a-1) // left
        if(a%cols!=(cols-1)) CHECK(a+1) // right
        if(a<(rows-1)*cols) CHECK(a+cols) // down
    }

    return mat[rows*cols-1];
}

int main() {
    std::ifstream f("/Users/bendik/drive/project-euler/083/p082_matrix.txt");

    int i = 0;
    while (f >> input[i]) {
        f.ignore(1, ',');
        mat[i++] = std::numeric_limits<int>::max();
    }
    printf("%d\n", dijkstra());
    return 0;
}
