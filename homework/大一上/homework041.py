import math

# --- 這裡是不使用 sys 的輸入處理邏輯 ---
# 建立一個緩衝區來存放切分好的字串
token_buffer = []

def get_next_token():
    """
    每次呼叫這個函式，就會回傳下一個有效的字串(token)。
    如果緩衝區空了，就用 input() 讀下一行並補滿緩衝區。
    """
    global token_buffer
    
    # 當緩衝區沒東西時，嘗試讀取下一行
    while not token_buffer:
        try:
            line = input()
            # 將讀到的那一行切分並加入緩衝區
            # split() 會自動過濾掉空格與換行
            token_buffer.extend(line.split())
        except EOFError:
            # 如果沒有資料了 (End Of File)，回傳 None
            return None
            
    # 從緩衝區拿第一個出來回傳
    return token_buffer.pop(0)

# -------------------------------------

def main():
    # 1. 讀取總課程數 M
    m_str = get_next_token()
    if m_str is None:
        return
    M = int(m_str)

    # 資料結構
    # student_records: { (Dept, EntYear, AcadYear): [StudentObj, ...] }
    student_records = {} 
    
    # course_stats: { (CourseCode, AcadYear): {'grades': [], 'withdraw': 0, 'total': 0} }
    course_stats = {}

    # 2. 迴圈讀取每一門課
    for _ in range(M):
        course_code_full = get_next_token()
        sem_code = get_next_token()
        n_str = get_next_token()
        
        # 如果讀不到資料就中斷
        if course_code_full is None: break
            
        n = int(n_str)
        subject_code = course_code_full[:3] # 前三碼科目代號
        
        # 取得學分 (第四碼)
        try:
            credits = int(course_code_full[3])
        except:
            credits = 0

        acad_year = int(sem_code[:3])
        
        # 初始化課程統計
        ckey = (course_code_full, acad_year)
        if ckey not in course_stats:
            course_stats[ckey] = {'grades': [], 'withdraw': 0, 'total': 0}
        
        course_stats[ckey]['total'] += n

        # 3. 讀取該門課的 N 位學生
        for _ in range(n):
            sid = get_next_token()
            score_str = get_next_token()
            
            ent_year = int(sid[:3])
            dept = int(sid[3:6])
            
            # 初始化學生資料結構
            if sid not in student_records:
                student_records[sid] = {}
            
            if acad_year not in student_records[sid]:
                student_records[sid][acad_year] = {
                    'weighted_sum': 0,
                    'credits': 0,
                    'total_courses': 0,
                    'withdraw_courses': 0,
                    'dept': dept,
                    'ent_year': ent_year
                }
            
            st_data = student_records[sid][acad_year]
            st_data['total_courses'] += 1
            
            # 處理成績邏輯
            if score_str == 'w':
                # 退選：計入退選數，不讀取後續成績
                st_data['withdraw_courses'] += 1
                course_stats[ckey]['withdraw'] += 1
            else:
                sem_score = int(score_str)
                final_score = sem_score
                
                # 特殊科目規則：如果是 101 或 201 且「沒有退選」，才有會考成績
                if subject_code == '101' or subject_code == '201':
                    exam_str = get_next_token()
                    exam_score = int(exam_str)
                    # 成績計算公式
                    final_score = math.ceil(sem_score * 0.7 + exam_score * 0.3)
                
                # 累加分數
                st_data['weighted_sum'] += final_score * credits
                st_data['credits'] += credits
                
                # 記錄到課程統計
                course_stats[ckey]['grades'].append(final_score)

    # 4. 輸出第一部分：學生排名
    # 找出所有 (系號, 入學年, 學年) 的組合
    groups = set()
    for sid, years in student_records.items():
        for y, data in years.items():
            groups.add((data['dept'], data['ent_year'], y))
    
    sorted_groups = sorted(list(groups))
    
    for dept, ent, acad in sorted_groups:
        print(f"{dept} {ent} {acad}")
        
        # 收集該群組學生
        group_students = []
        for sid, years in student_records.items():
            if acad in years:
                d = years[acad]
                if d['dept'] == dept and d['ent_year'] == ent:
                    avg = 0
                    if d['credits'] > 0:
                        # 平均分數無條件捨去
                        avg = math.floor(d['weighted_sum'] / d['credits'])
                    
                    drop_pct = 0
                    if d['total_courses'] > 0:
                        drop_pct = math.floor((d['withdraw_courses'] / d['total_courses']) * 100)
                        
                    group_students.append({
                        'id': sid,
                        'avg': avg,
                        'drop_pct': drop_pct
                    })
        
        # 排序與計算排名
        N = len(group_students)
        # 1. 先排學號 (小到大)
        group_students.sort(key=lambda x: x['id'])
        # 2. 再排平均 (大到小) - Python 的 sort 是穩定的，所以同分會保持學號順序
        group_students.sort(key=lambda x: x['avg'], reverse=True)
        
        ranked_fail_students = []
        for rank_idx, st in enumerate(group_students):
            rank = rank_idx + 1
            
            # 計算排名百分比 (依題目特殊公式)
            pct = 100
            for p in range(1, 101):
                if math.ceil(N * p / 100) >= rank:
                    pct = p
                    break
            
            st['rank_pct'] = pct
            
            # 篩選不及格者
            if st['avg'] < 60:
                ranked_fail_students.append(st)
        
        # 輸出結果
        if len(ranked_fail_students) < 3:
            print("Not Enough Student")
        else:
            for st in ranked_fail_students[:3]:
                print(f"{st['id']} {st['avg']} {st['rank_pct']}% {st['drop_pct']}%")

    # 5. 輸出第二部分：課程統計
    sorted_courses = sorted(course_stats.keys())
    
    for code, year in sorted_courses:
        print(f"{code} {year}")
        stats = course_stats[(code, year)]
        grades = stats['grades']
        
        drop_rate = 0
        if stats['total'] > 0:
            drop_rate = math.floor((stats['withdraw'] / stats['total']) * 100)

        if not grades:
            # 全都退選的情況
            print(f"0 0 0 {drop_rate}% 0")
        else:
            max_g = max(grades)
            min_g = min(grades)
            avg_g = math.floor(sum(grades) / len(grades))
            pass_count = sum(1 for g in grades if g > 40) # 題目定義 >40 及格
            
            print(f"{max_g} {avg_g} {min_g} {drop_rate}% {pass_count}")
main()