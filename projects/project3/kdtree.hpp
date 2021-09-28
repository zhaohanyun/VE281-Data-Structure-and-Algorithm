#include <tuple>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdexcept>

/**
 * An abstract template base of the KDTree class
 */
template<typename...>
class KDTree;

/**
 * A partial template specialization of the KDTree class
 * The time complexity of functions are based on n and k
 * n is the size of the KDTree
 * k is the number of dimensions
 * @typedef Key         key type
 * @typedef Value       value type
 * @typedef Data        key-value pair
 * @static  KeySize     k (number of dimensions)
 */
template<typename ValueType, typename... KeyTypes>
class KDTree<std::tuple<KeyTypes...>, ValueType> {
public:
    typedef std::tuple<KeyTypes...> Key;
    typedef ValueType Value;
    typedef std::pair<const Key, Value> Data;
    static inline constexpr size_t KeySize = std::tuple_size<Key>::value;
    static_assert(KeySize > 0, "Can not construct KDTree with zero dimension");
protected:
    struct Node {
        Data data;
        Node *parent;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(const Key &key, const Value &value, Node *parent) : data(key, value), parent(parent) {}

        const Key &key() { return data.first; }

        Value &value() { return data.second; }
    };

public:
    /**
     * A bi-directional iterator for the KDTree
     * ! ONLY NEED TO MODIFY increment and decrement !
     */
    class Iterator {
    private:
        KDTree *tree;
        Node *node;

        Iterator(KDTree *tree, Node *node) : tree(tree), node(node) {}

        /**
         * Increment the iterator
         * Time complexity: O(log n)
         */
        void increment() {
            // TODO: implement this function
            if(node->right){//if has right subtree, then increment will be the leftmost of the right subtree.
                node=node->right;
                while(node->left) node=node->left;
            }
            else{//go up and find a 'right' ancestor
                if (!node->parent) {//reach the root node
                    node= nullptr;
                    return;
                }
                //while(!node->parent->right || node->parent->right->data.first==node->data.first){
                while((node->parent->left && node->parent->left->data.first!=node->data.first) || !node->parent->left){
                    //if data==data, because left child must be smaller, so it must be a "left" parent
                    node=node->parent;
                    if (node->parent== nullptr) {
                        node= nullptr;
                        return;
                    }
                }
//                if(node->parent->right) {
//                    node = node->parent->right;
//                    while (node->left) node = node->left;
//                }
//                else
                node=node->parent;
            }
        }

        /**
         * Decrement the iterator
         * Time complexity: O(log n)
         */
        void decrement() {
            // TODO: implement this function
            if(node->left){
                node=node->left;
                while(node->right) node=node->right;
            }
            else{
                if(node->parent== nullptr){
                    node= nullptr;
                    return;
                }
                while((node->parent->right && node->parent->right->data.first!=node->data.first) || !node->parent->right) {
                    node = node->parent;
                    if (node->parent == nullptr) {
                        node = nullptr;
                        return;
                    }
                }
//                if(node->parent->left) {
//                    node = node->parent->left;
//                    while (node->right) node = node->right;
//                }
//                else
                node=node->parent;
            }
        }

    public:
        friend class KDTree;

        Iterator() = delete;

        Iterator(const Iterator &) = default;

        Iterator &operator=(const Iterator &) = default;

        Iterator &operator++() {
            increment();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            increment();
            return temp;
        }

        Iterator &operator--() {
            decrement();
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            decrement();
            return temp;
        }

        bool operator==(const Iterator &that) const {
            return node == that.node;
        }

        bool operator!=(const Iterator &that) const {
            return node != that.node;
        }

        Data *operator->() {
            return &(node->data);
        }

        Data &operator*() {
            return node->data;
        }
    };

protected:                      // DO NOT USE private HERE!
    Node *root = nullptr;       // root of the tree
    size_t treeSize = 0;        // size of the tree

