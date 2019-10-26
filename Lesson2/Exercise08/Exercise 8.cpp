#include <iostream>
#include <queue>

struct node
{
    std::string position;
    node *first, *second;
};

struct org_tree
{
    node *root;

    static org_tree create_org_structure(const std::string &pos)
    {
        org_tree tree;
        tree.root = new node{pos, NULL, NULL};
        return tree;
    }

    static node *find(node *root, const std::string &value)
    {
        if (root == NULL)
            return NULL;
        if (root->position == value)
            return root;
        auto firstFound = org_tree::find(root->first, value);
        if (firstFound != NULL)
            return firstFound;
        return org_tree::find(root->second, value);
    }

    bool addSubordinate(const std::string &manager, const std::string &subordinate)
    {
        auto managerNode = org_tree::find(root, manager);
        if (!managerNode)
        {
            std::cout << "No position named " << manager << std::endl;
            return false;
        }
        if (managerNode->first && managerNode->second)
        {
            std::cout << manager << " already has 2 subordinates." << std::endl;
            return false;
        }
        if (!managerNode->first)
            managerNode->first = new node{subordinate, NULL, NULL};
        else
            managerNode->second = new node{subordinate, NULL, NULL};
        return true;
    }

    static void levelOrder(node *start)
    {
        if (!start)
            return;
        std::queue<node *> q;
        q.push(start);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                auto current = q.front();
                q.pop();
                std::cout << current->position << ", ";
                if (current->first)
                    q.push(current->first);
                if (current->second)
                    q.push(current->second);
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    auto tree = org_tree::create_org_structure("CEO");
    
    auto insert = [&](const std::string& manager, const std::string& subordinate) {
        if (tree.addSubordinate(manager, subordinate)) {
            std::cout << "Added " << subordinate <<  " in the tree." << std::endl;
        } else {
            std::cout << "Couldn't add " << subordinate <<  " in the tree." << std::endl;
        }
    };
    
    insert("CEO", "Deputy Director");  
    insert("Deputy Director", "IT Head"); 
    insert("Deputy Director", "Marketing Head");
    insert("IT Head", "Security Head");
    insert("IT Head", "App Development Head");
    insert("Marketing Head", "Logistics Head");
    insert("Marketing Head", "Public Relations Head");
    insert("Deputy Director", "Finance Head");
    
    org_tree::levelOrder(tree.root);
}
