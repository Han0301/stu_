#include <vector>
#include <iostream>

// 检测结果
struct det_data
{

};

// 链表节点
struct linked_node
{
    // data
    det_data m_data;
    // ptr
    linked_node* last_ptr;
    linked_node* next_ptr;

    // 构造时传入数据
    linked_node(det_data data)
    :last_ptr(nullptr),
     next_ptr(nullptr),
     m_data(data)
    {}
};

// 通用的链表方法
class linked_lists
{
public:
    // 构造
    linked_lists()
    {
        start_ptr = nullptr;
        end_ptr = nullptr;
        size = 0;
    }

    // 析构
    ~linked_lists()
    {
        // 1 先指向第一个链表节点指针
        linked_node* now_ptr = start_ptr;
        // 2 但指针不为空
        while(now_ptr)
        {
            // 2.1 保存下一个指针位置
            linked_node* next_ptr = now_ptr->next_ptr;
            // 2.2 删除当前指针内容
            delete now_ptr;
            // 2.3 赋值回去
            now_ptr = next_ptr;
        }
    }

    // 传入新节点数据, 从尾部添加新的节点
    void add_end(const det_data& data)
    {
        linked_node* new_ptr = new linked_node(data);
        if (!end_ptr)       // 空链表
        {
            // 新增链表的第一个节点
            start_ptr = new_ptr;
            end_ptr = new_ptr;
        }
        else        // 链表中节点数 >= 1
        {
            new_ptr->last_ptr = end_ptr;        // 等价与 (*new_ptr).last_ptr = end_ptr;
            end_ptr->next_ptr = new_ptr;
            end_ptr = new_ptr;      // 最后将 end_ptr 指向最后一个
        }
        size++;
    }
    
    // 删除指定节点
    void del_node(linked_node* remove_node)
    {
        linked_node* last_node = remove_node->last_ptr;
        linked_node* next_node = remove_node->next_ptr;

        if (last_node)
        {
            last_node->next_ptr = remove_node->next_ptr;
        }
        else        // 删除的是头节点
        {
            start_ptr = next_node;
        }

        if (next_node)
        {
            next_node->last_ptr = remove_node->last_ptr;
        }
        else        // 删除的是尾节点
        {
            end_ptr = last_node;
        }
        delete remove_node;
        size--;
    }

    // 批量提取链表中数据, 返回容器
    std::vector<det_data> data_to_vector() const
    {
        std::vector<det_data> data_lists;

        linked_node* now_ptr = start_ptr;
        while(now_ptr)
        {
            data_lists.push_back(now_ptr->m_data);
            now_ptr = now_ptr->next_ptr;
        }
        return data_lists;
    }

    int get_size() const
    {
        return size;
    }

private:
    linked_node* start_ptr;
    linked_node* end_ptr;
    int size;
};

int test1()
{
    linked_lists linked_lists_;
    std::vector<det_data> data_lists;

    data_lists.resize(10);
    std::cout << "data_lists.size(): " << data_lists.size() << std::endl;

    for (size_t i = 0; i < data_lists.size(); i++)
    {
        std::cout << "push" << std::endl;
        linked_lists_.add_end(data_lists[i]);
    }
    std::cout << "linked_lists_.get_size(): " << linked_lists_.get_size() << std::endl;
}
int main()
{
    test1();
    return 0;
}