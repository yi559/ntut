from collections import deque

def bfs_path(graph, start, end):
    """
    使用 BFS 尋找從 start 到 end 的最短路徑。
    回傳值: 成功回傳 list [start, ..., end]，失敗回傳 None
    """
    if start == end:
        return [start]
    
    # Queue 存放目前的完整路徑
    queue = deque([ [start] ])
    visited = {start}
    
    while queue:
        path = queue.popleft()
        current_node = path[-1] # 路徑最後一個點是目前所在位置
        
        if current_node == end:
            return path
        
        # 找鄰居
        for neighbor in graph.get(current_node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                # 產生新路徑並加入佇列
                new_path = list(path)
                new_path.append(neighbor)
                queue.append(new_path)
                
    return None

def main():
    try:
        # 1. 讀取第一行：路徑數 N, 起點 X, 終點 Z
        line1 = input().split()
        if not line1: return
        N = int(line1[0])
        X = int(line1[1])
        Z = int(line1[2])

        # 2. 讀取第二行：休息點列表
        line2 = input().split()
        rest_stops = [int(x) for x in line2]
        # 題目要求：若路徑長度相同，輸出編號最小的休息站
        # 所以我們先將休息站由小到大排序，這樣後續只要遇到「更短」的才更新，
        # 遇到「一樣長」的就跳過（保留原本比較小的那個）
        rest_stops.sort()

        # 3. 讀取接下來的 N 行建立地圖 (Graph)
        graph = {}
        edges_read = 0
        while edges_read < N:
            try:
                line = input().strip()
                if not line: continue # 跳過空行
                
                parts = line.split()
                u = int(parts[0])
                v = int(parts[1])
                
                # 無向圖，雙向連接
                if u not in graph: graph[u] = []
                if v not in graph: graph[v] = []
                graph[u].append(v)
                graph[v].append(u)
                
                edges_read += 1
            except EOFError:
                break

        # 4. 開始計算每個休息點的路徑
        best_path = None
        best_rest_stop = -1
        min_length = float('inf')

        found = False

        for k in rest_stops:
            # 第一段：起點 -> 休息點
            path1 = bfs_path(graph, X, k)
            if path1 is None: continue # 路不通，換下一個休息點

            # 第二段：休息點 -> 終點
            path2 = bfs_path(graph, k, Z)
            if path2 is None: continue # 路不通，換下一個休息點
            
            # 算出總路徑 (path1 + path2)
            # 注意：path1 結尾是 k，path2 開頭也是 k，合併時 k 會重複，所以 path2 從索引 1 開始取
            full_path = path1 + path2[1:]
            total_len = len(full_path)

            # 判斷是否為更短的路徑
            # 因為 rest_stops 已經從小排到大，這裡只要 < min_length 即可
            # 如果 == min_length，我們不更新，這樣自然保留了編號較小的 k
            if total_len < min_length:
                min_length = total_len
                best_rest_stop = k
                best_path = full_path
                found = True

        # 5. 輸出結果
        if not found:
            print("NO")
        else:
            print(best_rest_stop)
            # 將路徑列表 [1, 4, 3] 轉成字串 "1 4 3"
            print(" ".join(map(str, best_path)))

    except EOFError:
        pass

if __name__ == "__main__":
    main()