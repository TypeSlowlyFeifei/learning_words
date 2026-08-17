#include "lw_file/page.h"
#include "lw_file/words_map.h"
#include "scoreboard.h"
#include "word_checker.h"
#include <memory>
#include <sstream>
#include <random>
#include <iomanip>

<<<<<<< HEAD
#ifndef _WIN32 
#include <climits>
#endif

using namespace std;

inline const string score_file_name = "learning_words_score.txt";
inline const string return_keyword = "__return__";
=======
using namespace std;

const inline string score_file_name = "learning_words_score.txt";
const inline string return_keyword = "__return__";
>>>>>>> 669e4130e9b3ae9c32b3755f82acc7028d729fa2

void practice_basic(const words_map& in_words_map, const unsigned long long& in_max_count)
{
    random_device rd; // 随机设备
    mt19937 gen(rd()); // 梅森旋转算法
    uniform_int_distribution<size_t> dis(0, in_words_map.get_map()->size() - 1); // 均匀分布

    scoreboard board; // 计分板

<<<<<<< HEAD
    for (unsigned long long i = 0; i < (in_max_count == 0 ? UINT64_MAX : in_max_count); i++)
=======
    for (unsigned long long i = 0; i < (in_max_count == 0 ? __UINT64_MAX__ : in_max_count); i++)
>>>>>>> 669e4130e9b3ae9c32b3755f82acc7028d729fa2
    {
        long long randomIndex = dis(gen); // 随机索引
        auto it = in_words_map.get_map()->begin();

        // 随机选择一个位置s
        advance(it, randomIndex);

        // 首页
        auto p_page_q = make_unique<page>("释义: " + it->second, "练习", "请拼写", true);

        // 输入
        auto temp = p_page_q->get_input();
        if (temp == return_keyword)
        {
            // 退出本次练习
            break;
        }

        p_page_q.reset(); // 首页析构

        // 检查器
        auto p_checker = make_unique<word_checker>(it->first, temp);
        
        if (p_checker->check() != -1)
        {
            stringstream line1;
            line1 << "拼错了哦！正确答案是: " << it->first;
            stringstream line2;
            line2 << "从第" << p_checker->check() + 1 << "个字符开始错误";

            // 提示页
            auto p_page_i = make_unique<page>(vector<string>{line1.str(), line2.str()}, "练习", "", true);

            // 错误
            board.add(false);
        }
        else
        {
            // 正确
            board.add(true);
        }
    }

    if (board.get_rate() == "NaN")
    {
        return; // 无练习记录时，不生成成绩单
    }

    auto line1 = ostringstream() << "本次共练习拼写单词" << board.get_num() << "个";
    auto line2 = ostringstream() << "拼写正确" << board.get_right_num() << "个";
    auto line3 = ostringstream() << "正确率" << board.get_rate();
    
    ofstream score_file(score_file_name);
    if (!score_file.is_open()) // 创建文件失败
    {
        auto p_page_score_err = make_unique<page>(
            vector<string>{"无法保存成绩单，在此显示简略信息", line3.str()}, "成绩单", page::default_question, true
        );
<<<<<<< HEAD
=======
        p_page_score_err->console_print();
>>>>>>> 669e4130e9b3ae9c32b3755f82acc7028d729fa2
    }
    else
    {
        auto p_page_score = make_unique<page>(
            vector<string>{line1.str(), line2.str(), line3.str()},
            "成绩单",
            "",
            false
        );
        p_page_score->file_print(&score_file);

<<<<<<< HEAD
        auto p_page_score_i = make_unique<page>("本次练习的成绩单已打印到文件" + score_file_name, "练习", page::default_question, true);
=======
        auto p_page_score_i = make_unique<page>("本次练习的成绩单已打印到文件" + score_file_name, "练习", page::default_question);
        p_page_score_i->console_print();
>>>>>>> 669e4130e9b3ae9c32b3755f82acc7028d729fa2
    }
}

// 文件检查，打开成功就加载图，否则不作修改
inline bool check_dict_file(unique_ptr<words_map>& p_in_words_map, string file_name)
{
    try
    {
        // 尝试打开并加载词典
        p_in_words_map = make_unique<words_map>(file_name);

        return true;
    }
    catch (const runtime_error& e)
    {
        // 错误页
<<<<<<< HEAD
        auto p_page_err = make_unique<page>(e.what(), "错误", page::default_question, true);
=======
        auto p_page_err = make_unique<page>(e.what(), "错误", page::default_question);
        p_page_err->console_print();
>>>>>>> 669e4130e9b3ae9c32b3755f82acc7028d729fa2

        return false;
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1 || argc > 3)
    {
        // 无主函数参数运行
        while (true)
        {
            unique_ptr<words_map> p_words_map;

            while (true) // 文件打不开时重复询问
            {
                ostringstream line3;
                line3 << "输入" << return_keyword << "即可返回上一个页面";

                // 首页
                auto p_page_q = make_unique<page>(
                    vector<string>{
                        "程序启动后，从逗号分隔值文件（*.csv）加载词典",
                        "您也可以在命令行直接指定要加载的词典（不带扩展名）",
                        "在词典名后输入数字可以指定练习次数，默认为无限次练习",
                        line3.str()
                    },
#ifdef _WIN32
                    "狒狒 单词/短语拼拼乐 Windows版",
#else
                    "狒狒 单词/短语拼拼乐 Linux和其他系统版",
#endif
                    "请键入文件名（不带扩展名）",
                    true
                );

                // 输入
                auto temp = p_page_q->get_input();
                if (temp == return_keyword)
                {
                    return 0;
                }

                if (check_dict_file(p_words_map, temp))
                {
                    // 打开成功退出循环，开始练习
                    break;
                }
            }

            // 练习页面
            practice_basic(*p_words_map, 0);
        }
    }
    else if (argc == 2)
    {
        unique_ptr<words_map> p_words_map;

        if (check_dict_file(p_words_map, argv[1]))
        {
            // 练习页面
            practice_basic(*p_words_map, 0);

            return 0;
        }

        return -1;
    }
    else 
    {
        unsigned long long max_count;

        try
        {
            max_count = stoull(argv[2]);

            if (max_count == 0)
            {
                throw runtime_error("");
            }
        }
        catch (...)
        {
            // 错误页
<<<<<<< HEAD
            auto p_page_err = make_unique<page>("无效的启动参数", "错误", "", true);
=======
            auto p_page_err = make_unique<page>("无效的启动参数", "错误", "");
            p_page_err->console_print();
>>>>>>> 669e4130e9b3ae9c32b3755f82acc7028d729fa2

            return -1;
        }

        unique_ptr<words_map> p_words_map;

        if (check_dict_file(p_words_map, argv[1]))
        {
            // 练习页面
            practice_basic(*p_words_map, max_count);

            return 0;
        }

        return -1;
    }
}
