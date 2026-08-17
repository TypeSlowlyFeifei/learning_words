#include "scoreboard.h"
#include <iomanip>
#include <sstream>

using namespace std;

scoreboard::scoreboard() : num(0), right_num(0)
{ }

void scoreboard::add(bool is_right)
{
    num++;
    if (is_right)
    {
        right_num++;
    }
}

long long scoreboard::get_num() const noexcept
{
    return num;
}

long long scoreboard::get_right_num() const noexcept
{
    return right_num;
}

string scoreboard::get_rate()
{
    if (num == 0)
    {
        return "NaN";
    }

    ostringstream ss;
    ss << static_cast<long double>(right_num) / static_cast<long double>(num) * 100.f << "%";

    return ss.str();
}
