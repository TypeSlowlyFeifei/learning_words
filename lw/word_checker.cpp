#include "word_checker.h"
#include <algorithm>

using namespace std;

word_checker::word_checker(const string& in_target, const string& in_source)
    : target(in_target), source(in_source)
{ }

long long word_checker::check() const
{
    // 取最小长度
    long long string_size = min(target.size(), source.size());

    if (string_size == 0)
    {
        // 未作答
        return 0;
    }

    for (long long i = 0; i < string_size; i++)
    {
        if (target[i] != source[i])
        {
            // 字符不一
            return i;
        }
    }

    // 拼写正确
    return -1;
}
