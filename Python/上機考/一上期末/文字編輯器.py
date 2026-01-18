def main():
    try:
        # 讀取 M (行數) 和 N (指令數)
        first_line = input().strip().split()
        
        M = int(first_line[0])
        N = int(first_line[1])

        # 讀取原始文章
        content = []
        for _ in range(M):
            # 將每一行讀入並切割成單字列表
            line_words = input().strip().split()
            content.append(line_words)

        # 處理 N 個指令
        for _ in range(N):
            command_line = input().strip().split()
            cmd = command_line[0]

            if cmd == 'awf':
                # awf i n word: 第 i 行, 第 n 個字前面加上 word
                i = int(command_line[1]) - 1
                n = int(command_line[2]) - 1
                word = command_line[3]
                content[i].insert(n, word)

            elif cmd == 'awa':
                # awa i n word: 第 i 行, 第 n 個字後面加上 word
                i = int(command_line[1]) - 1
                n = int(command_line[2]) # insert at n (原本的第 n 個字之後)
                word = command_line[3]
                content[i].insert(n, word)

            elif cmd == 'asf':
                # asf i sentence: 在第 i 行"內容的前面"加入 sentence
                i = int(command_line[1]) - 1
                sentence_words = command_line[2:]
                content[i] = sentence_words + content[i] # 將新句子接在原行列表的最前面

            elif cmd == 'asa':
                # asa i sentence: 在第 i 行"內容的後面"加入 sentence
                i = int(command_line[1]) - 1
                sentence_words = command_line[2:]
                content[i] = content[i] + sentence_words # 將新句子接在原行列表的最後面

            elif cmd == 'if':
                # if key word: 在文章中所有 key 前面加上 word
                key = command_line[1]
                word = command_line[2]
                
                for idx, row in enumerate(content):
                    new_row = []
                    for token in row:
                        if token == key:
                            new_row.append(word)
                        new_row.append(token)
                    content[idx] = new_row

            elif cmd == 'ia':
                # ia key word: 在文章中所有 key 的後面加上 word
                key = command_line[1]
                word = command_line[2]
                
                for idx, row in enumerate(content):
                    new_row = []
                    for token in row:
                        new_row.append(token)
                        if token == key:
                            new_row.append(word)
                    content[idx] = new_row

            elif cmd == 'dw':
                # dw i n: 刪除第 i 行中, 第 n 個字
                i = int(command_line[1]) - 1
                n = int(command_line[2]) - 1
                content[i].pop(n)

            elif cmd == 'dl':
                # dl i: 刪除第 i 行
                i = int(command_line[1]) - 1
                content.pop(i)

            elif cmd == 'rp':
                # rp old new: 將文章中所有 old 替換為 new
                old_word = command_line[1]
                new_word = command_line[2]
                for row in content:
                    for idx, token in enumerate(row):
                        if token == old_word:
                            row[idx] = new_word

            elif cmd == 'c':
                # c: 目前文章總計字數
                total_words = sum(len(row) for row in content)
                print(total_words)

        # 輸出編輯完成之文章
        for row in content:
            print(" ".join(row))

    except Exception:
        pass

if __name__ == "__main__":
    main()