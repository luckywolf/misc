#include <vector>
using namespace std;

template <typename T>
class heap {
public:
    void insert(T t);
    T getMin();
};
/*  version 1 */
class intHeap : public heap<int> {
public:    
    intHeap(int m): _maxSize(m), _size(0), _vec(m) {}

    void insert(int val) {
        assert(_size < _maxSize);
        int i, p;
        _vec[_size++] = val;
        for (int i = _size-1; i > 0 && _vec[p = (i-1)/2] > _vec[i]; i = p) {
            swap(p, i);
        }
    }
    
    int getMin() {
        assert(_size > 0);
        int i, c;
        int res = _vec[0];
        _vec[0] = _vec[--_size];
        for (int i = 0; (c = 2*i+1) < _size; i = c) {
            if (c+1 < _size && _vec[c+1] < _vec[c]) {
                ++c;
            }
            if (_vec[i] <= _vec[c]) {
                break;
            }
            swap(c, i);
        }
        return res;
    }
private:
    int _maxSize, _size;
    vector<int> _vec;
    swap(int i, int j) {
        int temp = _vec[i];
        _vec[i] = _vec[j];
        _vec[j] = temp;
    }
};

/* version 2 */
class intHeap : public heap<int> {
public:    
    intHeap(int m): _maxSize(m), _size(0), _vec() {}

    void insert(int val) {
        assert(_vec.size() < _maxSize);
        int i, p;
        _vec.push_back(val);
        for (int i = _vec.size()-1; i > 0 && _vec[p = (i-1)/2] > _vec[i]; i = p) {
            swap(p, i);
        }
    }
    
    int getMin() {
        assert(_vec.size() > 0);
        int i, c;
        int res = _vec[0];
        _vec[0] = _vec.back();
        vec.pop_back();
        for (int i = 0; (c = 2*i+1) < _vec.size(); i = c) {
            if (c+1 < _vec.size() && _vec[c+1] < _vec[c]) {
                ++c;
            }
            if (_vec[i] <= _vec[c]) {
                break;
            }
            swap(c, i);
        }
        return res;
    }
private:
    int _maxSize;
    vector<int> _vec;
    swap(int i, int j) {
        int temp = _vec[i];
        _vec[i] = _vec[j];
        _vec[j] = temp;
    }
};