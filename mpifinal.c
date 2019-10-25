code1="""

#include<omp.h>
#include<chrono>
#include<iostream>
#include<stdio.h>

using namespace std;
using namespace std::chrono;

class Node
{
  public:
    int val;
    Node *left,*right;

    Node(int val)
    {
        this->val=val;
        this->left=NULL;
        this->right=NULL;
    }
};

void dfs(Node *root)
{
    if(root==NULL)
      return;
    else
    {
        dfs(root->left);

        dfs(root->right);

        cout<<root->val<<"\t";
    }
}

void pdfs(Node *root)
{
    if(root==NULL)
      return;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            pdfs(root->left);
        }

        #pragma omp section
        {
            pdfs(root->right);
        }
    }

    cout<<root->val<<"\t";



}

int main()
{
  int n=5000;
  int a[n];

  for(int i=0;i<n;i++)
    a[i]=i;

  Node *root=NULL;

  root=new Node(a[0]);

  for(int i=1;i<n;i++)
  {
      Node *nn=new Node(a[i]);
      Node *temp=root;

      while(temp!=NULL)
      {
        using namespace std::chrono;
        if(nn->val < temp->val)
        {
            if(temp->left==NULL)
            {
                temp->left=nn;
                break;

            }
            else
              temp=temp->left;
        }
        else
        {
            if(temp->right==NULL)
            {
                temp->right=nn;
                break;
            }
            else
              temp=temp->right;
        }
      }
  } //end for

  double start,end;
  start=omp_get_wtime();
  dfs(root);
  end=omp_get_wtime();
  cout<<endl;
  cout<<"serial:"<<end-start<<endl;

  start=omp_get_wtime();
  pdfs(root);
  end=omp_get_wtime();
  cout<<endl;
  cout<<"parallel:"<<end-start<<endl;
}

"""