    /**
     * Find the node with key
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param node
     * @return the node with key, or nullptr if not found
     */
    template<size_t DIM>
    Node *find(const Key &key, Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        //node is root
        if(!node) return nullptr;
        else {
            if (node->data.first == key) return node;
            else if (std::get<DIM>(key)< std::get<DIM>(node->data.first)) {//go to the left subtree
                return find<DIM_NEXT>(key, node->left);
            }
            else{//go to the right subtree
                return find<DIM_NEXT>(key, node->right);
            }
        }
    }

    /**
     * Insert the key-value pair, if the key already exists, replace the value only
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param value
     * @param node
     * @param parent
     * @return whether insertion took place (return false if the key already exists)
     */
    template<size_t DIM>
    bool insert(const Key &key, const Value &value, Node *&node, Node *parent) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if(!node) {
            node=new Node(key,value,parent);
            node->left= nullptr;
            node->right= nullptr;
//            if(fuckcompare<DIM,std::less<>>(key,parent->key())){//the new node is a left leaf
//               // compareKey<DIM_CMP,std::less<>>(min->data.first,root->data.first)
//                parent->left=node;//std::cout<<"left ";
//            }
//            else{
//                parent->right=node;//std::cout<<"right ";
//            }
            this->treeSize++;
            return true;
        }
        else{
            if(node->data.first==key){
                node->data.second=value;//std::cout<<"replace ";
                return false;
            }
            if(fuckcompare<DIM,std::less<>>(key,node->key())){//go to the left subtree
                return insert<DIM_NEXT>(key,value,node->left,node);
            }
            else{
                return insert<DIM_NEXT>(key,value,node->right,node);
            }
        }
    }

    /**
     * Compare two keys on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return relationship of two keys on a dimension with the compare function
     */
    template<size_t DIM, typename Compare>
    static bool compareKey(const Key &a, const Key &b, Compare compare = Compare()) {
        if (std::get<DIM>(a) != std::get<DIM>(b)){
            return compare(std::get<DIM>(a), std::get<DIM>(b));
        }
        return compare(a, b);
    }

    template<size_t DIM, typename Compare>
    static bool fuckcompare(const Key &a, const Key &b, Compare compare = Compare()) {
        return compare(std::get<DIM>(a), std::get<DIM>(b));
    }

    /**
     * Compare two nodes on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return the minimum / maximum of two nodes
     */
    template<size_t DIM, typename Compare>
    static Node *compareNode(Node *a, Node *b, Compare compare = Compare()) {
        if (!a) return b;
        if (!b) return a;
        return compareKey<DIM, Compare>(a->key(), b->key(), compare) ? a : b;
    }

    /**
     * Find the minimum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the minimum node on a dimension
     */
    template<size_t DIM_CMP, size_t DIM>
    Node *findMin(Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if(!node) return nullptr;
        Node *min=findMin<DIM_CMP,DIM_NEXT>(node->left);
        if(DIM_CMP!=DIM){
            Node* rightmin=findMin<DIM_CMP,DIM_NEXT>(node->right);
            //min=minNode<DIM_CMP>(min,rightmin);
            min=compareNode<DIM_CMP,std::less<>>(min,rightmin);
        }//要排除和nullptr比较！！
        //return minNode<DIM_CMP>(min,node);
        return compareNode<DIM_CMP,std::less<>>(min,node);
        //node *findMin(node *root, int dimCmp, int dim) {// dimCmp: dimension for comparison  if(!root) return NULL;
        // node *min =     findMin(root->left, dimCmp, (dim+1)%numDim);
        // if(dimCmp != dim) {    rightMin =     findMin(root->right, dimCmp, (dim+1)%numDim);
        // min = minNode(min, rightMin, dimCmp);  }  return minNode(min, root, dimCmp);}

        }

    template<size_t DIM_CMP>
    Node *minNode(Node *min,Node *target){//may be leftmin and rightmin, or min of subtrees and root
        if(!min && !target) return nullptr; //only possible when comparing two unexisting children of a leaf
        if(!min) return target; //comparing the min in subtree with a leaf itself or leftmin is null
        if(!target) return min; //rightmin is null
        return compareKey<DIM_CMP,std::less<>>(min->data.first,root->data.first) ? min : target;
            //if min == target(root), then root (the first node encountered) will be returned.
    }
    /**
     * Find the maximum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the maximum node on a dimension
     */
    template<size_t DIM_CMP, size_t DIM>
    Node *findMax(Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if(!node) return nullptr;
        Node *max=findMax<DIM_CMP,DIM_NEXT>(node->right);
        if(DIM_CMP!=DIM){
            Node* leftmax=findMax<DIM_CMP,DIM_NEXT>(node->left);
            //max=maxNode<DIM_CMP>(max,leftmax);
            max=compareNode<DIM_CMP,std::greater<>>(max,leftmax);
        }
        //return maxNode<DIM_CMP>(max,node);
        return compareNode<DIM_CMP,std::greater<>>(max,node);
    }

    //minNode 和 maxNode tmd 写错了
    template<size_t DIM_CMP>
    Node *maxNode(Node *max,Node *target){
        if(!max && !target) return nullptr;
        if(!max) return target;
        if(!target) return max;
        return compareKey<DIM_CMP,std::greater<>>(max->data.first,root->data.first) ? max : target;
    }

    template<size_t DIM>
    Node *findMinDynamic(size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return findMin<DIM, 0>(root);
        return findMinDynamic<DIM_NEXT>(dim);
    }

    template<size_t DIM>
    Node *findMaxDynamic(size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return findMax<DIM, 0>(root);
        return findMaxDynamic<DIM_NEXT>(dim);
    }

    /**
     * Erase a node with key (check the pseudocode in project description)
     * Time Complexity: max{O(k log n), O(findMin)}
     * @tparam DIM current dimension of node
     * @param node
     * @param key
     * @return nullptr if node is erased, else the (probably) replaced node
     */
    template<size_t DIM>
    Node *erase(Node *node, const Key &key) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if(!node) return nullptr;
        if(node->key()==key) {
            if (!node->left && !node->right) {
                delete node;
                treeSize--;
                return nullptr;
            }
            else if (node->right) {
                Node *min = findMin<DIM, DIM_NEXT>(node->right);
                node->data.second=min->value();
                const_cast<Key&>(node->key())=min->key();
                node->right=erase<DIM_NEXT>(node->right,min->key());
            }
            else if (node->left){
                Node *max = findMax<DIM, DIM_NEXT>(node->left);
                node->data.second=max->value();
                const_cast<Key&>(node->key())=max->key();
                node->left=erase<DIM_NEXT>(node->left,max->key());
            }
        }
        else{//node->key()!=key
            if(compareKey<DIM,std::less<>>(key,node->key()))
                node->left=erase<DIM_NEXT>(node->left,key);
            else
                node->right=erase<DIM_NEXT>(node->right,key);
        }
        return node;
    }

    template<size_t DIM>
    Node *eraseDynamic(Node *node, size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return erase<DIM>(node, node->key());
        return eraseDynamic<DIM_NEXT>(node, dim);
    }

    // TODO: define your helper functions here if necessary

