#pragma once

#include <string>

class scoreboard
{
public:
    // 总练习数
    long long num;

    // 正确数
    long long right_num;

public:
    // 默认构造
    scoreboard();

public:
    // 计分
    void add(bool);

    // 获取总练习数
    long long get_num() const noexcept;

    // 获取正确数
    long long get_right_num() const noexcept;

    // 获取正确率百分比
    std::string get_rate();
};
