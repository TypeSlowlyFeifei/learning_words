#pragma once

#include <string>

class word_checker final
{
private:
    // 目标串，正确答案
    std::string target;

    // 源串，输入
    std::string source;

public:
    // 传参构造
    word_checker(const std::string&, const std::string&);

public:
    /**
     * 检查拼写
     * 若有错误，返回字符索引
     * 若正确，返回-1
     */
    long long check() const;
};
