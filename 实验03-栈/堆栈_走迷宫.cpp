#include <stack>
#include <iostream>
// #include<vector>
using namespace std;

class position
{
public:
    int x_is = 0;
    int y_is = 0;
    bool up_moving = 1;
    bool down_moving = 1;
    bool left_moving = 1;
    bool right_moving = 1;

    position(int x_is, int y_is, int **maze, int n);
    ~position();
    bool move(stack<position> *path, position *now, int n, int **maze);
    bool movable();
};

bool position::movable()
{
    if (up_moving || down_moving || left_moving || right_moving)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 调用move前push(this),，之后调用move，调用之后pop(this)
bool position::move(stack<position> *path, position *now, int n, int **maze)
{
    if (this->x_is == n - 1 && this->y_is == n - 1)
    {
        // 成功，加上this
        path->push(*now);
        return 1;
    }

    // 没有判断点在栈中是否存在，导致一直重复兜圈，所以要动态修改maze，把走过的路变成1
    // push伴随着1,pop伴随着0
    // 为了不绕远路，优先走右上，果然过了..
    while (this->movable())
    {
        if (this->up_moving)
        {
            position next_position = position(this->x_is, this->y_is + 1, maze, n);

            // 先false再push
            // 从下往上走，上面不能down_moving了
            this->up_moving = false;
            next_position.down_moving = false;

            path->push(*now);
            maze[x_is][y_is] = 1;

            bool success = next_position.move(path, &next_position, n, maze);
            if (success)
            {
                return 1;
            }
            else
            {
                path->pop();
                maze[x_is][y_is] = 0;
            }
        }
        else if (this->right_moving)
        {

            position next_position = position(this->x_is + 1, this->y_is, maze, n);
            this->right_moving = false;
            next_position.left_moving = false;

            maze[x_is][y_is] = 1;
            path->push(*now);
            bool success = next_position.move(path, &next_position, n, maze);
            if (success)
            {
                return 1;
            }
            else
            {
                maze[x_is][y_is] = 0;
                path->pop();
            }
        }
        else if (this->down_moving)
        {

            position next_position = position(this->x_is, this->y_is - 1, maze, n);
            this->down_moving = false;
            next_position.up_moving = false;

            maze[x_is][y_is] = 1;
            path->push(*now);

            bool success = next_position.move(path, &next_position, n, maze);
            if (success)
            {
                return 1;
            }
            else
            {
                maze[x_is][y_is] = 0;
                path->pop();
            }
        }
        else if (this->left_moving)
        {

            position next_position = position(this->x_is - 1, this->y_is, maze, n);
            this->left_moving = false;
            next_position.right_moving = false;

            maze[x_is][y_is] = 1;
            path->push(*now);
            bool success = next_position.move(path, &next_position, n, maze);
            if (success)
            {
                return 1;
            }
            else
            {
                maze[x_is][y_is] = 0;
                path->pop();
            }
        }
    }
    return 0;
}

position::position(int x_is, int y_is, int **maze, int n)
{
    this->x_is = x_is;
    this->y_is = y_is;
    if (x_is == 0 || maze[x_is - 1][y_is] == 1)
    {
        left_moving = false;
    }
    if (x_is == n - 1 || maze[x_is + 1][y_is] == 1)
    {
        right_moving = false;
    }
    if (y_is == 0 || maze[x_is][y_is - 1] == 1)
    {
        down_moving = false;
    }
    if (y_is == n - 1 || maze[x_is][y_is + 1] == 1)
    {
        up_moving = false;
    }
}

position::~position()
{
}

int main()
{
    stack<position> path;
    // position first_position = position(0, 0, 0, )

    int try_times = 0;
    scanf("%d", &try_times);

    // 迷宫样本数
    for (int j = 0; j < try_times; j++)
    {
        int n;

        //nxn迷宫
        scanf("%d", &n);

        // 定义二维数组
        int **maze = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++)
        {
            maze[i] = (int *)malloc(n * sizeof(int));
        }

        // 赋值
        for (int i1 = 0; i1 < n; i1++)
        {
            for (int i2 = 0; i2 < n; i2++)
            {
                //scanf_s("%d", &maze[i1][i2]);
                // cout << maze[i1][i2] << flush;
                cin >> maze[i1][i2];
            }
        }

        position first_position = position(0, 0, maze, n);
        int success = first_position.move(&path, &first_position, n, maze);

        if (success)
        {
            // 反向存储
            stack<position> path1;
            while (!path.empty())
            {
                path1.push(path.top());
                path.pop();
            }

            int i = 0;
            while (!path1.empty())
            {
                position cpos = path1.top();
                if ((++i) % 4 == 0)
                    cout << '[' << cpos.x_is << ',' << cpos.y_is << ']' << "--" << endl;
                else
                    cout << '[' << cpos.x_is << ',' << cpos.y_is << ']' << "--";

                path1.pop();
            }
            cout << "END" << endl;
        }
        else
        {
            cout << "no path" << endl;
        }
    }
    return 1;
}