#include <iostream>
#include<list>
using namespace std;

namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    public:
        BinaryTree():root(nullptr)
        {}
        ~BinaryTree()
        {
        }
          struct Node
        {
            T value;
            Node *left;
            Node *right;
           Node(T value):value(value),left(nullptr),right(nullptr){}
        };

        Node *root;

 BinaryTree(const BinaryTree &other)
    {
          if (other.root!=nullptr)
            {
            root = new Node(other.root->value);    
            copyTree(root,other.root);
            }
    }

   BinaryTree(BinaryTree &&other) noexcept 
      {
            move(other);
      }
     
         BinaryTree & operator = (BinaryTree &&other) noexcept
        {
        this*=move(other->root);
        return *this;
        }

        BinaryTree<T> &add_root(T value)
        {
            if(root!=nullptr)
            {
                root->value=value;
            }
            else{
             root=new Node(value);
              root->value=value;
            }
                  return *this;
        }
     BinaryTree &operator= (const BinaryTree other) 
    {
        if (this != &other) 
        { 
            root=new Node(other.root->value);   
            copyTree(root,other.root);
        }
        return *this;
    }
      BinaryTree<T> &add_right(T parent, T nodeAdd)
          {
             Node* findRight=findNode(root,parent);
             if(root!=nullptr&&findRight!=nullptr)
             {
             if (findRight->right == nullptr) 
             {
                 findRight->right = new Node(nodeAdd); 
             }
             else{(findRight->right)->value=nodeAdd;}
             return *this;
             }
              throw std::invalid_argument(" node not found ");
         }

         BinaryTree<T> &add_left( T parent, T nodeAdd)
         {
            Node* findLeft=findNode(root,parent);
             if(root!=nullptr&&findLeft!=nullptr)
             {             
             if (findLeft->left == nullptr) 
             {
                 findLeft->left = new Node(nodeAdd); 
             }
             else{(findLeft->left)->value=nodeAdd;}
             return *this;
             }
             throw std::invalid_argument("node not found");
             
         }

        friend ostream &operator<<(ostream &out, const BinaryTree &tree)
        {
            return out;
        }

       Node* findNode(Node *root,T value)
        {
            
            if(root==nullptr)
            {
             return nullptr;
            }
            if(root->value==value)
            {
                return root;
            }
             Node* next=findNode(root->left,value);
             if(next==nullptr)
            {
            next= findNode(root->right,value);
            }
                return next;
            
        }

         void copyTree(Node* first, Node* other)
        {
            if(other->left!=nullptr)
            {
                first->left=new Node(other->left->value);
                copyTree(first->left,other->left);
            }
            if(other->right!=nullptr)
            {
                 first->right=new Node(other->right->value);
                 copyTree(first->right,other->right);
            }
        }
      

        class inOrderIt
        {
        public:
        int n=-1;
            Node *curr;
            list<Node *> s;

        void preOrderInit(Node *root)
            {
                if (root==nullptr)
                {
                    return;
                }
                s.push_front(root);
                preOrderInit(root->left);
                preOrderInit(root->right);
            }
            void inOrderInit(Node *root)
            {
                if (root==nullptr)
                {
                    return;
                }
                inOrderInit(root->left);
                 s.push_front(root);
                inOrderInit(root->right);
            }
           void postOrderInit(Node *root)
            {
                if (root==nullptr)
                {
                    return;
                }
                postOrderInit(root->left);
                postOrderInit(root->right);
                s.push_front(root);
            }
            

            inOrderIt(Node *node, int n) 
            {
                n=n;
                curr=node;
                if(n==0)
                {
                preOrderInit(curr);
                }
                if(n==1)
                {
                inOrderInit(curr);
                }
                if(n==2)
                {
                 postOrderInit(curr);
                }
                s.push_front(nullptr);
                curr =s.back();
                s.pop_back();

            }

            inOrderIt &operator++()
            {
            curr=s.back();
            s.pop_back();
            return *this;
               
            }

            inOrderIt operator++(int)
            {
                inOrderIt it = *this;
                curr=s.back();
                s.pop_back();
                return it;
            }
            T &operator*() const
            {
             return curr->value;
            }

            T *operator->() const
            {
                return &curr->value;
            }

            bool operator==(const inOrderIt &rhs) const
            {
                return curr==rhs.curr;
            }

            bool operator!=(const inOrderIt &rhs) const
            {
                return !(curr==rhs.curr);
            }

      
        };

        inOrderIt end_inorder() 
        {
            return inOrderIt(nullptr,0);
        }
        inOrderIt begin_inorder()
        {
            return inOrderIt(this->root,1);
        }

        inOrderIt end_postorder() 
        {
          return inOrderIt(nullptr,2);
        }
        inOrderIt begin_postorder() 
        {
            return inOrderIt(this->root,2);
        }

         inOrderIt end_preorder() 
        {
            return inOrderIt(nullptr,0);
        }
        inOrderIt begin_preorder() 
        {
       
         return inOrderIt(this->root,0);
        }
      inOrderIt begin() 
        {
               return inOrderIt(this->root,1);
        }
        inOrderIt end() 
        {
            return inOrderIt(nullptr,1);
        }
       
};
    } 
