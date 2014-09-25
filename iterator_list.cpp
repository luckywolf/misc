template<typename T>
class Node{ //used by List
private:
    Node(T data, Node<T>* next):_data(data), _next(next){}
    T _data;
    Node<T>* _next;
    friend class List<T>; //only friend can call private
    friend class ListIterator<T>; 
};

template<typename T>
class List{
public:
    List(Node<T>* head = NULL, Node<T>* tail = NULL); 
    List(const List<T>& orig); 
    List<T>& operator=(const List<T>& orig); 
    void push_front();
    void push_end();
    void pop_front();
    void pop_end();

    //the following are used for iterator:
    typedef ListIterator<T> iterator;
    iterator begin(){return iterator(_head); }
    iterator end(){return iterator(); }
private: 
    Node<T> *_head, *_tail;
};

template<typename T>
class ListIterator{    
public:
    ListIterator(Node<T>* cur = NULL): _cur(cur){}
    ListIterator(const ListIterator<T>& orig){_cur = orig._cur;}
    ListIterator& operator=(const ListIterator<T>& orig){
        _cur = orig_cur; 
        return *this;}
    bool operator==(const ListIterator<T>& orig){return _cur == orig._cur;}
    ListIterator<T>& operator++(){
        _cur = _cur->_next;
        return *this; }
    ListIterator<T> operator++(int i){
        ListIterator a(*this);
        _cur = _cur->_next;
        return a; }
    const T operator*() const {
        return _cur->_data;
    }
private:
    Node<T>* _cur; 
};
