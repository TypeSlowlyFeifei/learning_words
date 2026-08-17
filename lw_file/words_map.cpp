#include "words_map.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

words_map::words_map() : p_my_map(nullptr)
{ }

words_map::words_map(const string& file_name) : p_my_map(nullptr)
{
    load(file_name);
}

bool words_map::load(const string& file_name)
{
    if (p_my_map)
    {
        // 必须先置空原来的图
        return false;
    }

    ifstream file(file_name + ".csv");
    if (!file.is_open())
    {
        // 抛出异常
        throw runtime_error("打不开文件");
    }

    // 创建新对象
    p_my_map = make_unique<unordered_map<string, string>>();

    string line;
    while (getline(file, line))
    {
        // 创建键值对
        create_pair(line);
    }
    
    file.close();

    return true;
}

bool words_map::unload() noexcept
{
    if (p_my_map)
    {
        p_my_map.reset(); // 图析构

        return true;
    }

    return false;
}

void words_map::create_pair(string line)
{
    stringstream* p_line_stream = new stringstream(line);
    string token;
    vector<string> tokens;

    // 分割后添加进容器
    while (getline(*p_line_stream, token, ','))
    {
        tokens.push_back(token);
    }

    // 删除串流
    delete p_line_stream;
    p_line_stream = nullptr;

    // 清理
    auto clear_token = [](string& text)
    {
        for (int i = 0; i < text.size(); i++)
        {
            // 去除无需拼写的音标
            if (text[i] == '[' || text[i] == '/' || text[i] == '(' || text[i] == '?')
            {
                text.erase(text.begin() + i, text.end());
                return;
            }
        }

        // 去除开头空白
        auto start = find_if_not(text.begin(), text.end(), [](char s) { return s == ' '; });
        text.erase(text.begin(), start);

        // 去除结尾空白
        auto end = find_if_not(text.rbegin(), text.rend(), [](char s) { return s == ' '; }).base();
        text.erase(end, text.end());
    };

    // 必须有两个串
    if (tokens.size() == 2)
    {
        // 有一个是空串，即判定该条无效
        if (tokens[0] == "" || tokens[1] == "")
        {
            return;
        }

        // 清理每个串
        clear_token(tokens[0]);
        clear_token(tokens[1]);

        // 创建键值对
        (*p_my_map)[tokens[0]] = tokens[1];
    }
}

const unordered_map<string, string>* words_map::get_map() const
{
    return p_my_map.get();
}
