# 標準台灣身分證區域碼對應表
ID_MAP = {
    'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15, 'G': 16, 'H': 17,
    'I': 34, 'J': 18, 'K': 19, 'L': 20, 'M': 21, 'N': 22, 'O': 35, 'P': 23,
    'Q': 24, 'R': 25, 'S': 26, 'T': 27, 'U': 28, 'V': 29, 'W': 32, 'X': 30,
    'Y': 31, 'Z': 33
}

# 每月累積天數 (非閏年)
MONTH_ACC_DAYS = [0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334]

def get_total_minutes(time_str):
    """將時間字串轉換為絕對分鐘數"""
    date_part, time_part = time_str.split()
    y, m, d = map(int, date_part.split('/'))
    hh, mm = map(int, time_part.split(':'))
    
    total_days = y * 365
    total_days += MONTH_ACC_DAYS[m]
    total_days += (d - 1)
    
    total_mins = total_days * 1440 + hh * 60 + mm
    return total_mins

def check_id_validity(id_str):
    """檢查身分證合法性"""
    if len(id_str) != 10:
        if not id_str or not id_str[0].isupper():
            return "wrong area code"
        return "illegal"

    c1 = id_str[0]
    if c1 not in ID_MAP:
        return "wrong area code"
    
    c2 = id_str[1]
    if c2 not in ('1', '2'):
        return "wrong gender code"
    
    try:
        area_num = ID_MAP[c1]
        num_seq_str = str(area_num) + id_str[1:]
        
        if not num_seq_str.isdigit():
            return "illegal"
            
        digits = [int(d) for d in num_seq_str]
        weights = [1, 9, 8, 7, 6, 5, 4, 3, 2, 1]
        
        val_sum = sum(digits[i] * weights[i] for i in range(10))
            
        remainder = val_sum % 10
        check_code = 0 if remainder == 0 else (10 - remainder)
        
        input_check_code = int(id_str[9])
        
        if check_code == input_check_code:
            return "pass"
        else:
            return "illegal"
    except Exception:
        return "illegal"

def calculate_password_strength(pwd):
    """計算密碼強度"""
    score = 0
    count_lower = 0
    count_upper = 0
    count_digit = 0
    count_special = 0
    
    target_specials = set("~!@#$%^&*<>_+= ")
    digits_indices = []
    
    for i, char in enumerate(pwd):
        if 'a' <= char <= 'z':
            count_lower += 1
        elif 'A' <= char <= 'Z':
            count_upper += 1
        elif '0' <= char <= '9':
            count_digit += 1
            digits_indices.append(i)
        elif char in target_specials:
            count_special += 1
            
    score += count_lower
    score += 3 * count_upper
    score += 2 * count_digit
    score += 5 * count_special
    
    if count_digit >= 5:
        is_separated = True
        for k in range(len(digits_indices) - 1):
            if digits_indices[k+1] - digits_indices[k] == 1:
                is_separated = False
                break
        if is_separated:
            score += 15
            
    return score

def main():
    output_buffer = []

    try:
        line = input().strip()
        while not line:
            line = input().strip()
        limit = int(line)
        
        n_str = input().strip()
        while not n_str:
            n_str = input().strip()
        n = int(n_str)
        
        users = {}
        
        for _ in range(n):
            # Step 1: 輸入時間
            curr_time_str = input().strip()
            curr_mins = get_total_minutes(curr_time_str)
            
            # Step 2-4: 帳號驗證
            user_id = ""
            while True:
                user_id = input().strip()
                result = check_id_validity(user_id)
                output_buffer.append(result)
                if result == "pass":
                    break
            
            # Step 5-10: 登入與強度檢查
            is_login_success = False
            is_new_user = False
            current_input_pwd = ""
            
            while not is_login_success:
                # Step 5: 密碼強度
                while True:
                    pwd_input = input().strip()
                    strength = calculate_password_strength(pwd_input)
                    if strength < 30:
                        output_buffer.append("not strong enough")
                    else:
                        output_buffer.append("ok good password")
                        current_input_pwd = pwd_input
                        break
                
                # Step 7: 新舊用戶判斷
                if user_id not in users:
                    # Step 8: 新用戶
                    users[user_id] = {
                        'pwd': current_input_pwd,
                        'history': [current_input_pwd],
                        'time': curr_mins
                    }
                    output_buffer.append("new")
                    is_new_user = True
                    is_login_success = True
                    break 
                else:
                    # Step 9: 舊用戶
                    stored_data = users[user_id]
                    if current_input_pwd == stored_data['pwd']:
                        # Step 10: 正確
                        output_buffer.append("correct")
                        is_login_success = True
                        break 
                    else:
                        output_buffer.append("wrong")
                        continue
            
            # 如果是新用戶，結束這筆操作
            if is_new_user:
                continue

            # Step 11: 檢查時間差距
            last_change_time = users[user_id]['time']
            diff = curr_mins - last_change_time
            
            # Step 12: 時間未到
            if diff < limit:
                output_buffer.append("no need to change")
                continue 
            
            # Step 13: 需要變更
            output_buffer.append("need to change")
            
            # Step 14-20: 變更密碼
            while True:
                new_pwd = input().strip()
                
                # Step 15 & 16
                strength = calculate_password_strength(new_pwd)
                if strength < 30:
                    output_buffer.append("not strong enough")
                    continue
                
                # Step 17
                output_buffer.append("ok good password")
                
                # Step 18
                if new_pwd in users[user_id]['history']:
                    output_buffer.append("same password")
                    continue
                
                # Step 20
                output_buffer.append("password changed")
                
                users[user_id]['pwd'] = new_pwd
                users[user_id]['time'] = curr_mins
                users[user_id]['history'].append(new_pwd)
                
                if len(users[user_id]['history']) > 3:
                    users[user_id]['history'].pop(0)
                
                break

    except (EOFError, ValueError):
        pass
    
    for line in output_buffer:
        print(line)

if __name__ == "__main__":
    main()