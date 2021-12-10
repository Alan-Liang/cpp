//可以自己定义一些全局变量、引用头文件
#include <iostream>

class BasicException {
protected:
    //可以自己定义所需要的成员
    const char *message;

public:
    explicit BasicException(const char *_message) {
        //用错误信息初始化
    }

    virtual const char *what() const {
        //return: 错误信息字符串
        return message;
    }
};

class ArgumentException: public BasicException {
};

class IteratorException: public BasicException {
};

struct Pokemon {
    //设计你自己的宝可梦类！
    //唯一要求：一定要有名为name id的两个public成员变量，评测时需要用到
    char name[12];
    int id;
    //...
};

class Pokedex {
private:
    //可以自己定义需要的成员

public:
    explicit Pokedex(const char *_fileName) {
        //TO DO: 构造函数，从名为_fileName的文件中读取数据（没有则创建）
    }

    ~Pokedex() {
        //TO DO: 析构函数
    }

    bool pokeAdd(const char *name, int id, const char *types) {
        //TO DO: 添加宝可梦
        //返回是否添加成功
    }

    bool pokeDel(int id) {
        //TO DO: 删除对应宝可梦
        //return: 返回是否删除成功
    }

    std::string pokeFind(int id) const {
        //TO DO: 查询id对应的宝可梦
        //return: 如果找到，返回宝可梦的name。否则返回字符串 "None"
    }

    std::string typeFind(const char *types) const {
        //TO DO: 查询属性包含了types中的属性的宝可梦
        //return: 如果找到，返回多行字符串。第一行为满足的宝可梦数量，
        //          接下来每一行为宝可梦的name，按id从小到大。
        //        如果找不到，返回字符串 "None"
        //注意，types可能为多种属性，同样用 # 号分隔
    }

    float attack(const char *type, int id) const {
        //TO DO: 伤害倍率计算
        //return: 返回id对应的宝可梦受到属性type的攻击的伤害倍率。
        //          如果id对应不存在宝可梦，返回 -1
        //这里type保证为单属性
    }

    int catchTry() const {
        //TO DO: 全图鉴捕获尝试
        //return: 按照前文过程最后能拥有的宝可梦数量。
    }

    struct iterator {
        //可以自己定义所需要的成员

        iterator &operator++() {
            //TO DO: ++迭代器
        }
        iterator &operator--() {
            //TO DO: --迭代器
        }
        iterator operator++(int) {
            //TO DO: 迭代器++
        }
        iterator operator--(int) {
            //TO DO: 迭代器--
        }
        iterator & operator = (const iterator &rhs) {
            //TO DO: 迭代器赋值
        }
        bool operator == (const iterator &rhs) const {
            //TO DO: 判断迭代器是否指向同一位置
        }
        bool operator != (const iterator &rhs) const {
            //TO DO: 不等号
        }
        Pokemon & operator*() const {
            //TO DO: * 运算符
        }
        /**
         * for the support of it->first.
         * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
         */
        Pokemon *operator->() const {
            //TO DO: -> 运算符
        }
    };

    iterator begin() {
        //return: 返回指向图鉴头部的迭代器
    }

    iterator end() {
        //return: 返回指向图鉴尾部的迭代器。
        //准确的说，是“最后的一个元素”的后面，指向的内容为空，详情可以去了解标准库容器的 end()
    }
};
