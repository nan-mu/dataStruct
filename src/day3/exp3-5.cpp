#include "/usr/include/eigen3/Eigen/Core"
#include <iostream>
#include <iterator>
#include <vector>

using namespace Eigen;
using namespace std;

// org_map保存地图信息和记录格子是否已被走过，path保持到达该点需要的格数，其中起点为0，墙壁0
Array<int, 6, 6> org_map, path;
IOFormat CleanFmt(0, 0, " ", "\n", "|",
                  "|"); //地图输出格式

struct point { //如题
    int x;
    int y;
    point(int _x, int _y) : x(_x), y(_y) {}
};

/// @brief
/// 判断方向是否可走。假如要更换城市距离为极坐标距离，就修改这个函数。几何距离因为有根号二所有还要另写
int find_possible_next_point(point opt, vector<point>& res);

int main() {
    cout << "地图：" << endl;
    org_map << -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, -1, -1, -1, 0, -1, 0, 0, -1,
        -1, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1;
    point start(1, 1), end(4, 4);
    cout << org_map.format(CleanFmt) << endl
         << endl
         << "将输出所有路径，最短路径在最前面，最长路径在最后面。" << endl;

    vector<vector<point>> route = {vector<point>{start}};
    vector<Array<int, 6, 6>> map;
    Array<int, 6, 6> _map = org_map;
    _map(1, 1) = 1;
    map.push_back(_map);
    vector<point> possible_dircetion;
    auto path = route.begin();
    auto path_map = map.begin();
    while (!route.empty()) {
        if (path == route.end()) {
            path = route.begin();
            path_map = map.begin();
        }

        if (path->crbegin()->x == end.x &&
            path->crbegin()->y == end.y) { //到终点，弹出路径并返回
            (*path_map)(1, 1) = 0;
            cout << path_map->format(CleanFmt) << endl << endl;
        }

        possible_dircetion.clear();
        switch (
            find_possible_next_point(*(path->rbegin()), possible_dircetion)) {
        case 0: //走到死胡同了
            path = route.erase(path);
            path_map = map.erase(path_map);
            break;
        case 1: //只有一个方向，那继续走下去
            if ((*path_map)(possible_dircetion[0].x, possible_dircetion[0].y) ==
                0) {
                path->push_back(possible_dircetion[0]);
                (*path_map)(possible_dircetion[0].x, possible_dircetion[0].y) =
                    path->size() - 1;
                path++;
                path_map++;
            } else {
                path = route.erase(path);
                path_map = map.erase(path_map);
            }
            break;
        case 2: //多个方向，开始分叉。为了代码美观浪费了一些性能，写完子路径父路径直接删！
        case 3:
            vector<point> _path(*path);
            Array<int, 6, 6> _map(*path_map);
            //这里是因为vector的迭代器，不是一个真的迭代器，透过运算符重载看去这个迭代器是一个内存指针。
            //然后出问题了，vector更新时没更新迭代器，所有这里要主动保存下标（距离），然后主动更新迭代器。
            auto _distance = distance(route.begin(), path);
            for (auto possible_point : possible_dircetion) {
                //这里的逻辑是，假如可能的点跟路径中的某一端撞上了，那就不写了新路径了
                //并且这里的逻辑是每一个新的点都会到一个新的路径向量中，所以并不需要主动删除
                //这里的条件判断我看着也血压高，语法太奇妙了
                if ((*(map.begin() + _distance))(possible_point.x,
                                                 possible_point.y) == 0) {
                    route.push_back(_path);
                    map.push_back(_map);
                    route.rbegin()->push_back(possible_point);
                    (*map.rbegin())(possible_point.x, possible_point.y) =
                        _path.size();
                }
            }
            vector<point>().swap(_path);
            path = route.erase(route.begin() + _distance);
            path_map = map.erase(map.begin() + _distance);
            break;
        }
    }
}

int find_possible_next_point(point opt, vector<point>& res) {
    bool bool_res[4] = {
        (org_map(opt.x + 1, opt.y) != -1), (org_map(opt.x - 1, opt.y) != -1),
        (org_map(opt.x, opt.y + 1) != -1), (org_map(opt.x, opt.y - 1) != -1)};
    if (bool_res[0])
        res.push_back(point(opt.x + 1, opt.y));
    if (bool_res[1])
        res.push_back(point(opt.x - 1, opt.y));
    if (bool_res[2])
        res.push_back(point(opt.x, opt.y + 1));
    if (bool_res[3])
        res.push_back(point(opt.x, opt.y - 1));
    return bool_res[0] + bool_res[1] + bool_res[2] + bool_res[3];
}