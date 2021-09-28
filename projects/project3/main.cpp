#include <iostream>
#include "kdtree.hpp"
using namespace std;
int main()
{
    vector<pair<tuple<int,int,int>, int>> vec;
    auto k1=make_tuple(0,0,0);
    auto e1=make_pair(k1,1);
    auto k2=make_tuple(0,0,0);
    auto e2=make_pair(k2,2);
    auto k3=make_tuple(-1,2,0);
    auto e3=make_pair(k3,3);
    auto k4=make_tuple(1,-1,0);
    auto e4=make_pair(k4,4);
    vec.push_back(e1);
    vec.push_back(e2);
    vec.push_back(e3);
    vec.push_back(e4);
    KDTree<tuple<int,int,int>, int> kdtree(vec);
    auto key1=make_tuple(0,0,0);
    auto key2=make_tuple(-1,2,-4);
    auto key3=make_tuple(1,-1,-10);
    auto key4=make_tuple(3,-2,3);
    auto key5=make_tuple(4,-3,2);
    auto key6=make_tuple(-2,4,9);
    auto key7=make_tuple(-3,1,1);
    auto key8=make_tuple(-6,-10,-7);
    auto key9=make_tuple(1,-1,-10);
    auto key10=make_tuple(16,23,-23);
    auto key11=make_tuple(-23,32,34);
    auto key12=make_tuple(-11,12,31);
    auto key13=make_tuple(49,-11,-24);
    auto key14=make_tuple(33,34,70);
    auto key15=make_tuple(-100,-100,-100);
    //////////////////////////////////////////////
    auto ele1=make_pair(key1,1);
    auto ele2=make_pair(key2,2);
    auto ele3=make_pair(key3,3);
    auto ele4=make_pair(key4,4);
    auto ele5=make_pair(key5,5);
    auto ele6=make_pair(key6,6);
    auto ele7=make_pair(key7,7);
    auto ele8=make_pair(key8,8);
    auto ele9=make_pair(key9,100);
    auto ele10=make_pair(key10,50);
    auto ele11=make_pair(key11,70);
    auto ele12=make_pair(key12,18);
    auto ele13=make_pair(key13,20);
    auto ele14=make_pair(key14,80);
    auto ele15=make_pair(key15,200);
    /////////////////////////////////////////////
    kdtree.insert(key1,1);
    kdtree.insert(key2,2);
    kdtree.insert(key3,3);
    kdtree.insert(key4,4);
    kdtree.insert(key5,5);
    kdtree.insert(key6,6);
    kdtree.insert(key7,7);
    kdtree.insert(key8,8);
   // cout<<kdtree.findMin(2)->second<<endl;
    kdtree.insert(key9,100);
    kdtree.insert(key10,50);
    kdtree.insert(key11,70);
    kdtree.insert(key12,18);
    kdtree.insert(key13,20);
    kdtree.insert(key14,80);
    kdtree.insert(key15,-200);
kdtree.erase(k3);
    cout<<kdtree.find(key15)->second<<"=100?"<<endl;
//     KDTree<tuple<int,int,int>, int> kdtree1(vec);
//    kdtree=kdtree1;
//    auto it=kdtree.end();
////    cout<<(*(--it)).second<<"iterator test"<<endl;
//    auto it=kdtree.begin();
//    cout<<(*(++++++it)).second<<"iterator test"<<endl;
    KDTree<tuple<int,int,int>, int> kdtree1(kdtree);
    kdtree1=kdtree;
//    for (auto &item : kdtree1)
//    {
//        cout<< item.second<<endl;
//    }
//for (auto item2=kdtree1.begin();item2!=kdtree1.end();item2++){
//    cout<< item2->second<<endl;
//}

}