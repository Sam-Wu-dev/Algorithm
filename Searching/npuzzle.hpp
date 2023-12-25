#ifndef npuzzle_hpp
#define npuzzle_hpp
#include <vector>
#include <queue>
#include <math.h>
#include <stack>
#include <memory>
#include <unordered_set>
using namespace std;

#define axis pair<int, int>
const int grid_size = 4;

pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b)
{
    return {a.first + b.first, a.second + b.second};
}
pair<int, int> operator-(const pair<int, int> &a, const pair<int, int> &b)
{
    return {a.first - b.first, a.second - b.second};
}
class N_puzzle
{
protected:
    struct Movement
    {
        enum Dir
        {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };
        static axis get_dir(Dir m)
        {
            vector<axis> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
            return directions[static_cast<int>(m)];
        }
        static Dir get_dir(axis m)
        {
            if (m.first == -1 && m.second == 0)
            {
                return UP;
            }
            if (m.first == 1 && m.second == 0)
            {
                return DOWN;
            }
            if (m.first == 0 && m.second == -1)
            {
                return LEFT;
            }
            if (m.first == 0 && m.second == 1)
            {
                return RIGHT;
            }
            throw("Unknown movement direction");
        }
        static Dir reverse(Dir m)
        {
            vector<Dir> arr = {DOWN, LEFT, UP, RIGHT};
            return arr[static_cast<int>(m)];
        }

        static string to_string(Dir m)
        {
            vector<string> strings = {"UP", "RIGHT", "DOWN", "LEFT"};
            return strings[static_cast<int>(m)];
        }
    };

    const vector<vector<int>> &initialState;
    const vector<vector<int>> &finalState;
    size_t maxStates = 0;
    vector<Movement::Dir> moves;

    struct Node
    {
        std::shared_ptr<Node> parent;
        vector<vector<int>> image;
        axis now;
        Node(std::shared_ptr<Node> p, vector<vector<int>> i, axis n) : parent(std::move(p)), image(i), now(n) {}
    };

    void getPath(shared_ptr<Node> node)
    {
        while (node->parent)
        {
            moves.push_back(Movement::get_dir(node->parent->now - node->now));
            node = node->parent;
        }
    }

    bool valid(axis a)
    {
        return a.first >= 0 && a.second >= 0 && a.first < grid_size && a.second < grid_size;
    }
    axis find(const vector<vector<int>> &initialState, int num)
    {
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if (initialState[i][j] == num)
                    return {i, j};
            }
        }
        return {-1, -1};
    }
    int heuristic(const vector<vector<int>> &initialState, const vector<vector<int>> &finalState)
    {
        int distance = 0;
        vector<axis> a(grid_size * grid_size), b(grid_size * grid_size);
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                a[initialState[i][j]] = {i, j};
                b[finalState[i][j]] = {i, j};
            }
        }
        for (int i = 0; i < a.size(); i++)
        {
            distance += Manhattan_distance(a[i], b[i]);
        }
        return distance;
    }
    float Manhattan_distance(axis now, axis target)
    {
        // Manhattan distance
        return abs(target.first - now.first) + abs(target.second - now.second);
    }
    string createStateKey(const vector<vector<int>> &state) const
    {
        string key;
        for (const auto &row : state)
        {
            for (int val : row)
            {
                key += to_string(val) + ",";
            }
        }
        return key;
    }

public:
    N_puzzle(const vector<vector<int>> &is, const vector<vector<int>> &fs)
        : initialState(is), finalState(fs) {}

    // Method to get the number of movements (steps) taken in the shortest path.
    int getNumberOfMovements() const
    {
        return moves.size();
    }

    // Method to get the maximum number of states ever saved in memory during the search process.
    int getMaxStatesInMemory() const
    {
        return maxStates;
    }

    void analysis()
    {
        cout << "Total number of moves: " << getNumberOfMovements() << endl;
        cout << "Maximum number of states ever saved in memory: " << getMaxStatesInMemory() << endl;
        cout << "Shortest path:" << endl;
        for (auto m : moves)
        {
            cout << Movement::to_string(m) << " ";
        }
        cout << endl;
    }
};

class IDFS : public N_puzzle
{
private:
    int minMoveNum = 0;
    struct DFSNode : public Node
    {
        int g; // Additional property for DFS

        DFSNode(std::shared_ptr<Node> p, vector<vector<int>> i, axis n, int d)
            : Node(std::move(p), std::move(i), n), g(d) {}
    };

public:
    IDFS(const vector<vector<int>> &initialState, const vector<vector<int>> &finalState) : N_puzzle(initialState, finalState) {}
    bool solve()
    {
        maxStates = 0;
        moves.clear();
        minMoveNum = 0;
        bool result = false;
        do
        {
            cout << "Depth limit: " << ++minMoveNum << endl;
            result = DFS(minMoveNum);
        } while (!result);
        return true;
    }
    bool DFS(int depth_limit)
    {
        stack<shared_ptr<DFSNode>> bt;
        bt.push(make_shared<DFSNode>(nullptr, initialState, find(initialState, 0), 0));
        std::unordered_set<std::string> visited;
        std::string target = createStateKey(finalState);
        while (!bt.empty())
        {
            auto node = bt.top();
            bt.pop();
            if (createStateKey(node->image) == target)
            {
                getPath(node);
                maxStates = visited.size();
                return true;
            }
            for (int i = 0; i < 4; i++)
            {
                auto move = static_cast<Movement::Dir>(i);
                auto dir = Movement::get_dir(move);
                auto next = node->now + dir;
                if (valid(next))
                {
                    vector<vector<int>> after = node->image;
                    swap(after[node->now.first][node->now.second], after[next.first][next.second]);
                    std::string stateKey = createStateKey(after);
                    if (visited.find(stateKey) == visited.end() && node->g + 1 <= depth_limit)
                    {
                        bt.push(make_shared<DFSNode>(node, after, next, node->g + 1));
                        visited.insert(stateKey);
                    }
                }
            }
        }
        maxStates = visited.size();
        return false;
    }
};
class BFS : public N_puzzle
{
protected:
    struct BFSNode : public Node
    {
        int f; // cost
        int g; // depth