public:
    KDTree() = default;

    /**
     * Time complexity: O(kn log n)
     * @param v we pass by value here because v need to be modified
     */
    explicit KDTree(std::vector<std::pair<Key, Value>> v) {
        // TODO: implement this function
        //std::stable_sort(v.begin(),v.end(),mycmp<0,std::less<>>);
        std::stable_sort(v.begin(),v.end(),mycmp<0>);
        auto it=std::unique(v.rbegin(),v.rend(),myequal);
        v.erase(--it.base());
        treeSize=v.size();
        root=KDTree_helper<0>(v, nullptr);
    }
    template <size_t DIM>
    Node* KDTree_helper(std::vector<std::pair<Key, Value>> data, Node* parent){
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if(data.empty()) return nullptr;
        //std::stable_sort(data.begin(),data.end(),mycmp<DIM,std::less<>>);
        std::stable_sort(data.begin(),data.end(),mycmp<DIM>);
        //typename std::vector<Data>::Iterator it=std::unique(data.rbegin(),data.rend(),myequal());
        //data.erase(--it.base());
        auto it2=data.begin();
        for(unsigned int i=1;i<(data.size()+1)/2;i++){
            it2++;
        }
        //it2 is the median
        Node *root_temp=new Node(it2->first, it2->second, parent);
        std::vector<std::pair<Key, Value>> left(data.begin(),it2);
        std::vector<std::pair<Key, Value>> right(++it2,data.end());

        root_temp->left=KDTree_helper<DIM_NEXT>(left,root_temp);
        root_temp->right=KDTree_helper<DIM_NEXT>(right,root_temp);
        return root_temp;
    }

