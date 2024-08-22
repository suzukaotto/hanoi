#include <iostream>
#include <vector>
#include <stack>

class HANOI {
private:
    int sort_count;
    int n;
    std::vector<std::stack<int>> towers;

    void block_move(int _source, int _target, int s_val = 0, int t_val = 0) {
        sort_count++;
        std::cout << sort_count << ". Moved block: " << _source << "(" << s_val << ") -> " << _target << "(" << t_val << ")" << std::endl;
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
        towers[0] = std::stack<int>();
        towers[1] = std::stack<int>();
        towers[2] = std::stack<int>();
        for (int i = n; i > 0; i--) {
            towers[0].push(i);
        }
    }

    bool move(int _source, int _target) {
        if (_source < 0 || _source >= 3 || _target < 0 || _target >= 3) {
            std::cout << "Move fail: source or target is out of range" << std::endl;
            return false;
        }

        if (_source == _target) {
            std::cout << "Move fail: source and target are the same" << std::endl;
            return false;
        }

        if (towers[_source].empty()) {
            std::cout << "Move fail: source is empty" << std::endl;
            return false;
        }

        int source_val = towers[_source].top();

        if (towers[_target].empty()) {
            block_move(_source, _target, source_val);
            return true;
        }

        int target_val = towers[_target].top();

        if (source_val > target_val) {
            std::cout << "Move fail: source is bigger than target" << std::endl;
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
            std::cout << "Tower " << i << ": ";
            std::stack<int> temp = towers[i];
            while (!temp.empty()) {
                std::cout << temp.top() << " ";
                temp.pop();
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    HANOI hanoi;
    hanoi.reset(8);

    std::cout << "Before sort" << std::endl;
    hanoi.print();
    std::cout << std::endl;

    hanoi.sort();

    hanoi.print();
    std::cout << "After sort" << std::endl;

    return 0;
}