        BFSNode(vector<vector<int>> v, std::shared_ptr<BFSNode> p, axis n, int g, int f)
            : Node(std::move(p), std::move(v), n), g(g), f(f) {}

        bool operator>(const BFSNode &other) const
        {
            return f > other.f;
        }
    };
    struct CompareBFSNode
    {
        bool operator()(const std::shared_ptr<BFSNode> &a, const std::shared_ptr<BFSNode> &b) const
        {
            return *a > *b; // Assuming AStarNode has operator> defined
        }
    };

public:
    BFS(const vector<vector<int>> &initialState, const vector<vector<int>> &finalState) : N_puzzle(initialState, finalState) {}
    template <typename Func>
    bool solve(Func func)
    {
        maxStates = 0;
        moves.clear();
        std::priority_queue<std::shared_ptr<BFSNode>, vector<std::shared_ptr<BFSNode>>, CompareBFSNode> pq;
        pq.push(make_shared<BFSNode>(initialState, nullptr, find(initialState, 0), 0, 0));
        std::unordered_set<std::string> visited;
        string target = createStateKey(finalState);
        while (!pq.empty())
        {
            std::shared_ptr<BFSNode> node = pq.top();
            pq.pop();
            if (createStateKey(node->image) == target)
            {
                getPath(node);
                maxStates = visited.size();
                return true;
            }
            for (int i = 0; i < 4; i++)
            {
                auto move = static_cast<Movement::Dir>(i);
                auto dir = Movement::get_dir(move);
                auto next = node->now + dir;
                if (valid(next))
                {
                    vector<vector<int>> after = node->image;
                    swap(after[node->now.first][node->now.second], after[next.first][next.second]);
                    std::string stateKey = createStateKey(after);
                    int cost = func(node->g, after, finalState);
                    if (visited.find(stateKey) == visited.end())
                    {
                        pq.push(std::make_shared<BFSNode>(after, node, next, node->g + 1, cost));
                        visited.insert(stateKey);
                    }
                }
            }
        }
        maxStates = visited.size();
        return false;
    }
};
class AStar : public BFS
{
public:
    AStar(const vector<vector<int>> &initialState, const vector<vector<int>> &finalState)
        : BFS(initialState, finalState) {}
    bool solve()
    {
        auto g_plus_h = [this](int pre_g, const vector<vector<int>> &initialState, const vector<vector<int>> &finalState)
        {
            return heuristic(initialState, finalState) + pre_g + 1;
        };

        return BFS::solve(g_plus_h);
    }
};
class UCS : public BFS
{
public:
    UCS(const vector<vector<int>> &initialState, const vector<vector<int>> &finalState) : BFS(initialState, finalState) {}
    bool solve()
    {
        auto g = [this](int pre_g, const vector<vector<int>> &initialState, const vector<vector<int>> &finalState)
        {
            return pre_g + 1;
        };

        return BFS::solve(g);
    }
};
class GBFS : public BFS
{
public:
    GBFS(const vector<vector<int>> &initialState, const vector<vector<int>> &finalState) : BFS(initialState, finalState) {}
    bool solve()
    {
        auto h = [this](int pre_g, const vector<vector<int>> &initialState, const vector<vector<int>> &finalState)
        {
            return heuristic(initialState, finalState);
        };

        return BFS::solve(h);
    }
};
class RBFS : public BFS
{
private:
    string target;

public:
    RBFS(const vector<vector<int>> &initialState, const vector<vector<int>> &finalState) : BFS(initialState, finalState) {}

    bool solve()
    {
        maxStates = 0;
        moves.clear();
        target = createStateKey(finalState);
        auto result = R_BFS(std::make_shared<BFSNode>(initialState, nullptr, find(initialState, 0), 0, heuristic(initialState, finalState)), INT_MAX, 0);
        return result.first;
    }
    pair<bool, int> R_BFS(shared_ptr<BFSNode> node, int f_limit, size_t stateNum)
    {
        maxStates = max(maxStates, stateNum);
        if (createStateKey(node->image) == target)
        {
            getPath(node); // use parent to get path
            return {true, node->f};
        }
        std::priority_queue<std::shared_ptr<BFSNode>, vector<std::shared_ptr<BFSNode>>, CompareBFSNode> pq;
        for (int i = 0; i < 4; i++)
        {
            auto move = static_cast<Movement::Dir>(i);
            auto dir = Movement::get_dir(move);
            auto next = node->now + dir;
            if (valid(next))
            {
                vector<vector<int>> after = node->image;
                swap(after[node->now.first][node->now.second], after[next.first][next.second]);
                int cost = max(node->f, heuristic(after, finalState) + node->g + 1);
                pq.push(std::make_shared<BFSNode>(after, node, next, node->g + 1, cost));
            }
        }
        int count = pq.size();
        while (!pq.empty())
        {
            auto best = pq.top();
            pq.pop();
            if (best->f > f_limit)
                return {false, best->f};
            if (pq.empty())
            {
                return R_BFS(best, f_limit, stateNum + count);
            }
            auto second = pq.top();
            auto result = R_BFS(best, min(second->f, f_limit), stateNum + count);
            best->f = result.second;
            pq.push(best);
            if (result.first)
            {
                return result;
            }
        }
        return {false, INT_MAX};
    }
};
#endif