//    template<size_t DIM , typename Compare>
//    static bool mycmp(const Data A, const Data B, Compare compare = Compare()){
//        return compareKey<DIM,std::less<>>(A.first,B.first);
//    }
    template<size_t DIM>
    static bool mycmp(const Data A, const Data B){
        return compareKey<DIM,std::less<>>(A.first,B.first);
    }

    static bool myequal(const Data A, const Data B){
        return A.first==B.first;
    }
    /**
     * Time complexity: O(n)
     */


    /**
     * Time complexity: O(n)
     */
    KDTree &operator=(const KDTree &that) {
        // TODO: implement this function
        treeSize=that.treeSize;
        root=KDTree_helper2(that.root, nullptr);
        return *this;
    }

    KDTree(const KDTree &that) {
        // TODO: implement this function
        treeSize=that.treeSize;
        root=KDTree_helper2(that.root, nullptr);
    }

    //template <size_t DIM>
    Node* KDTree_helper2(Node* node,Node* parent){
        //constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if(!node) return nullptr;
        Node* temp_root=new Node(node->data.first,node->data.second,parent);
        //temp_root->parent=parent;
        //temp_root->left=KDTree_helper2<DIM_NEXT>(node->left,temp_root);
        //temp_root->right=KDTree_helper2<DIM_NEXT>(node->right,temp_root);
        temp_root->left=KDTree_helper2(node->left,temp_root);
        temp_root->right=KDTree_helper2(node->right,temp_root);
        return temp_root;
    }

    /**
     * Time complexity: O(n)
     */
    ~KDTree() {
        // TODO: implement this function
        des_helper(this->root);
    }

    void des_helper(Node* node){
        if(node){
            des_helper(node->left);
            des_helper(node->right);
            delete node;
        }
        else return;
    }

    Iterator begin() {
        if (!root) return end();
        auto node = root;
        while (node->left) node = node->left;
        return Iterator(this, node);
    }

    Iterator end() {
        return Iterator(this, nullptr);
    }

    Iterator find(const Key &key) {
        return Iterator(this, find<0>(key, root));
    }

    void insert(const Key &key, const Value &value) {
        insert<0>(key, value, root, nullptr);
    }

    template<size_t DIM>
    Iterator findMin() {
        return Iterator(this, findMin<DIM, 0>(root));
    }

    Iterator findMin(size_t dim) {
        return Iterator(this, findMinDynamic<0>(dim));
    }

    template<size_t DIM>
    Iterator findMax() {
        return Iterator(this, findMax<DIM, 0>(root));
    }

    Iterator findMax(size_t dim) {
        return Iterator(this, findMaxDynamic<0>(dim));
    }

    bool erase(const Key &key) {
        auto prevSize = treeSize;
        erase<0>(root, key);
        return prevSize > treeSize;
    }

    Iterator erase(Iterator it) {
        if (it == end()) return it;
        auto node = it.node;
        if (!it.node->left && !it.node->right) {
            it.node = it.node->parent;
        }
        size_t depth = 0;
        auto temp = node->parent;
        while (temp) {
            temp = temp->parent;
            ++depth;
        }
        eraseDynamic<0>(node, depth % KeySize);
        return it;
    }

    size_t size() const { return treeSize; }
};
