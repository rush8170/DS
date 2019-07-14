#include<bits/stdc++.h>
using namespace std;
struct node {
    int value;
    struct node* left,* right;
    int balance_factor;
};
struct node* root;

void create() {
    root = NULL;
}

struct node* search(struct node* root,int val) {
    if(root==NULL) {
        return root;
    }
    else {
        if(root->value==val) {
            return root;
        }
        else if(root->value<val) {
            return search(root->right,val);
        }
        else {
            return search(root->left,val);
        }
    }
    return root;
}

struct node* insert(struct node* root,int val,bool * flag) {
    if(root==NULL) {
        struct node* temp = (struct node*)malloc(sizeof(struct node));
        temp->value = val;
        temp->left = NULL;
        temp->right = NULL;
        temp->balance_factor = 0;
        *flag=true;
        return temp;
    }
    else {
        if(root->value<val) {
            root->right = insert(root->right,val,flag);
            //root->balance_factor = root->balance_factor - 1;
            //check for critical node
            struct node* child = root->right;
            if(*flag) {
                switch(root->balance_factor) {
                    case -1 : //right heavy
                    //Check for the balance factor of right child
                    if(child->balance_factor == -1) {
                        //Case of RR rotation 
                        cout<<"RR rotation"<<endl;
                        root->right = child->left;
                        child->left = root;
                        root->balance_factor = 0;
                        child->balance_factor = 0;
                        root = child;
                    }
                    else {
                        cout<<"RL rotation"<<endl;
                        struct node* grandchild = child->left;
                        child->left = grandchild->right;
                        root->right = grandchild->left;
                        grandchild->right = child;
                        grandchild->left = root;
                        if(grandchild->balance_factor== -1) {
                            root->balance_factor = 1;
                        }
                        else {
                            root->balance_factor = 0;
                        }
                        if(grandchild->balance_factor == 1) {
                            child->balance_factor = -1;
                        }
                        else {
                            child->balance_factor = 0;
                        }
                        grandchild->balance_factor = 0;
                        root = grandchild;
                    }
                    *flag = false;  
                    break;
                    case 0 : //Balanced
                    cout<<"Balanced-->Right heavy"<<endl;
                    root->balance_factor = -1;    
                    break;
                    case 1 : //Left Balanced
                    cout<<"Left heavy-->Balanced"<<endl;
                    *flag = false;
                    root->balance_factor = 0;
                    break;
                }  
            }
        }
        else {
            root->left = insert(root->left,val,flag);
            //root->balance_factor = root->balance_factor + 1;
            //check for critical node
            if(*flag) {
                switch(root->balance_factor) {
                    case -1://Right balanced
                            cout<<"Right heavy-->Balanced"<<endl;
                            *flag = false;
                            root->balance_factor = 0;
                            break;
                    case 0://Balanced
                            cout<<"Balanced-->Left heavy"<<endl;
                            root->balance_factor = 1;
                            break;
                    case 1://Left balanced
                    struct node* child = root->left;
                    if(child->balance_factor == 1) {
                        //LL rotation
                        cout<<"LL rotation"<<endl;
                        root->left = child->right;
                        child->right = root;
                        root->balance_factor = 0;
                        child->balance_factor = 0;
                        root = child;
                    }
                    else {
                        //LR rotation
                        cout<<"LR rotation"<<endl;
                        struct node* grandchild = child->right;
                        child->right = grandchild->left;
                        root->left = grandchild->right;
                        grandchild->left = child;
                        grandchild->right = root;
                        if(grandchild->balance_factor == 1) {
                            root->balance_factor = -1;
                            //child->balance_factor = 0;
                        }
                        else {
                            root->balance_factor = 0;
                        }
                        if(grandchild->balance_factor == -1) {
                            child->balance_factor = 1;
                        }
                        else {
                            child->balance_factor = 0;
                        }
                        grandchild->balance_factor = 0;
                        root = grandchild;
                    }
                    *flag=false;
                    break;
                }
            }
        }
    }
    return root;
}

void display(struct node* root) {
    if(root==NULL) return;
    cout<<"Value:"<<root->value<<" Factor:"<<root->balance_factor<<endl;
    display(root->left);
    display(root->right);
}

int main() {
    create();
    int choice;
    cout<<"Enter choice 1.Insert 2.Find 3.Display 4.Exit"<<endl;
    cin>>choice;
    int val;
    bool flag = false;
    while(choice!=4) {
        switch(choice) {
            case 1 : cout<<"Enter value";
                    cin>>val;
                    root = insert(root,val,&flag);
                    break;
            case 2: cout<<"Enter value";
                    cin>>val;
                    if(search(root,val)!=NULL) cout<<"Found"<<endl;
                    else cout<<"Not Found!"<<endl;
                    break;
            case 3: display(root);
                    break;
        }
        cout<<"Enter choice 1.Insert 2.Find 3.Display 4.Exit"<<endl;
        cin>>choice;
    }
    return 0;
}