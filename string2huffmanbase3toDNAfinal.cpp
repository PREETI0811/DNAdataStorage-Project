#include <iostream>
#include<vector>
#include <queue>
#include<utility>
#include<string>
using namespace std;
vector<char> D;
vector<int> HC;
void getDNAcode(string h)
{
    string encDNA;
    if(h[0]=='0')
        encDNA.push_back('C');
    else if(h[0]=='1')
         encDNA.push_back('G');
    else if(h[0]=='2')
         encDNA.push_back('T');
        for(int i=1;i<h.size();i++)
        {
            if(encDNA[i-1]=='A')
                 {
                     if(h[i]=='0')
                       encDNA.push_back('C');
                     else if(h[i]=='1')
                       encDNA.push_back('G');
                       else if(h[i]=='2')
                        encDNA.push_back('T');
                 }
             if(encDNA[i-1]=='C')
                 {
                     if(h[i]=='0')
                       encDNA.push_back('G');
                     else if(h[i]=='1')
                       encDNA.push_back('T');
                       else if(h[i]=='2')
                        encDNA.push_back('A');
                 }
                 if(encDNA[i-1]=='G')
                 {
                     if(h[i]=='0')
                       encDNA.push_back('T');
                     else if(h[i]=='1')
                       encDNA.push_back('A');
                       else if(h[i]=='2')
                        encDNA.push_back('C');
                 }
                 if(encDNA[i-1]=='T')
                 {
                    if(h[i]=='0')
                       encDNA.push_back('A');
                     else if(h[i]=='1')
                       encDNA.push_back('C');
                       else if(h[i]=='2')
                        encDNA.push_back('G');
                 }


        }
          cout<<endl;

            cout<<encDNA;

}
class huff_node {
public:

    char data;
    int freq;
    huff_node* l;
    huff_node* m;
    huff_node* r;
    huff_node(char character, int frequency)
    {
        data = character;
        freq = frequency;
        l = m = r = NULL;
    }
};

class cmp {
public:
    bool operator()(huff_node* a, huff_node* b)
    {
        return a->freq > b->freq;
    }
};

huff_node* generateTree(priority_queue<huff_node*, vector<huff_node*>, cmp> pq)
{
    while (pq.size() != 1)
        {
        huff_node* l = pq.top(); //cout<<endl<< pq.top()->data;
        pq.pop();
        huff_node* m = pq.top();//cout<<endl<< pq.top()->data;
        pq.pop();
        huff_node* r = pq.top(); //cout<<endl<< pq.top()->data;
        pq.pop();
        huff_node* node = new huff_node('#', l->freq + m->freq + r->freq); //#represents node i.e. not a leaf
        //cout<<endl<<l->freq + m->freq + r->freq;//new nodes freq
        //cout<<endl<<node->freq;
        node->l = l;
        node->m = m;
        node->r = r;
        pq.push(node);

    }
    //cout<<endl<<pq.top()->freq;
    return pq.top(); //returns root in the end
}

//pair<char,int> get_huffCode(huff_node* root, int pq_arr[],int i)
void get_huffCode(huff_node* root, int pq_arr[],int i)
{
    if (root->l) //checking if left branch of node his n ie not NULL
        {
        pq_arr[i]=0;
        get_huffCode(root->l, pq_arr,i+1); //recursive call
    }

     if (root->m) {
        pq_arr[i]=1;
        get_huffCode(root->m, pq_arr,i+1);
    }
    if (root->r) {
       pq_arr[i]=2;
        get_huffCode(root->r, pq_arr,i+1);
    }

    if (!root->l && !root->m && !root->r) //if its a leaf
        { int hCode;
        //cout << root->data << " ";
        //for (int j = 0; j < i; j++) {
           // cout << pq_arr[j];}
          //cout << endl;
         hCode=pq_arr[0];
          for (int j = 1; j < i; j++)
            hCode+=pq_arr[j]*10;
        //cout<<root->data<<","<<hCode<<endl;
        D.push_back(root->data);
        HC.push_back(hCode);
    }

}

void  huff(vector<char> data, vector<int> freq, int size)
{
    priority_queue<huff_node*, vector<huff_node*>,cmp> pq;
    for (int i = 0; i < size; i++)
    {
        huff_node* newNode
            = new huff_node(data[i], freq[i]);
        pq.push(newNode);
    }
 /* while(!pq.empty())
    {
        cout<<"\n"<<pq.top()->data<<","<<pq.top()->freq;
       pq.pop();
    }*/
   huff_node* root = generateTree(pq);
   int pq_arr[(size+1)%3+1],i=0;
  get_huffCode(root, pq_arr, i);


}
int main()
{
    string s; //ip string
    string h;  //huffman string
    string d; //DNA string
    cin>>s;
    vector<char> data;
    vector<int> freq ;
    data.push_back(s[0]);
    freq.push_back(1);
    int j;
    for(int i=1;i<s.size();i++)
        {  int cond=0;
             for(j=0;j<data.size();j++)
             {
              if(data[j]==s[i])
              {
              cond=1;
              freq[j]++;
              break;
              }
             }
          if(cond==0)
          {data.push_back(s[i]);
           freq.push_back(1);}
        }

  if(data.size()%2==0)
   {data.push_back('`');
    freq.push_back(0);
   }
huff(data, freq, data.size());

for(int i=0;i<s.size();i++)
{
    for(int j=0;j<D.size();j++)
        if(s[i]==D[j])
        h.append(to_string(HC[j]));
}
cout<<h;
getDNAcode(h);

return 0;
}
