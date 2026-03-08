#include <gtest/gtest.h>

extern "C" {
    #include "homework008.h"
}

// 測試：純數字判斷
TEST(Homework008Test, PureDigitsTest) {
    EXPECT_EQ(is_pure_digits((char*)"", 1), 0);          // 空字串
    EXPECT_EQ(is_pure_digits((char*)"12a", 1), 0);       // 包含非數字
    EXPECT_EQ(is_pure_digits((char*)"01", 1), 0);        // 複數長度但以 0 開頭
    EXPECT_EQ(is_pure_digits((char*)"0", 0), 0);         // 是 0 但不允許 0
    EXPECT_EQ(is_pure_digits((char*)"0", 1), 1);         // 是 0 且允許 0
    EXPECT_EQ(is_pure_digits((char*)"123", 1), 1);       // 正常數字
}

// 測試：整數判斷
TEST(Homework008Test, IntegerTest) {
    EXPECT_EQ(is_integer((char*)""), 0);                 // 長度 < 1
    char long_str[60] = "123456789012345678901234567890123456789012345678901";
    EXPECT_EQ(is_integer(long_str), 0);                  // 長度 > 50
    EXPECT_EQ(is_integer((char*)"-"), 0);                // 只有負號
    EXPECT_EQ(is_integer((char*)"0"), 1);                // 零
    EXPECT_EQ(is_integer((char*)"-0"), 1);               // 負零
    EXPECT_EQ(is_integer((char*)"123"), 1);              // 正整數
    EXPECT_EQ(is_integer((char*)"-45"), 1);              // 負整數
    EXPECT_EQ(is_integer((char*)"012"), 0);              // 開頭為零的無效整數
}

// 測試：變數名稱判斷
TEST(Homework008Test, VariableTest) {
    EXPECT_EQ(is_variable((char*)""), 0);                // 空字串
    EXPECT_EQ(is_variable((char*)"thisisverylong"), 0);  // 長度 > 10
    EXPECT_EQ(is_variable((char*)"1var"), 0);            // 數字開頭
    EXPECT_EQ(is_variable((char*)"-var"), 0);            // 符號開頭
    EXPECT_EQ(is_variable((char*)"var-1"), 0);           // 包含無效符號
    EXPECT_EQ(is_variable((char*)"_var1"), 1);           // 底線開頭合法
    EXPECT_EQ(is_variable((char*)"x"), 1);               // 單一字母合法
}

// 測試：浮點數判斷
TEST(Homework008Test, FloatTest) {
    EXPECT_EQ(is_float((char*)"1"), 0);                  // 長度 < 3
    char long_str[60] = "1.23456789012345678901234567890123456789012345678901";
    EXPECT_EQ(is_float(long_str), 0);                    // 長度 > 50
    EXPECT_EQ(is_float((char*)".5"), 0);                 // 小數點開頭
    EXPECT_EQ(is_float((char*)"-.5"), 0);                // 負號接小數點
    EXPECT_EQ(is_float((char*)"1."), 0);                 // 小數點結尾
    EXPECT_EQ(is_float((char*)"1.2.3"), 0);              // 多個小數點
    EXPECT_EQ(is_float((char*)"01.5"), 0);               // 整數部分開頭為 0
    EXPECT_EQ(is_float((char*)"1a.5"), 0);               // 整數部分有字母
    EXPECT_EQ(is_float((char*)"1.5a"), 0);               // 小數部分有字母
    EXPECT_EQ(is_float((char*)"0.5"), 1);                // 合法浮點數
    EXPECT_EQ(is_float((char*)"-1.23"), 1);              // 合法負浮點數
    EXPECT_EQ(is_float((char*)"123.45"), 1);             // 合法浮點數
}

// 測試：分數判斷 (帶分數、真分數、假分數)
TEST(Homework008Test, FractionTest) {
    // 帶分數測試
    EXPECT_STREQ(check_fractions((char*)"1 1/2"), "mixed fraction");
    EXPECT_EQ(check_fractions((char*)"1 2/2"), nullptr); // 分子沒有小於分母
    EXPECT_EQ(check_fractions((char*)"a 1/2"), nullptr); // 前面不是整數
    EXPECT_EQ(check_fractions((char*)"1 1//2"), nullptr);// 多個斜線
    EXPECT_EQ(check_fractions((char*)"1 1"), nullptr);   // 後面沒有斜線

    // 普通分數測試
    EXPECT_STREQ(check_fractions((char*)"1/2"), "proper fraction");
    EXPECT_STREQ(check_fractions((char*)"-1/2"), "proper fraction");
    EXPECT_STREQ(check_fractions((char*)"3/2"), "improper fraction");
    EXPECT_STREQ(check_fractions((char*)"2/2"), "improper fraction");
    
    // 邊界與錯誤測試
    EXPECT_EQ(check_fractions((char*)"thisistoolong"), nullptr); // 長度 > 10
    EXPECT_EQ(check_fractions((char*)"/2"), nullptr);    // 只有分母
    EXPECT_EQ(check_fractions((char*)"1/"), nullptr);    // 只有分子
    EXPECT_EQ(check_fractions((char*)"abc"), nullptr);   // 什麼都不是
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}