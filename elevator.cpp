/*
1 Elevator Object, Ӧ�ð���physical components: Door, Indicator Lights, 
Control Panel. һЩ����(Non physical properties): Speed, Num of floors, 
capacity, max weight. ���ܴ��µĲ���methods: moveto, stop, ringbell��Ȼ���
��Ӧ���ܹ�handle user request, ���Ի�Ӧ��һ��requestQueue, ����Ӧ�ø����Լ�
��state �� requestQueue����moveto, stop�ľ�����������һcomponent: 
requestHandler(Strategy pattern),����set��ͬ��requestHanlder.

2 Door, properties: State, method: open, close�� getState.

3 Indicator light(ָʾ����¥�㣩��properties: state; method: on, off, 
getState

4 Control Panel, ����physical component: Floor Buttons, Other buttons(Ҳ��ֱ
�Ӱ�Buttons ���� elevator��components����û������һ�������ã�

5 Button, properties: floorNum, Parent Elevator, methods: OnPress(Observer 
Pattern). 

6 ElevatorRequestHandler: handleRequest(Elevator ele, requestList rlist), ��
��define һ��interface, Ȼ���ָ��ֲ�ͬʵ��

7 Request: ����define һ��abstract class, Ȼ��������movingRequest, 
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
�Ҹо�Elevator�໹��Ӧ�ü�¼������Ӧ��ͣ����¥�㣬������stop_floors��ʾ����
��ֻ��һ��destination�����������bitmap����������ʵ�֡���������˿��԰��¶�
��¥�㡣����bank�յ�¥�ݼ��request��ʱ�򣬾����ĸ���������Ӧ������񣬲���
��¥����뵽��Ӧ����ĵ��ݵ�stop_floors���ĳһ��ͣ����ʹ���ɾ����
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