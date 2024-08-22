#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class HANOI {
private:
    int sort_count;
    int n;
    vector<stack<int>> towers;

    void block_move(int _source, int _target, int s_val = 0, int t_val = 0) {
        sort_count++;
        cout << sort_count << ". Moved block: " << _source << "(" << s_val << ") -> " << _target << "(" << t_val << ")" << endl;
        towers[_target].push(towers[_source].top());
        towers[_source].pop();
    }

    void hanoi(int n, int _source, int _target, int _auxiliary) {
        if (n == 1) {
            move(_source, _target);
        } else {
            hanoi(n - 1, _source, _auxiliary, _target);
            move(_source, _target);
            hanoi(n - 1, _auxiliary, _target, _source);
        }
    }

    void count_sort(int n, int _source, int _target, int _auxiliary) {
        if (n == 1) {
            move(_source, _target);
            sort_count++;
        } else {
            count_sort(n - 1, _source, _auxiliary, _target);
            move(_source, _target);
            sort_count++;
            count_sort(n - 1, _auxiliary, _target, _source);
        }
    }

public:
    HANOI() : sort_count(0), n(0) {
        towers.resize(3);
    }

    void reset(int _n) {
        n = _n;
        towers[0] = stack<int>();
        towers[1] = stack<int>();
        towers[2] = stack<int>();
        for (int i = n; i > 0; i--) {
            towers[0].push(i);
        }
    }

    bool move(int _source, int _target) {
        if (_source < 0 || _source >= 3 || _target < 0 || _target >= 3) {
            cout << "Move fail: source or target is out of range" << endl;
            return false;
        }

        if (_source == _target) {
            cout << "Move fail: source and target are the same" << endl;
            return false;
        }

        if (towers[_source].empty()) {
            cout << "Move fail: source is empty" << endl;
            return false;
        }

        int source_val = towers[_source].top();

        if (towers[_target].empty()) {
            block_move(_source, _target, source_val);
            return true;
        }

        int target_val = towers[_target].top();

        if (source_val > target_val) {
            cout << "Move fail: source is bigger than target" << endl;
            return false;
        }

        block_move(_source, _target, source_val, target_val);
        return true;
    }

    void sort() {
        sort_count = 0;
        count_sort(n, 0, 1, 2);
    }

    void print() {
        for (int i = 0; i < 3; i++) {
            cout << "Tower " << i << ": ";
            stack<int> temp = towers[i];
            while (!temp.empty()) {
                cout << temp.top() << " ";
                temp.pop();
            }
            cout << endl;
        }
    }
};

int main() {
    int block_num;
    cout << "Enter number of blocks: ";
    cin >> block_num;

    HANOI hanoi;
    hanoi.reset(block_num);

    cout << "Before sort" << endl;
    hanoi.print();
    cout << endl;

    hanoi.sort();

    cout << endl;
    cout << "After sort" << endl;
    hanoi.print();

    cout << endl;
    system("pause");

    return 0;
}
