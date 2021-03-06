/*
Implement Iterator interface. Add a new function peek() to return the value of next(),
but you can't move the pointer. The constructor is defined, as PeekIterator(Iterator iter)
*/
template <typename T>
class PeekIterator {
public:
    PeekIterator(Iterator<T> iter) {
        it = iter;
        data = iter.hasNext() ? iter.next() : NULL;
    }

    bool hasNext() {
        return data != NULL;
    }

    T next() {
        T current = data;
        data = it.hasNext() ? it.next() : NULL;
        return current;
    } 

    T peek() {
        return data;
    }

private:
    Iterator<T> it;
    T data;
};