/* bridge pattern */
#include <string>
#include <iostream>

using namespace std;

class testFixture;
class material;

class furniture {
public:
    furniture (material* mat): m(mat) {}
    virtual void tostring() = 0;
    void setMaterial(material* m) {
        this->m = m;
    }
    material* getMaterial() {
        return m;
    }
    void testFurniture() { 
        m->testMaterial(); 
    }
private:
    material* m;
};

class material {
public:
    virtual string what() = 0; 
    void setMaterialName(string s) { 
        materialName = s;
    }
    void setTestFixture(testFixture* t) { 
        this->fixture = t;
    }
    testFixture* getTestFixture() {
        return fixture;
    }
    void testMaterial() {
        fixture->test();
    }

private:
    string materialName;
    testFixture *fixture;
};

class testFixture {
public:
    virtual void test() = 0;
};

class chokingTestFixture: testFixture {
    virtual void test() {
    // test choking
    }
}

class fireTestFixture: testFixture {
    virtual void test() {
    // test fire
    }
}

class steel: public material {
public:
    steel(){
        setMaterialName("steel");
        setTestFixture(new fireTestFixture());
    }
    virtual string what(){
        return "steel";
    }
};

class wood: public material {
public:
    wood(){
        setMaterialName("wood");
        setTestFixture(new chokingTestFixture());
    }
    virtual string what() {
        return "wood";
    }
};


class chair: public furniture {
public:
    chair(material* mat): furniture(mat) {}
    void tostring() {
        cout << "this is chair and I am made of: " << getMaterial()->what() << endl;
    }
};

class desk: public furniture {
public:
    desk(material* mat): furniture(mat) {}
    void tostring() {
        cout << "this is desk and I am made of: " << getMaterial()->what() << endl;
    }
};

int main() {
    furniture* f = new desk(new steel());
    f->tostring();
    return 0;
}
