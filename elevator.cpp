/*
1 Elevator Object, 应该包含physical components: Door, Indicator Lights, 
Control Panel. 一些性质(Non physical properties): Speed, Num of floors, 
capacity, max weight. 所能从事的操作methods: moveto, stop, ringbell。然后电
梯应该能够handle user request, 所以还应有一个requestQueue, 电梯应该根据自己
的state 和 requestQueue做出moveto, stop的决定，所以有一component: 
requestHandler(Strategy pattern),可以set不同的requestHanlder.

2 Door, properties: State, method: open, close， getState.

3 Indicator light(指示所到楼层），properties: state; method: on, off, 
getState

4 Control Panel, 包含physical component: Floor Buttons, Other buttons(也可直
接把Buttons 当作 elevator的components，还没考虑哪一个方法好）

5 Button, properties: floorNum, Parent Elevator, methods: OnPress(Observer 
Pattern). 

6 ElevatorRequestHandler: handleRequest(Elevator ele, requestList rlist), 可
以define 一个interface, 然后又各种不同实现

7 Request: 可以define 一个abstract class, 然后有子类movingRequest, 
helpRequest doorRequest etc.
*/

class Door {
public:
    void open();
    void close();
    int getState() {
        return state;
    }
private:
    int state;    // Door is open or closed.
};

class Button {
public:
    void push();    // Send a request to go to a certain floor.
    void clear();
    int getIndicate() {
        return indicate;
    }
    int getState() {
        return state;
    }
private:
    int indicate;    // What does this Button indicate? 
    int state;

};

class Alarm {
public:
    void beep();
    void stopBeep();
    int getState() {
        return state;
    }
private:
    int state;    // Current state of alarm, beeping or not
};

class Light {
public:
    void turnOn();
    void turnOff();
    int getState() {
        return state;
    }
private:
    int state;    // Current state of light, on or off
};

class Elevator {
public:
    void moveTo(int dest);
    int setState(int st);
    int getState();
    int getDest();
    int setIndex();
    int getIndex();
    int setCurFloor();
    int getCurFloor();
    int checkOverLoad();
    void updateLoad(double load);
private:
    int state;
    int index;
    int destination;
    int curFloor;
//    int *requests;
    Button *buttons;
    Alarm al;
    Light Lt;
    double maxLoad;
    double currentLoad;
};
/*
我感觉Elevator类还是应该记录所有它应该停靠的楼层，比如用stop_floors表示，而
不只是一个destination。这个可以用bitmap或者数组来实现。电梯里的人可以按下多
个楼层。另外bank收到楼梯间的request的时候，决定哪个电梯来响应这个服务，并把
该楼层加入到相应服务的电梯的stop_floors里。在某一层停过后就从中删除。
*/
class Manager {
pubic:
    distributeRequest(); // Give the request to an elevator.
    run();
    shutDownElav();
    turnOnEval();
    powerOff();
    powerOn();
private:
    Elevator *evals;
    int *requests;
    int state;
};