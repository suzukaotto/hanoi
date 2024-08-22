class HANOI:    
    def __init__(self):
        self.sort_count = 0
    
    def reset(self, _n):
        self.towers = [[], [], []]
        self.n = _n
        self.towers[0] = list(range(self.n, 0, -1))
    
    def move(self, _source: int, _target: int):
        def block_move(s_val=" ", t_val=" "):
            print(f"{self.sort_count+1}. Moved block: {_source}({s_val}) -> {_target}({t_val})")
            self.towers[_target].append(self.towers[_source].pop())
        
        if (_source < 0 or _source > self.n) or (_target < 0 or _target > self.n):
            print("Move fail: source or target is out of range")
            return False
        
        if _source == _target:
            print("Move fail: source and target are the same")
            return False
        
        if self.towers[_source] == []:
            print("Move fail: source is empty")
            return False
        
        source_val = self.towers[_source][-1]
        
        if self.towers[_target] == []:
            block_move(s_val=source_val)
            return True
        
        source_val = self.towers[_source][-1]
        target_val = self.towers[_target][-1]
        
        if source_val > target_val:
            print("Move fail: source is bigger than target")
            return False
        
        block_move(s_val=source_val, t_val=target_val)
        return True
    
    def sort(self):
        def hanoi(n, _source, _target, _auxiliary):
            if n == 1:
                self.move(_source, _target)
            else:
                hanoi(n - 1, _source, _auxiliary, _target)
                self.move(_source, _target)
                hanoi(n - 1, _auxiliary, _target, _source)
        
        self.sort_count = 0
        
        def count_sort(n, _source, _target, _auxiliary):
            if n == 1:
                self.move(_source, _target)
                self.sort_count += 1
            else:
                count_sort(n - 1, _source, _auxiliary, _target)
                self.move(_source, _target)
                self.sort_count += 1
                count_sort(n - 1, _auxiliary, _target, _source)
        
        count_sort(self.n, 0, 1, 2)

    def print(self):
        print(self.towers)


hanoi = HANOI()
hanoi.reset(8)

print("Before sort")
hanoi.print()
print()

hanoi.sort()

hanoi.print()
print("After sort")
