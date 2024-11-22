def can_nest(box_a, box_b):
    return all(dim_a < dim_b for dim_a, dim_b in zip(box_a['dimensions'], box_b['dimensions']))

def find_longest_nesting_sequence(lines):
    results = []
    i = 0
    while i < len(lines):
        k, n = map(int, lines[i].split())
        i += 1
        boxes = []
        
        for j in range(k):
            dimensions = list(map(int, lines[i].split()))
            boxes.append({'index': j + 1, 'dimensions': sorted(dimensions)})
            i += 1
            
        boxes.sort(key=lambda box: box['dimensions'])
        
        graph = [[] for _ in range(k)]
        for u in range(k):
            for v in range(u + 1, k):
                if can_nest(boxes[u], boxes[v]):
                    graph[u].append(v)
        
        dp = [1] * k
        prev = [-1] * k
        
        for u in range(k):
            for v in graph[u]:
                if dp[u] + 1 > dp[v]:
                    dp[v] = dp[u] + 1
                    prev[v] = u
                elif dp[u] + 1 == dp[v] and u < prev[v]:
                    prev[v] = u
        
        max_length = 0
        max_index = -1
        for u in range(1, k):
            if dp[u] >= max_length:
                max_length = dp[u]
                max_index = u
        
        sequence = []
        while max_index != -1:
            sequence.append(boxes[max_index]['index'])
            max_index = prev[max_index]
        
        results.append(str(max_length))
        results.append(" ".join(map(str, reversed(sequence))))
    
    return "\n".join(results)

def main():
    import sys
    lines = []
    print("Enter input (end with an empty line):")
    for line in sys.stdin:
        if line.strip() == "":
            break
        lines.append(line.strip())
    
    output = find_longest_nesting_sequence(lines)
    print(output)

if __name__ == "__main__":
    main()
