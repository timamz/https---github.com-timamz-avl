#include <iostream>
#include <string>
#include <vector>

class AVLTree
{
public:
    class Node
    {
    public:
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int k) : key(k), height(1), left(nullptr), right(nullptr)
        {}
    };

private:
    Node* root;

    Node* rotateRight(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;       
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }


    int height(Node* N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    Node* insert(Node* node, int key)
    {

        if (node == nullptr)
            return (new Node(key));

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }


    Node* minValueNode(Node* node)
    {
        Node* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }


    Node* deleteNode(Node* root, int key)
    {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else
        {
            if ((root->left == nullptr) || (root->right == nullptr))
            {
                Node* temp;
                if (root->left != nullptr)
                    temp = root->left;
                else
                    temp = root->right;

                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else
            {

                Node* temp = minValueNode(root->right);

                root->key = temp->key;

                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + std::max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }


    int getBalance(Node* N)
    {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    bool exists(Node* root, int key)
    {
        if (root == nullptr)
            return false;

        if (key < root->key)
            return exists(root->left, key);

        else if (key > root->key)
            return exists(root->right, key);

        else
            return true;
    }

public:
    AVLTree() : root(nullptr)
    {}

    ~AVLTree()
    {
        eraseALL(root);
    }

    void eraseALL(Node* current)
    {
        if (!current)
            return;

        eraseALL(current->left);
        eraseALL(current->right);
        delete current;
    }

    void insert(int key)
    {
        root = insert(root, key);
    }

    void deleteNode(int key)
    {
        root = deleteNode(root, key);
    }

    bool exists(int key)
    {
        return exists(root, key);
    }

    void inorder(Node* current)
    {
        if (current)
        {
            inorder(current->left);
            std::cout << current->key << ' ';
            inorder(current->right);
        }
    }

    void printTree()
    {
        inorder(root);
    }
};

void inorder(AVLTree::Node* current)
{
    if (current)
    {
        inorder(current->left);
        std::cout << current->key;
        inorder(current->right);
    }
}

int main()
{
	AVLTree avlTree;

	std::vector<int> data = {90, 80, 70, 60, 50, 75};

	for(int i = 0; i < data.size(); i++)
	{
        avlTree.insert(data[i]);
	}

    avlTree.printTree();
}
