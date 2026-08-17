#include "page.h"
#include <iostream>

using namespace std;

page::page(const string& in_text, const string& in_title, const string& in_question, bool print)
    : input_buffer(""), title(in_title), question(in_question)
{
    texts.push_back(in_text);

    if (print)
    {
        console_print();
    }
}

page::page(const vector<string>& in_texts, const string& in_title, const string& in_question, bool print)
    : input_buffer(""), texts(in_texts), title(in_title), question(in_question)
{ 
    if (print)
    {
        console_print();
    }
}

void page::console_print()
{
    // 输出格式
    cout << "###" << ' ';

    if (title == "")
    {
        cout << "新页面"; // 默认标题
    }
    else
    {
        cout << title;
    }

    // 输出格式
    cout << ' ' << "###" << endl;

    for (string line : texts)
    {
        cout << line << endl;
    }

    // 有问题时才询问，否则为普通页面
    if (question != "")
    {
        cout << question << " >> ";
        
        getline(cin, input_buffer);
    }

    cout << endl;
}

void page::file_print(ofstream* p_file)
{
    if (question != "")
    {
        throw runtime_error("不能向文件中打印提问页面");
    }

    // 输出格式
    *p_file << "###" << ' ';

    if (title == "")
    {
        *p_file << "新页面"; // 默认标题
    }
    else
    {
        *p_file << title;
    }

    // 输出格式
    *p_file << ' ' << "###" << endl;

    for (string line : texts)
    {
        *p_file << line << endl;
    }

    cout << endl;
}

string page::get_input()
{
    return input_buffer;
}
